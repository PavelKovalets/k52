/*
 * BoundedNelderMead.cpp
 *
 *  Created on: May 23, 2012
 *      Author: feanor
 */

#include "Random.h"
#include "BoundedNelderMead.h"
#include <optimize/params/i_continuous_parameters.h>

#include <math.h>
#include <stdexcept>
#include <algorithm>
#include <fstream>

using ::std::vector;

namespace k52
{
namespace optimize
{

BoundedNelderMead::BoundedNelderMead(double l, double precision, double lowerBound, double upperBound)
	: _fitnessCounter(false)
{
	_lowerBound = lowerBound;
	_upperBound = upperBound;
	_precision = precision;
	_l = l;
}

void BoundedNelderMead::Optimize(const IObjectiveFunction &function_to_optimize, IParameters* parametrs_to_optimize)
{
	IContinuousParameters* continuousParameters = dynamic_cast<IContinuousParameters*> (parametrs_to_optimize);
	if(continuousParameters == NULL)
	{
		throw std::invalid_argument("parametrsToOptimize must be of type IContinuousParameters for BoundedNelderMead");
	}
	vector<double> initialParameters = continuousParameters->GetValues();

	//Size of task
	size_t n = initialParameters.size();

	//Iteration index
	int r = 0;

	//For simplex points count
	double squareRootFrom2 = sqrt(2.);
	double r1 = _l * ( sqrt((double)(n+1)) + n - 1 ) / ( n * squareRootFrom2 );
	double r2 = _l * ( sqrt((double)(n+1)) - 1 ) / ( n * squareRootFrom2 );

	//Random init
	vector<double> basePoint(n);
	for(int i = 0; i < n; i++)
	{
		basePoint[i] = Random::Instance().getContinuousRandomQuantity(_lowerBound, _upperBound);
	}
	//Build simplex
	vector< vector<double> > polygon = getRegularSimplex(basePoint, _l);

	//count values
	vector<double> functionValues = countObjectiveFunctionValues(polygon, continuousParameters, function_to_optimize);	

	do
	{
		outputPolygon(polygon);
		r++;
		int firstMaxIndex = 0, secondMaxIndex = 0, minIndex = 0;
		//determine maximums and minimum
		getIndexes(functionValues, &firstMaxIndex, &secondMaxIndex, &minIndex);

		double highestValue = functionValues[firstMaxIndex];
		double secondHighestValue = functionValues[secondMaxIndex];
		double lowestValue = functionValues[minIndex];

		//determine center of mass
		vector<double> centerOfMass = getCenterOfMass(polygon, firstMaxIndex); 

		//Reflect max point - we seek for minimum
		vector<double> reflectedPoint = reflexion(centerOfMass, polygon[firstMaxIndex]);
		correctByProjectingToBounds(&reflectedPoint);
		double reflectedPointValue = countObjectiveFunctionValue(reflectedPoint, continuousParameters, function_to_optimize);

		if( reflectedPointValue < lowestValue)
		{
			vector<double> expandedPoint = expansion(centerOfMass, reflectedPoint);
			correctByProjectingToBounds(&expandedPoint);
			double expandedPointValue = countObjectiveFunctionValue(expandedPoint, continuousParameters, function_to_optimize);

			if( expandedPointValue < reflectedPointValue )
			{
				//Replace max with expanded
				polygon[firstMaxIndex] = expandedPoint;
				functionValues[firstMaxIndex] = expandedPointValue;
				continue;
			}
			else
			{
				//Replace max with reflected
				polygon[firstMaxIndex] = reflectedPoint;
				functionValues[firstMaxIndex] = reflectedPointValue;
				continue;
			}
		}
		else
		{
			if( reflectedPointValue <= secondHighestValue )
			{
				//Replace max with reflected
				polygon[firstMaxIndex] = reflectedPoint;
				functionValues[firstMaxIndex] = reflectedPointValue;
				continue;
			}
			else
			{
				if( reflectedPointValue < highestValue )
				{
					//Replace max with reflected
					polygon[firstMaxIndex] = reflectedPoint;
					functionValues[firstMaxIndex] = reflectedPointValue;
					highestValue = reflectedPointValue;
				}

				vector<double> contractionPoint = contraction(centerOfMass, polygon[firstMaxIndex]);
				double contractionPointValue = countObjectiveFunctionValue(contractionPoint, continuousParameters, function_to_optimize);

				if( contractionPointValue > highestValue )
				{
					reduction(&polygon, minIndex);
					continue;
				}
				else
				{
					//Replace max with contracted
					polygon[firstMaxIndex] = contractionPoint;
					functionValues[firstMaxIndex] = contractionPointValue;
					continue;
				}
			}
		}
	}while( countDifferance(functionValues) > _precision );


	size_t bestIndex = std::distance(functionValues.begin(), std::max_element(functionValues.begin(), functionValues.end()));
	continuousParameters->SetValues( polygon[bestIndex] );
}

double BoundedNelderMead::countDifferance(const vector<double>& values)
{
	double summ = 0;
	for(size_t i = 0; i < values.size(); i++)
	{
		summ += values[i];
	}
	double averadge = summ / values.size();

	double squareSumm = 0;
	for(size_t i = 0; i < values.size(); i++)
	{
		double diff = values[i] - averadge;
		squareSumm += diff*diff;
	}
	return sqrt( squareSumm / values.size());
}

void BoundedNelderMead::getIndexes(const vector<double>& values, int* firstMaxIndex, int* secoundMaxIndex, int* minIndex)
{
	if(values.size() < 2)
	{
		throw std::invalid_argument("values must have at least 2 elements");
	}

	if( values[0] > values[1] )
	{
		*firstMaxIndex = 0;
		*secoundMaxIndex = 1;
		*minIndex = 1;
	}
	else
	{
		*firstMaxIndex = 1;
		*secoundMaxIndex = 0;
		*minIndex = 0;
	}

	for (int i = 2; i<values.size(); i++) 
	{
		if (values[i] > values[*firstMaxIndex]) 
		{
			*secoundMaxIndex = *firstMaxIndex;
			*firstMaxIndex = i;
		} 
		else if (values[i]  > values[*secoundMaxIndex]) 
		{
			*secoundMaxIndex = i;
		}

		if( values[i] < values[*minIndex])
		{
			*minIndex = i;
		}
	}
}

vector< vector<double> > BoundedNelderMead::getRegularSimplex(const vector<double>& basePoint, double l)
{
	//Size of task
	size_t n = basePoint.size();

	//For simplex points count
	double squareRootFrom2 = sqrt(2.);
	double r1 = l * ( sqrt((double)(n+1)) + n - 1 ) / ( n * squareRootFrom2 );
	double r2 = l * ( sqrt((double)(n+1)) - 1 ) / ( n * squareRootFrom2 );

	vector< vector<double> > regularSimplex( n + 1 );
	regularSimplex[0] = basePoint;

	for(int i = 1; i < n + 1; i++)
	{
		regularSimplex[i] = vector<double>(n);

		for(int j = 0; j < n; j++)
		{
			if( j == i - 1 )
			{
				regularSimplex[i][j] = basePoint[j] + r1;
			}
			else
			{
				regularSimplex[i][j] = basePoint[j] + r2;
			}
		}
	}

	return regularSimplex;
}

double BoundedNelderMead::countObjectiveFunctionValue(const vector<double>& parameters,
	IContinuousParameters* baseParameters,
	const IObjectiveFunction & functionToOptimize)
{
	vector< vector<double> > cover(1);
	cover[0] = parameters;
	return countObjectiveFunctionValues(cover, baseParameters, functionToOptimize)[0];
}

vector<double> BoundedNelderMead::countObjectiveFunctionValues(const vector< vector<double> >& parametersValues,
	IContinuousParameters* baseParameters,
	const IObjectiveFunction & functionToOptimize)
{
	size_t N = parametersValues.size();
	vector<IContinuousParameters::shared_ptr> storages(N);
	vector<const IParameters*> parameters(N);
	for(size_t i = 0; i < N; i++)
	{
		baseParameters->SetValues(parametersValues[i]);
		storages[i] = IContinuousParameters::shared_ptr(baseParameters->Clone());

		//TODO fix - do not use inner ptr
		parameters[i] = storages[i].get();
	}

	return _fitnessCounter.countObjectiveFunctionValues(parameters, functionToOptimize);
}

vector<double> BoundedNelderMead::reflexion(const vector<double>& centerOfMass, const vector<double>& targetPoint)
{
	double reflectionCoefficient = 1;
	vector<double> newPoint (targetPoint.size());

	//Reflect
	for(int i = 0; i < targetPoint.size(); i++)
	{
		newPoint[i] = centerOfMass[i] + reflectionCoefficient * (centerOfMass[i] - targetPoint[i]);
	}

	return newPoint;
}

vector<double> BoundedNelderMead::expansion(const vector<double>& centerOfMass, const vector<double>& targetPoint)
{
	double expansionCoefficient = 2;
	vector<double> newPoint (targetPoint.size());

	//Reflect
	for(int i = 0; i < targetPoint.size(); i++)
	{
		newPoint[i] = centerOfMass[i] + expansionCoefficient * (targetPoint[i] - centerOfMass[i]);
	}

	return newPoint;
}

vector<double> BoundedNelderMead::contraction(const vector<double>& centerOfMass, const vector<double>& targetPoint)
{
	double contractionCoefficient = 0.5;
	vector<double> newPoint (targetPoint.size());

	//Reflect
	for(int i = 0; i < targetPoint.size(); i++)
	{
		newPoint[i] = centerOfMass[i] + contractionCoefficient * (targetPoint[i] - centerOfMass[i]);
	}

	return newPoint;
}

void BoundedNelderMead::reduction(vector< vector<double> >* polygon, int pointIndex)
{
	if(pointIndex<0 || pointIndex>= polygon->size())
	{
		throw std::invalid_argument("Incorrect pointIndex");
	}

	double reductionCoefficient = 0.5;
	size_t n = (*polygon)[0].size();

	for(int i = 0; i < n +1; i++)
	{
		if( i != pointIndex )
		{
			for(int j = 0; j < n; j++)
			{
				(*polygon)[i][j] = (*polygon)[pointIndex][j] + reductionCoefficient * ( (*polygon)[i][j]  - (*polygon)[pointIndex][j] );
			}
		}
	}
}

vector<double> BoundedNelderMead::getCenterOfMass(const vector< vector<double> >& polygon, int pointIndex)
{
	if(pointIndex<0 || pointIndex>= polygon.size())
	{
		throw std::invalid_argument("Incorrect pointIndex");
	}
	size_t n = polygon[0].size();
	vector<double> centerOfMass(n);

	//TODO implement with valarray
	for(int i = 0; i < n; i++)
	{
		centerOfMass[i] = 0;

		for(int j = 0; j < n+1; j++)
		{
			if( j != pointIndex )
			{
				centerOfMass[i] += polygon[j][i];
			}
		}

		centerOfMass[i] /= n;
	}

	return centerOfMass;
}

void BoundedNelderMead::correctByProjectingToBounds(vector<double>* point)
{
	for(size_t i = 0; i < point->size(); i++)
	{
		if( (*point)[i] > _upperBound)
		{
			(*point)[i] = _upperBound;
		}
		else if( (*point)[i] < _lowerBound)
		{
			(*point)[i] = _lowerBound;
		}
	}
}

void BoundedNelderMead::outputPolygon(const vector< vector<double> >& polygon)
{
	std::ofstream polygonOutput("polygon.plot", std::ofstream::app);
	polygonOutput<<std::endl;

	for(size_t i = 0; i < polygon.size(); i++)
	{
		for(size_t j = 0; j < polygon[i].size(); j++)
		{
			polygonOutput << polygon[i][j] << " ";
		}
		polygonOutput<<std::endl;
	}
}

}/* namespace optimize */
}/* namespace k52 */
