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

namespace k52
{
namespace optimize
{

double DoubleParameter::getValue() const
{
    return  _baseIntParameter->getValue() * _precision + _minValue;
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
	_baseIntParameter = NULL;
}

DoubleParameter::DoubleParameter(double desiredValue, double minValue, double maxValue, double desiredPrecision)
{
	if(maxValue <= minValue)
	{
		throw std::invalid_argument("maxValue <= minValue");
	}
	
	_maxValue = maxValue;
	_minValue = minValue;

	if(!checkBounds(desiredValue))
	{
		throw std::invalid_argument("desiredValue does not lie whithin [minValue;maxValue] interval.");
	}

	int bestMaxInt = CountBestMaxInt( getMaxInt(minValue, maxValue, desiredPrecision) );
	int minInt = 0;

	_precision = (maxValue - minValue) / bestMaxInt;
	//TODO check for smts like CEIL - int rounding may provide bugs
	int intValue = /*ceil*/((desiredValue - minValue)/_precision);

	_baseIntParameter = IntParameter::shared_ptr(new IntParameter(intValue, minInt, bestMaxInt));

	this->setConstChromosomeSize(_baseIntParameter->getChromosomeSize());
}

DoubleParameter::DoubleParameter(const DoubleParameter& a)
{
	_baseIntParameter = NULL;
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

		if(a._baseIntParameter != NULL)
		{
			_baseIntParameter = IntParameter::shared_ptr(a._baseIntParameter->clone());
		}
		else
		{
			_baseIntParameter = NULL;
		}
	}
	// by convention, always return *this
	return *this;
}

DoubleParameter *DoubleParameter::clone() const
{
	DoubleParameter* clone = new DoubleParameter(*this);
	return clone;
}

bool DoubleParameter::checkConstraints() const
{
	return checkBounds(getValue());
}

void DoubleParameter::setChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const
{
	_baseIntParameter->setChromosome(from, to);
}

void DoubleParameter::setFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to)
{
	_baseIntParameter->setFromChromosome(from, to);
}

bool DoubleParameter::checkBounds(double value) const
{
	return value >= _minValue && value <= _maxValue;
}

int DoubleParameter::getMaxInt(double minValue, double maxValue, double precision)
{
	int maxInt = ceil((maxValue - minValue)/precision);
	if(maxInt < 1)
	{
		throw std::invalid_argument("minValue maxValue or precision were set incorrect");
	}
	return maxInt;
}

}/* namespace optimize */
}/* namespace k52 */
