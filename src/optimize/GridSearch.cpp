/*
 * GridSearch.cpp
 *
 *  Created on: May 20, 2012
 *      Author: feanor
 */

#include "GridSearch.h"
#include <optimize/params/IContinuousParameters.h>
#include <math.h>
#include <stdexcept>
#include <algorithm>

using ::std::vector;

namespace k52
{
namespace optimize
{

GridSearch::GridSearch(double precision, double lowerBound, double upperBound)
	: _fitnessCounter(false)
{
	_lowerBound = lowerBound;
	_upperBound = upperBound;
	_precision = precision;
}

size_t GridSearch::integerPow(size_t value, size_t pow)
{
	size_t result = 1;

	for(size_t i = 0; i < pow; i++)
	{
		result *= value;
	}

	return result;
}

void GridSearch::optimize(IParameters *parametrsToOptimize, const IObjectiveFunction & functionToOptimize)
{
	IContinuousParameters* continuousParameters = dynamic_cast<IContinuousParameters*> (parametrsToOptimize);

	vector<double> initialParameters = continuousParameters->getValues();

	int sizePerParameter = floor((_upperBound - _lowerBound)/_precision) + 1;

	if(sizePerParameter <= 0)
	{
		throw std::invalid_argument("upperBound, lowerBound, or precision was set incorrect");
	}

	size_t numberOfParameters = initialParameters.size();
	size_t totalSize = integerPow(sizePerParameter, numberOfParameters);

	vector<IContinuousParameters::shared_ptr> parametersStorages(totalSize);
	vector<const IParameters*> parameters(totalSize);
	//Fill all parameters
	for(size_t i = 0; i < totalSize; i++)
	{
		vector<double> values(numberOfParameters);

		for(size_t j = 0; j < numberOfParameters; j++)
		{
			size_t index = i / integerPow(sizePerParameter, j);
			values[j] = (index % sizePerParameter) * _precision + _lowerBound;
		}

		continuousParameters->setValues(values);
		parametersStorages[i] = IContinuousParameters::shared_ptr(continuousParameters->clone());

		//TODO FIX do not return local ptr
		parameters[i] = parametersStorages[i].get();
	}

	vector<double> countedValues(totalSize);
	_fitnessCounter.countObjectiveFunctionValues(&countedValues, parameters, functionToOptimize);
	size_t bestIndex = distance(countedValues.begin(), max_element(countedValues.begin(), countedValues.end()));

	continuousParameters->setValues( parametersStorages[bestIndex]->getValues() );

}

}/* namespace optimize */
}/* namespace k52 */
