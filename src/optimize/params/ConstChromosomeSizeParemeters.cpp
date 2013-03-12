/*
 * ConstChromosomeSizeParemeters.cpp
 *
 *  Created on: Apr 14, 2012
 *      Author: feanor
 */

#include <optimize/params/ConstChromosomeSizeParemeters.h>
#include <stdexcept>

ConstChromosomeSizeParemeters::ConstChromosomeSizeParemeters()
{
	_wasChromosomeSizeSet = false;
	_chromosomeSize = 0;
}

size_t ConstChromosomeSizeParemeters::getChromosomeSize() const
{
	checkIfChromosomeWasSet();
	return _chromosomeSize;
}

void ConstChromosomeSizeParemeters::checkForConstChromosomeSize(size_t chromosomeSize) const
{
	checkIfChromosomeWasSet();

	if(chromosomeSize != _chromosomeSize)
	{
		throw std::invalid_argument("Chromosome size do not match");
	}
}

void ConstChromosomeSizeParemeters::setConstChromosomeSize(size_t chromosomeSize)
{
	if(_wasChromosomeSizeSet)
	{
		throw std::logic_error("ChromosomeSize must only be set once");
	}
	else
	{
		_wasChromosomeSizeSet = true;
		_chromosomeSize = chromosomeSize;
	}
}

void ConstChromosomeSizeParemeters::checkIfChromosomeWasSet() const
{
	if(!_wasChromosomeSizeSet)
	{
		throw std::logic_error("Chromosome size was not set."
				" Please call setConstChromosomeSize before using setFromChromosome in ConstChromosomeSizeParemeters");
	}
}

