/*
 * CompositeParameters.cpp
 *
 *  Created on: Apr 22, 2012
 *      Author: feanor
 */

#include <optimize/params/CompositeDiscreteParameters.h>
#include <stdexcept>

namespace k52
{
namespace optimize
{

void CompositeDiscreteParameters::initialize(std::vector<IDiscreteParameters::shared_ptr> parameters)
{
	_parametersSet = std::vector<IDiscreteParameters::shared_ptr>(parameters.size());

	for(size_t i=0; i<_parametersSet.size(); i++)
	{
		_parametersSet[i] = IDiscreteParameters::shared_ptr(parameters[i]->Clone());
	}

	this->SetConstChromosomeSize( countTotalChromosomeSize() );

	_initializationChecker.SetInitialized();
}

size_t CompositeDiscreteParameters::getNumberOfParameters() const
{
	_initializationChecker.InitializationCheck();

    return _parametersSet.size();
}

const IDiscreteParameters::shared_ptr CompositeDiscreteParameters::getParameter(size_t index) const
{
	_initializationChecker.InitializationCheck();

	if(index+1 > _parametersSet.size())
	{
		throw std::out_of_range("index in getParameter method is out of range");
	}

	return _parametersSet[index];
}

CompositeDiscreteParameters *CompositeDiscreteParameters::Clone() const
{
	_initializationChecker.InitializationCheck();

	CompositeDiscreteParameters* clone = new CompositeDiscreteParameters();
	clone->initialize(_parametersSet);
	return clone;
}

bool CompositeDiscreteParameters::CheckConstraints() const
{
	_initializationChecker.InitializationCheck();

	for(size_t i=0; i<_parametersSet.size(); i++)
	{
		if(!_parametersSet[i]->CheckConstraints())
		{
			return false;
		}
	}
	return true;
}

void CompositeDiscreteParameters::SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const
{
	_initializationChecker.InitializationCheck();

	size_t chromosomeSize = to - from;

	this->CheckForConstChromosomeSize(chromosomeSize);

	std::vector<bool>::iterator currentFrom = from;

	for(size_t i = 0; i < _parametersSet.size(); i++)
	{
		size_t parameterChromosomeSize = _parametersSet[i]->GetChromosomeSize();

		std::vector<bool>::iterator currentTo = currentFrom + parameterChromosomeSize;

		_parametersSet[i]->SetChromosome(currentFrom, currentTo);

		currentFrom = currentTo;
	}
}

void CompositeDiscreteParameters::SetFromChromosome(std::vector<bool>::const_iterator from, std::vector<bool>::const_iterator to)
{
	_initializationChecker.InitializationCheck();

	size_t chromosomeSize = to - from;

	this->CheckForConstChromosomeSize(chromosomeSize);

	std::vector<bool>::const_iterator currentFrom = from;

	for(size_t i = 0; i < _parametersSet.size(); i++)
	{
		size_t parameterChromosomeSize = _parametersSet[i]->GetChromosomeSize();

		std::vector<bool>::const_iterator currentTo = currentFrom + parameterChromosomeSize;

		_parametersSet[i]->SetFromChromosome(currentFrom, currentTo);

		currentFrom = currentTo;
	}
}

size_t CompositeDiscreteParameters::countTotalChromosomeSize() const
{
	size_t totalChromosomeSize = 0;
	for(size_t i=0; i<_parametersSet.size(); i++)
	{
		totalChromosomeSize += _parametersSet[i]->GetChromosomeSize();
	}
	return totalChromosomeSize;
}

}/* namespace optimize */
}/* namespace k52 */

