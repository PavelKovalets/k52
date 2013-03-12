/*
 * GeneticAlgorithm.cpp
 *
 *  Created on: Jan 29, 2012
 *      Author: feanor
 */

#include "ObjectiveFunctionCounter.h"
#include "Random.h"
#include <optimize/GeneticAlgorithm.h>
#include <stdexcept>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <istream>
#include <iterator>
#include <algorithm>

using ::std::vector;

GeneticAlgorithm::GeneticAlgorithm(
		int populationSize,
		int elitismPairs,
		int maxNumberOfGenerations,
		int numberOfThreads,
		bool useFitnessValueCaching,
		double fitnessStopCriteria,
		double mutationProbability,
		std::string populationFileName)
		: _population(0), _populationStatistics(0), _fitnessCounter(new ObjectiveFunctionCounter(numberOfThreads, useFitnessValueCaching))
{
	if(populationSize%2!=0)
	{
		std::cout<<"populationSize must be even!"<<std::endl;
		exit(-1);
	}

	if(maxNumberOfGenerations<=0)
	{
		std::cout<<"maxNumberOfGenerations <= 0!"<<std::endl;
		exit(-1);
	}

	if(maxNumberOfGenerations<=0)
	{
		std::cout<<"maxNumberOfGenerations <= 0!"<<std::endl;
		exit(-1);
	}

	_callbackFunction = NULL;

	_elitismPairs = elitismPairs;
	_fitnessStopCriteria = fitnessStopCriteria;
	_mutationProbability = mutationProbability;
	_maxNumberOfGenerations = maxNumberOfGenerations;

	_populationSize = populationSize;
	_invalidChromosomes = 0;
	_populationFileName = populationFileName;
}

void GeneticAlgorithm::fireNextGenerationReady(GenerationStatistics statistics)
{
	if(_callbackFunction != NULL)
	{
		_callbackFunction(statistics);
	}
}

bool GeneticAlgorithm::greaterFitness(const Individual* first, const Individual* second)
{
	return (first->getFitness()) > (second->getFitness());
}

void GeneticAlgorithm::generateNextPopulation()
{
	double totalFitness = 0;

	vector<Individual*> sortedPopulation(_populationSize);
	
	for(int i =0; i<_populationSize; i++)
	{
		totalFitness += _population[i].getFitness();
		_population[i].resetTimesChosenForCrossover();
		sortedPopulation[i] = &(_population[i]);
	}
	sort(sortedPopulation.begin(), sortedPopulation.end(), greaterFitness);
	vector<Individual> nextPopulation(_populationSize);

	int elitismReady = 0;
	for(int i =0; i<_populationSize; i+=2)
	{
		if(elitismReady<_elitismPairs)
		{
			nextPopulation[i] = *(sortedPopulation[i]);
			nextPopulation[i+1] = *(sortedPopulation[i+1]);
			//elitism
			elitismReady++;
		}
		else
		{
			//crossover
			Individual firstParent, secondParent;

			bool success = true;

			do
			{
				success = true;

				int firstParentIndex = selectRandomIndividualIndexForCrossover(totalFitness);
				int secondParentIndex  = selectRandomIndividualIndexForCrossover(totalFitness);

				firstParent = _population[firstParentIndex];
				secondParent = _population[secondParentIndex];

				_population[firstParentIndex].increaseTimesChosenForCrossover();
				_population[secondParentIndex].increaseTimesChosenForCrossover();
			
				success = firstParent.crossover(&secondParent);
			
				if(!success)
				{
					_invalidChromosomes ++;
				}

			}while(!success);

			nextPopulation[i] = firstParent; // first Child
			nextPopulation[i+1] = secondParent; // second Child
		}
	}

	gatherAllIndividualsStatistics();

	_population = nextPopulation;
}

int GeneticAlgorithm::selectRandomIndividualIndexForCrossover(double totalFitness)
{
	double rouletteResult = Random::Instance().getBaseRandomQuantity() * totalFitness;

	double current = 0;

	for(int i =0; i<_populationSize; i++)
	{
		current += _population[i].getFitness();
		if(rouletteResult <= current)
		{
			return i;
		}
	}

	//This point should be unreachable
	throw std::logic_error("Something wrong with fitness calculation. Possible < 0");
}

void GeneticAlgorithm::mutate()
{
	for(int i =0; i<_populationSize; i++)
	{
		_invalidChromosomes += _population[i].mutate(_mutationProbability);
	}
}

void GeneticAlgorithm::initialize(IDiscreteParameters* parametrsToOptimize)
{
	_population = vector<Individual>(_populationSize);
	_populationStatistics = vector<IndividualStatistics>(_populationSize);

	for(int i =0; i<_populationSize; i++)
	{
		_population[i].initialize(parametrsToOptimize);
		_invalidChromosomes += _population[i].setRandomChromosome();
	}
	_bestIndivid = Individual(parametrsToOptimize);
}

