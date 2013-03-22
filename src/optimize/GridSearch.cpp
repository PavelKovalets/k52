/*
 * GridSearch.cpp
 *
 *  Created on: May 20, 2012
 *      Author: feanor
 */

#include "GridSearch.h"
#include <optimize/params/i_continuous_parameters.h>
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

void GridSearch::Optimize(const IObjectiveFunction &function_to_optimize, IParameters* parametrs_to_optimize)
{
	IContinuousParameters* continuousParameters = dynamic_cast<IContinuousParameters*> (parametrs_to_optimize);

	vector<double> initialParameters = continuousParameters->GetValues();

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

		continuousParameters->SetValues(values);
		parametersStorages[i] = IContinuousParameters::shared_ptr(continuousParameters->Clone());

		//TODO FIX do not return local ptr
		parameters[i] = parametersStorages[i].get();
	}

	vector<double> countedValues = _fitnessCounter.CountObjectiveFunctionValues(parameters, function_to_optimize);
	size_t bestIndex = distance(countedValues.begin(), max_element(countedValues.begin(), countedValues.end()));

	continuousParameters->SetValues( parametersStorages[bestIndex]->GetValues() );

}

}/* namespace optimize */
}/* namespace k52 */
