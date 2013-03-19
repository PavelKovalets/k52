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

	this->setConstChromosomeSize( countTotalChromosomeSize() );

	_initializationChecker.setInitialized();
}

size_t CompositeDiscreteParameters::getNumberOfParameters() const
{
	_initializationChecker.initializationCheck();

    return _parametersSet.size();
}

const IDiscreteParameters::shared_ptr CompositeDiscreteParameters::getParameter(size_t index) const
{
	_initializationChecker.initializationCheck();

	if(index+1 > _parametersSet.size())
	{
		throw std::out_of_range("index in getParameter method is out of range");
	}

	return _parametersSet[index];
}

CompositeDiscreteParameters *CompositeDiscreteParameters::Clone() const
{
	_initializationChecker.initializationCheck();

	CompositeDiscreteParameters* clone = new CompositeDiscreteParameters();
	clone->initialize(_parametersSet);
	return clone;
}

bool CompositeDiscreteParameters::checkConstraints() const
{
	_initializationChecker.initializationCheck();

	for(size_t i=0; i<_parametersSet.size(); i++)
	{
		if(!_parametersSet[i]->checkConstraints())
		{
			return false;
		}
	}
	return true;
}

void CompositeDiscreteParameters::SetChromosome(std::vector<bool>::iterator from, std::vector<bool>::iterator to) const
{
	_initializationChecker.initializationCheck();

	size_t chromosomeSize = to - from;

	this->checkForConstChromosomeSize(chromosomeSize);

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
	_initializationChecker.initializationCheck();

	size_t chromosomeSize = to - from;

	this->checkForConstChromosomeSize(chromosomeSize);

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

