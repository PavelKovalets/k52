/*
 * Mutator.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: feanor
 */

#include "Mutator.h"
#include "Random.h"
#include <math.h>
#include <stdexcept>

Mutator& Mutator::Instance()
{
	static Mutator self;
	return self;
}

void Mutator::mutateBoolArray(double genMutationProbability, std::vector<bool>* array)
{
	if(_wasProbabilitySet)
	{
		if(_mutationProbability != genMutationProbability)
		{
			throw std::logic_error("GenMutationProbability must not be changed according to current implementation of Mutator");
		}
	}
	else
	{
		setMutationProbability(genMutationProbability);
	}

    for(size_t i = 0;i < array->size(); i++)
    {
    	if(_currentlySkippedGens>=_gensToSkipNow)
    	{
    		(*array)[i] = !(*array)[i];
    		setGensToSkipNow();
    	}
    	else
    	{
    		_currentlySkippedGens ++;
    	}
    }
}

Mutator::Mutator()
{
	_maxNumberOfSkippedGens = 0;
	_mutationProbability = 0;
	_wasProbabilitySet = false;

	_gensToSkipNow = 0;
	_currentlySkippedGens = 0;
}

void Mutator::setMutationProbability(double genMutationProbability)
{
	_mutationProbability = genMutationProbability;

	_maxNumberOfSkippedGens = floor(1/_mutationProbability) - 1;

	if(_maxNumberOfSkippedGens <= 0)
	{
		throw std::invalid_argument("genMutationProbability was set incorrecty");
	}

	setGensToSkipNow();
}

void Mutator::setGensToSkipNow()
{
	_gensToSkipNow = Random::Instance().getUniformlyDistributedDiscreteRandomQuantity(0,_maxNumberOfSkippedGens);
	_currentlySkippedGens = 0;
}
