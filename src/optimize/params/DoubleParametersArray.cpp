/*
 * DoubleParametersArray.cpp
 *
 *  Created on: Mar 25, 2012
 *      Author: feanor
 */

#include <optimize/params/DoubleParametersArray.h>
#include <stdexcept>

DoubleParametersArray::DoubleParametersArray(double minValue, double maxValue, double desiredPrecision, size_t numberOfParameters)
{
	_minValue = minValue;
	_maxValue = maxValue;
	_desiredPrecision = desiredPrecision;

	if(numberOfParameters<=0)
	{
		throw std::logic_error("numberOfParameters<=0!");
	}

	vector<IDiscreteParameters::shared_ptr> doubleParameters(numberOfParameters);

	for(size_t i=0; i<numberOfParameters; i++)
	{
		doubleParameters[i] = IDiscreteParameters::shared_ptr (new DoubleParameter(0, _minValue, _maxValue, _desiredPrecision));
	}

	_doubleParameters = CompositeDiscreteParameters::shared_ptr(new CompositeDiscreteParameters());
	_doubleParameters->initialize(doubleParameters);
}

double DoubleParametersArray::getMaxValue() const
{
    return _maxValue;
}

double DoubleParametersArray::getMinValue() const
{
    return _minValue;
}

size_t DoubleParametersArray::getNumberOfParameters() const
{
    return _doubleParameters->getNumberOfParameters();
}

DoubleParametersArray *DoubleParametersArray::clone() const
{
	DoubleParametersArray* clone = new DoubleParametersArray(_minValue, _maxValue, _desiredPrecision, _doubleParameters->getNumberOfParameters());

	//TODO FIX - _doubleParameters should be also cloned
	clone->_doubleParameters = CompositeDiscreteParameters::shared_ptr(_doubleParameters->clone());

	return clone;
}

size_t DoubleParametersArray::getChromosomeSize() const
{
	return _doubleParameters->getChromosomeSize();
}

vector<double> DoubleParametersArray::getValues() const
{
	vector<double> values(_doubleParameters->getNumberOfParameters());

	for(size_t i=0; i<_doubleParameters->getNumberOfParameters(); i++)
	{
		values[i] = getDoubleParameter(i)->getValue();
	}
	return values;
}

const DoubleParameter::shared_ptr DoubleParametersArray::getDoubleParameter(size_t index) const
{
	return boost::dynamic_pointer_cast<DoubleParameter>(_doubleParameters->getParameter(index));
}


bool DoubleParametersArray::checkConstraints() const
{
	return _doubleParameters->checkConstraints();
}

void DoubleParametersArray::setFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to)
{
	_doubleParameters->setFromChromosome(from, to);
}

void DoubleParametersArray::setChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const
{
	_doubleParameters->setChromosome(from, to);
}

double DoubleParametersArray::getActualPrecision() const
{
	return getDoubleParameter(0)->getActualPrecision();
}
