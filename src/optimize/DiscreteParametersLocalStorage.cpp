/*
 * DiscreteParametersLocalStorage.cpp
 *
 *  Created on: May 20, 2012
 *      Author: feanor
 */

#include <optimize/DiscreteParametersLocalStorage.h>

DiscreteParametersLocalStorage::DiscreteParametersLocalStorage(const IDiscreteParameters* const parameters)
	: ParametersLocalStorage(parameters)
{
}

DiscreteParametersLocalStorage::DiscreteParametersLocalStorage(const DiscreteParametersLocalStorage & a)
	: ParametersLocalStorage(a)
{
}

DiscreteParametersLocalStorage::DiscreteParametersLocalStorage()
	: ParametersLocalStorage()
{
}

void DiscreteParametersLocalStorage::setChromosome(vector<bool>::iterator from, vector<bool>::iterator to) const
{
	getLocalParameters()->setChromosome(from, to);
}

void DiscreteParametersLocalStorage::setFromChromosome(vector<bool>::const_iterator from, vector<bool>::const_iterator to)
{
	getCloneableObjectAsParameters()->setFromChromosome(from, to);
}

size_t DiscreteParametersLocalStorage::getChromosomeSize() const
{
	return getLocalParameters()->getChromosomeSize();
}

const IDiscreteParameters* DiscreteParametersLocalStorage::getLocalParameters() const
{
	return (const IDiscreteParameters *const) this->getLocalCloneableObject();
}

IDiscreteParameters* DiscreteParametersLocalStorage::getCloneableObjectAsParameters()
{
	return (IDiscreteParameters *)_localCloneableObject;
}
