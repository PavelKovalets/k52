/*
 * DoubleParametersArray.cpp
 *
 *  Created on: Mar 25, 2012
 *      Author: feanor
 */

#include <optimize/params/DoubleParametersArray.h>
#include <stdexcept>

namespace k52
{
namespace optimize
{

DoubleParametersArray::DoubleParametersArray(double minValue, double maxValue, double desiredPrecision, size_t numberOfParameters)
{
	_minValue = minValue;
	_maxValue = maxValue;
	_desiredPrecision = desiredPrecision;

	if(numberOfParameters<=0)
	{
		throw std::logic_error("numberOfParameters<=0!");
	}

	std::vector<IDiscreteParameters::shared_ptr> doubleParameters(numberOfParameters);

	for(size_t i=0; i<numberOfParameters; i++)
	{
		doubleParameters[i] = IDiscreteParameters::shared_ptr (new DoubleParameter(_minValue, _minValue, _maxValue, _desiredPrecision));
	}

	_doubleParameters = CompositeDiscreteParameters::shared_ptr(new CompositeDiscreteParameters());
	_doubleParameters->Initialize(doubleParameters);
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
    return _doubleParameters->GetNumberOfParameters();
}

DoubleParametersArray *DoubleParametersArray::Clone() const
{
	DoubleParametersArray* clone = new DoubleParametersArray(_minValue, _maxValue, _desiredPrecision, _doubleParameters->GetNumberOfParameters());
	clone->_doubleParameters = CompositeDiscreteParameters::shared_ptr(_doubleParameters->Clone());
	return clone;
}

size_t DoubleParametersArray::GetChromosomeSize() const
{
	return _doubleParameters->GetChromosomeSize();
}

std::vector<double> DoubleParametersArray::getValues() const
{
	std::vector<double> values(_doubleParameters->GetNumberOfParameters());

	for(size_t i=0; i<_doubleParameters->GetNumberOfParameters(); i++)
	{
		values[i] = getDoubleParameter(i)->GetValue();
	}
	return values;
}

const DoubleParameter::shared_ptr DoubleParametersArray::getDoubleParameter(size_t index) const
{
	return boost::dynamic_pointer_cast<DoubleParameter>(_doubleParameters->GetParameter(index));
}


bool DoubleParametersArray::CheckConstraints() const
{
	return _doubleParameters->CheckConstraints();
}

void DoubleParametersArray::SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to)
{
	_doubleParameters->SetFromChromosome(from, to);
}

void DoubleParametersArray::SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const
{
	_doubleParameters->SetChromosome(from, to);
}

double DoubleParametersArray::getActualPrecision() const
{
	return getDoubleParameter(0)->get_actual_precision();
}

}/* namespace optimize */
}/* namespace k52 */
