/*
 * Individual.cpp
 *
 *  Created on: Jan 30, 2012
 *      Author: feanor
 */

#include <optimize/Individual.h>
#include "Random.h"
#include "Mutator.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <istream>

using ::std::vector;

namespace k52
{
namespace optimize
{

void Individual::boolCrossover(vector<bool> *first, vector<bool> *second)
{
	if(first->size() != second->size())
	{
		throw std::invalid_argument("For crossover chromosomes must have same size");
	}

	int crossoverPoint = Random::Instance().getUniformlyDistributedDiscreteRandomQuantity(0, first->size()-1);

	for(size_t i = crossoverPoint; i < first->size(); i++)
	{
		bool firstI = (*first)[i];
		if(firstI != (*second)[i])
		{
			(*first)[i] = !firstI;
			(*second)[i] = firstI;
		}
	}
}

int Individual::setRandomChromosome()
{
	_initializationChecker.initializationCheck();

	_hasFitness = false;

	int invalidChromosomes = 0;

	bool success = true;
	do
	{
		success = true;

		Random::Instance().setRandomBoolVector(&_chromosome);

		this->setParametersAccordingToChromosome();

		success = this->_parametersStorage->checkConstraints();

		if(!success)
		{
			invalidChromosomes++;
		}
		
	}while(!success);
	return invalidChromosomes;
}

int Individual::mutate(double genMutationProbability)
{
	_initializationChecker.initializationCheck();

	//TODO check if Individual has changed
	_hasFitness = false;

	int invalidChromosomes = 0;

	bool success = true;
	do
	{
		success = true;

		Mutator::Instance().mutateBoolArray(genMutationProbability, &_chromosome);

		this->setParametersAccordingToChromosome();

		success = this->_parametersStorage->checkConstraints();

		if(!success)
		{
			invalidChromosomes++;
		}
	}while(!success);
	return invalidChromosomes;
}

bool Individual::crossover(Individual* another)
{
	_initializationChecker.initializationCheck();

	//TODO check if Individual has changed
	another->_hasFitness = false;
	this->_hasFitness = false;

	boolCrossover(&(this->_chromosome), &(another->_chromosome));

	this->setParametersAccordingToChromosome();
	another->setParametersAccordingToChromosome();

	if( ( !this->_parametersStorage->checkConstraints() ) || ( !another->_parametersStorage->checkConstraints() ) )
	{
		return false;
	}
	else
	{
		return true;
	}
}

const IDiscreteParameters* const Individual::getParametersAccordingToChromosome() const
{
	_initializationChecker.initializationCheck();

	//TODO FIX do not return ptr from shared_ptr - maybe change return type to shared_ptr
	return _parametersStorage.get();
}

const vector<bool>& Individual:: getChromosome() const
{
	_initializationChecker.initializationCheck();
	return _chromosome;
}

void Individual::setParametersAccordingToChromosome()
{
	_initializationChecker.initializationCheck();

	_parametersStorage->setFromChromosome(_chromosome.begin(), _chromosome.end());
}

void Individual::initialize(const IDiscreteParameters* const parameters)
{
	_initializationChecker.setInitialized();

	_parametersStorage = IDiscreteParameters::shared_ptr(parameters->clone());
	_chromosome = vector<bool> ( _parametersStorage->getChromosomeSize() );

	_hasFitness = false;
	_timesChosenForCrossover = 0;
}

Individual::Individual()
	: _parametersStorage(), _initializationChecker()
{
}


Individual::Individual(const IDiscreteParameters* const parameters)
	: _parametersStorage(), _initializationChecker()
{
	initialize(parameters);
}

Individual::Individual(const Individual& a)
	: _parametersStorage()
{
	*this = a;
}

Individual& Individual::operator=(const Individual & a)
{
	if (this != &a) // protect against invalid self-assignment
	{
		if(a._parametersStorage != NULL)
		{
			_parametersStorage = IDiscreteParameters::shared_ptr( a._parametersStorage->clone() );
		}

		_chromosome = a._chromosome;
		_initializationChecker = a._initializationChecker;
		_fitness = a._fitness;
		_hasFitness = a._hasFitness;
		_timesChosenForCrossover = a._timesChosenForCrossover;
	}
	// by convention, always return *this
	return *this;
}

double Individual::getFitness() const
{
	checkForHavingFitness();
    return _fitness;
}

bool Individual::hasFitness() const
{
    return _hasFitness;
}

void Individual::setFitness(double fitness)
{
    _fitness = fitness;
    _hasFitness = true;
}

void Individual::checkForHavingFitness() const
{
	if(!_hasFitness)
	{
		throw std::logic_error("Fitness must be counted before this operation");
	}
}

IndividualStatistics Individual::getIndividualStatistics() const
{
	IndividualStatistics statistics;

	statistics.Fitness = getFitness();
	statistics.TimesChosenForCrossover = getTimesChosenForCrossover();

	return statistics;
}

int Individual::getTimesChosenForCrossover() const
{
	return _timesChosenForCrossover;
}

void Individual::increaseTimesChosenForCrossover()
{
	_timesChosenForCrossover++;
}

void Individual::resetTimesChosenForCrossover()
{
	_timesChosenForCrossover = 0;
}

std::ostream& operator<< (std::ostream& out, const Individual& individual)
{
	out<<"Chromosome:\t";
	const vector<bool>& chromosome = individual.getChromosome();
	for(size_t i=0; i<chromosome.size(); i++)
	{
		out<< (chromosome[i] ? '1' : '0');
	}
	out<<"\tFitness:\t"<<individual.getFitness()<<std::endl;
	return out;
}

//TODO for in>>fitness; --???
#include <iostream>

std::istream& operator>> (std::istream& in, Individual& individual)
{
	std::string s, chromosome;
	double fitness = 0;
	in>>s;//"Chromosome:\t"
	in>>chromosome;
	in>>s;//"\tFitness:\t"
	in>>fitness;

	if(chromosome.size() != individual.getChromosome().size())
	{
		throw std::logic_error("Attempt to read chromosome of inappropriate size");
	}

	vector<bool> newChromosome(chromosome.size());

	for(size_t i=0; i < chromosome.size(); i++)
	{
		if(chromosome[i] == '1')
		{
			newChromosome[i] = true;
		}
		else if(chromosome[i] == '0')
		{
			newChromosome[i] = false;
		}
		else
		{
			throw std::logic_error("Attempt to read chromosome with invalid  format");
		}
	}

	individual._chromosome = newChromosome;
	individual.setFitness(fitness);

	return in;
}

}/* namespace optimize */
}/* namespace k52 */