double GeneticAlgorithm::getPopulationAveradgeFitness()
{
	double averadge = 0;
	for(int i =0; i<_populationSize; i++)
	{
		averadge += _population[i].getFitness();
	}
	averadge = averadge / _populationSize;
	return averadge;
}

void GeneticAlgorithm::onNextGenerationReadyConnect(NextGenerationReadyCallback callbackFunction)
{
	_callbackFunction = callbackFunction;
}

void GeneticAlgorithm::outputPopulation(std::ostream & out)
{
    out << "Population_size: " << std::endl;
    out << _population.size() << std::endl;
    out << "Chromosome_size: " << std::endl;
    out << _population[0].getChromosome().size() << std::endl;
    for(size_t i = 0;i < _population.size();i++){
        out << _population[i];
    }
}

void GeneticAlgorithm::savePopulationToFile(std::string fileName)
{
	std::ofstream fout(fileName.c_str());
	if(fout)
	{
		outputPopulation(fout);
	}
	fout.close();
}

void GeneticAlgorithm::inputPopulation(std::ifstream & in)
{
    std::string s;
    int populationSize = 0;
    size_t chromosomeSize = 0;
    in >> s; //"Population_size: "
    in >> populationSize;
    std::cout << populationSize << std::endl;
    in >> s; //"Chromosome_size: "
    in >> chromosomeSize;
    std::cout << chromosomeSize << std::endl;
    if(_populationSize != populationSize || chromosomeSize != _population[0].getChromosome().size()){
		throw std::logic_error("Incorrect input file (maybe old settings - Population size, Chromosome size etc.)");
    }
    for(int i = 0;i < populationSize;i++){
        in >> _population[i];
    }
}

void GeneticAlgorithm::readPopulationFromFile()
{
	std::ifstream fin(_populationFileName.c_str());
	if(fin)
	{
		inputPopulation(fin);
	}
	fin.close();
}

void GeneticAlgorithm::optimize(IParameters* parametrsToOptimize, const IObjectiveFunction &functionToOptimize)
{
	IDiscreteParameters* discreteParameters = dynamic_cast<IDiscreteParameters*>(parametrsToOptimize);

	initialize(discreteParameters);
	if(!_populationFileName.empty())
	{
		readPopulationFromFile();
	}
	for (int n = 0; n < _maxNumberOfGenerations; n++)
	{
		_fitnessCounter->obtainFitness(&_population, functionToOptimize);

		Individual bestCurrentIndivid(_population[0]);

		for (int i = 1; i < _populationSize; i++)
		{
			if (bestCurrentIndivid.getFitness() < _population[i].getFitness())
			{
				bestCurrentIndivid = _population[i];
			}
		}

		if( (!_bestIndivid.hasFitness()) ||  _bestIndivid.getFitness() < bestCurrentIndivid.getFitness())
		{
			_bestIndivid = bestCurrentIndivid;
		}

		list<std::string> filesToSave;
		list<IndividualStatistics> allStatistics;

		std::copy (_populationStatistics.begin (), _populationStatistics.end (), std::back_inserter (allStatistics));
		allStatistics.sort(IndividualStatistics::greater);

		GenerationStatistics currentPopulationStatistics(getPopulationAveradgeFitness(),
				_bestIndivid.getParametersAccordingToChromosome(),
				_bestIndivid.getFitness(),
				n,
				_fitnessCounter->getCacheHits(),
				_invalidChromosomes,
				&filesToSave,
				allStatistics);

		fireNextGenerationReady(currentPopulationStatistics);

		for(list<std::string>::iterator it = filesToSave.begin(); it != filesToSave.end(); it++)
		{
			savePopulationToFile(*it);
		}

		filesToSave.clear();

		_fitnessCounter->resetCacheHits();
		_invalidChromosomes = 0;

		if(_bestIndivid.getFitness() >= _fitnessStopCriteria)
		{
			discreteParameters->setFromChromosome(
					_bestIndivid.getChromosome().begin(),
					_bestIndivid.getChromosome().end() );
			return;
		}

		generateNextPopulation();
		mutate();
	}

	discreteParameters->setFromChromosome(
						_bestIndivid.getChromosome().begin(),
						_bestIndivid.getChromosome().end() );

	return;
}

void GeneticAlgorithm::gatherAllIndividualsStatistics()
{
	for(int i = 0; i < _populationSize; i++)
	{
		_populationStatistics[i] = _population[i].getIndividualStatistics();
	}
}

