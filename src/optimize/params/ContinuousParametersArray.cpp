/*
 * ContinuousParametersArray.cpp
 *
 *  Created on: May 20, 2012
 *      Author: feanor
 */

#include <optimize/params/ContinuousParametersArray.h>
#include <stdexcept>

ContinuousParametersArray::ContinuousParametersArray(size_t numberOfParameters)
	: _values(numberOfParameters)
{
}

void ContinuousParametersArray::setValues(const std::vector<double> & values)
{
	if(values.size() != _values.size())
	{
		throw std::invalid_argument("values has incorrect size");
	}

	for(size_t i=0; i<_values.size(); i++)
	{
		_values[i] = values[i];
	}
}

std::vector<double> ContinuousParametersArray::getValues() const
{
	return _values;
}

ContinuousParametersArray *ContinuousParametersArray::clone() const
{
	ContinuousParametersArray* clone = new ContinuousParametersArray(_values.size());
	clone->_values = _values;
	return clone;
}

bool ContinuousParametersArray::checkConstraints() const
{
	return true;
}



