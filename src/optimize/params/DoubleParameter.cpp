/*
 * DoubleParameter.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: feanor
 */

#include <optimize/params/DoubleParameter.h>
#include "../Random.h"
#include <math.h>
#include <stdexcept>

double DoubleParameter::getValue() const
{
    return _value;
}

void DoubleParameter::setValue(double value)
{
	_value = value;
}

double DoubleParameter::getMaxValue() const
{
	return _maxValue;
}

double DoubleParameter::getMinValue() const
{
	return _minValue;
}

double DoubleParameter::getActualPrecision() const
{
	return _precision;
}

int DoubleParameter::CountBestMaxInt(int initialMaxInt)
{
	int bestMaxInt = 1;

	while(initialMaxInt>bestMaxInt)
	{
		bestMaxInt *= 2;
	}

	return bestMaxInt;
}

DoubleParameter::DoubleParameter()
{
	_baseIntParameter = 0;
}

DoubleParameter::DoubleParameter(double value, double minValue, double maxValue, double desiredPrecision)
{
	if(maxValue <= minValue)
	{
		throw std::invalid_argument("maxValue <= minValue");
	}

	_maxValue = maxValue;
	_minValue = minValue;
	_value = value;

	int bestMaxInt = CountBestMaxInt( getMaxInt(minValue, maxValue, desiredPrecision) );
	int minInt = 0;

	_precision = (maxValue - minValue) / bestMaxInt;
	//TODO check for smts like CEIL - int rounding may provide bugs
	int intValue = /*ceil*/((value - minValue)/_precision);

	
	_baseIntParameter = new IntParameter(intValue, minInt, bestMaxInt);

	this->setConstChromosomeSize(_baseIntParameter->getChromosomeSize());
}

DoubleParameter::DoubleParameter(const DoubleParameter& a)
{
	_baseIntParameter = 0;
	*this = a;
}

DoubleParameter& DoubleParameter::operator=(const DoubleParameter & a)
{
	if (this != &a) // protect against invalid self-assignment
	{
		this->ConstChromosomeSizeParemeters::operator =(a);
		_maxValue = a._maxValue;
		_minValue = a._minValue;
		_precision = a._precision;
		_value = a._value;

		if(a._baseIntParameter == 0)
		{
			_baseIntParameter = 0;
			return *this;
		}

		// 1: allocate new memory and copy the elements
		IntParameter* newBaseParameter = a._baseIntParameter->clone();

		// 2: deallocate old memory
		if(_baseIntParameter != 0)
		{
			delete _baseIntParameter;
		}

		// 3: assign the new memory to the object
		_baseIntParameter = newBaseParameter;
	}
	// by convention, always return *this
	return *this;
}

DoubleParameter::~DoubleParameter()
{
	if(_baseIntParameter != 0)
	{
		delete _baseIntParameter;
		_baseIntParameter = 0;
	}
}

DoubleParameter *DoubleParameter::clone() const
{
	DoubleParameter* clone = new DoubleParameter(_value, _minValue, _maxValue, _precision);
	return clone;
}

bool DoubleParameter::checkConstraints() const
{
	return _value>=_minValue && _value<=_maxValue;
}

void DoubleParameter::setChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const
{
	_baseIntParameter->setChromosome(from, to);
}

void DoubleParameter::setFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to)
{
	_baseIntParameter->setFromChromosome(from, to);

	int baseInt = _baseIntParameter->getValue();
	_value = baseInt * _precision + _minValue;
}

int DoubleParameter::getMaxInt( double minValue, double maxValue, double precision)
{
	int maxInt = ceil((maxValue - minValue)/precision);
	if(maxInt < 1)
	{
		throw std::invalid_argument("minValue maxValue or precision were set incorrect");
	}
	return maxInt;
}
