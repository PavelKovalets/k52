/*
 * IntParameter.cpp
 *
 *  Created on: Jan 29, 2012
 *      Author: feanor
 */

#include <optimize/params/IntParameter.h>
#include "../Random.h"

using ::std::vector;

namespace k52
{
namespace optimize
{

IntParameter* IntParameter::clone() const
{
	IntParameter* clone = new IntParameter(_value, _minValue, _maxValue);
	return clone;
}

IntParameter::IntParameter(int value, int minValue, int maxValue)
{
	setConstChromosomeSize( countVectorSize(minValue, maxValue) );

	_value = value;
	_minValue = minValue;
	_maxValue = maxValue;
}

void IntParameter::setChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const
{
	size_t chromosomeSize = to - from;
	this->checkForConstChromosomeSize(chromosomeSize);

	IntParameter::setBoolVectorFromInt(from, to, _value - _minValue);
}

void IntParameter::setFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to)
{
	size_t chromosomeSize = to - from;
	this->checkForConstChromosomeSize(chromosomeSize);

	_value = IntParameter::getIntFromBoolVector(from, to) + _minValue;
}

size_t IntParameter::countVectorSize(int minValue, int maxValue)
{
	int x = 1;
	int target = maxValue - minValue;
	size_t power = 0;
	while(target>x)
	{
		x*=2;
		power++;
	}
	return power;
}

void IntParameter::setBoolVectorFromInt(vector<bool>::iterator from, vector<bool>::iterator to, int value)
{
	size_t bitNumber = 0;

	for (vector<bool>::iterator it = from; it != to; it++)
	{
		if ((value >> bitNumber) & 1)
		{
			(*it) = true;
		}
		else
		{
			(*it) = false;
		}

		bitNumber++;
	}
}

int IntParameter::getIntFromBoolVector(vector<bool>::const_iterator from, vector<bool>::const_iterator to)
{
	unsigned int result = 0;

	size_t bitNumber = 0;

	for (vector<bool>::const_iterator it = from; it != to; it++)
	{
		if (*it)
		{
			result |= (1 << bitNumber);
		}
		else
		{
			result &= ~(1 << bitNumber);
		}

		bitNumber++;
	}

	return ((int)result);
}

bool IntParameter::checkConstraints() const
{
	if(_value > (_maxValue))
	{
		return false;
	}

	if(_value < (_minValue))
	{
		return false;
	}

	return true;
}

int IntParameter::getValue() const
{
	return _value;
}

int IntParameter::getMaxValue() const
{
	return _maxValue;
}

int IntParameter::getMinValue() const
{
	return _minValue;
}

}/* namespace optimize */
}/* namespace k52 */
