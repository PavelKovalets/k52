/*
 * GeneticAlgorithm.cpp
 *
 *  Created on: Jan 29, 2012
 *      Author: feanor
 */

#include "ObjectiveFunctionCounter.h"
#include "Random.h"
#include <optimize/genetic_algorithm.h>
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

namespace k52
{
namespace optimize
{

GeneticAlgorithm::GeneticAlgorithm(
		int populationSize,
		int elitismPairs,
		int maxNumberOfGenerations,
		bool useFitnessValueCaching,
		double fitnessStopCriteria,
		double mutationProbability,
		std::string populationFileName)
		: population_(0), population_statistics_(0), fitness_counter_(new ObjectiveFunctionCounter(useFitnessValueCaching))
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

	callback_function_ = NULL;

	elitism_pairs_ = elitismPairs;
	fitness_stop_criteria_ = fitnessStopCriteria;
	mutation_probability_ = mutationProbability;
	max_number_of_generations_ = maxNumberOfGenerations;

	population_size_ = populationSize;
	invalid_chromosomes_ = 0;
	population_file_name_ = populationFileName;
}

void GeneticAlgorithm::FireNextGenerationReady(GenerationStatistics statistics)
{
	if(callback_function_ != NULL)
	{
		callback_function_(statistics);
	}
}

bool GeneticAlgorithm::GreaterFitness(const Individual* first, const Individual* second)
{
	return (first->get_fitness()) > (second->get_fitness());
}

void GeneticAlgorithm::GenerateNextPopulation()
{
	double totalFitness = 0;

	vector<Individual*> sortedPopulation(population_size_);
	
	for(int i =0; i<population_size_; i++)
	{
		totalFitness += population_[i].get_fitness();
		population_[i].ResetTimesChosenForCrossover();
		sortedPopulation[i] = &(population_[i]);
	}
	sort(sortedPopulation.begin(), sortedPopulation.end(), GreaterFitness);
	vector<Individual> nextPopulation(population_size_);

	int elitismReady = 0;
	for(int i =0; i<population_size_; i+=2)
	{
		if(elitismReady<elitism_pairs_)
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

				int firstParentIndex = SelectRandomIndividualIndexForCrossover(totalFitness);
				int secondParentIndex  = SelectRandomIndividualIndexForCrossover(totalFitness);

				firstParent = population_[firstParentIndex];
				secondParent = population_[secondParentIndex];

				population_[firstParentIndex].IncreaseTimesChosenForCrossover();
				population_[secondParentIndex].IncreaseTimesChosenForCrossover();
			
				success = firstParent.Crossover(&secondParent);
			
				if(!success)
				{
					invalid_chromosomes_ ++;
				}

			}while(!success);

			nextPopulation[i] = firstParent; // first Child
			nextPopulation[i+1] = secondParent; // second Child
		}
	}

	GatherAllIndividualsStatistics();

	population_ = nextPopulation;
}

int GeneticAlgorithm::SelectRandomIndividualIndexForCrossover(double totalFitness)
{
	double rouletteResult = Random::Instance().getBaseRandomQuantity() * totalFitness;

	double current = 0;

	for(int i =0; i<population_size_; i++)
	{
		current += population_[i].get_fitness();
		if(rouletteResult <= current)
		{
			return i;
		}
	}

	//This point should be unreachable
	throw std::logic_error("Something wrong with fitness calculation. Possible < 0");
}

void GeneticAlgorithm::Mutate()
{
	for(int i =0; i<population_size_; i++)
	{
		invalid_chromosomes_ += population_[i].Mutate(mutation_probability_);
	}
}

void GeneticAlgorithm::Initialize(IDiscreteParameters* parametrsToOptimize)
{
	population_ = vector<Individual>(population_size_);
	population_statistics_ = vector<IndividualStatistics>(population_size_);

	for(int i =0; i<population_size_; i++)
	{
		population_[i].Initialize(parametrsToOptimize);
		invalid_chromosomes_ += population_[i].SetRandomChromosome();
	}
	best_individ_ = Individual(parametrsToOptimize);
}

double GeneticAlgorithm::GetPopulationAveradgeFitness()
{
	double averadge = 0;
	for(int i =0; i<population_size_; i++)
	{
		averadge += population_[i].get_fitness();
	}
	averadge = averadge / population_size_;
	return averadge;
}

void GeneticAlgorithm::OnNextGenerationReadyConnect(NextGenerationReadyCallback callbackFunction)
{
	callback_function_ = callbackFunction;
}

void GeneticAlgorithm::OutputPopulation(std::ostream & out)
{
    out << "Population_size: " << std::endl;
    out << population_.size() << std::endl;
    out << "Chromosome_size: " << std::endl;
    out << population_[0].GetChromosome().size() << std::endl;
    for(size_t i = 0;i < population_.size();i++){
        out << population_[i];
    }
}

void GeneticAlgorithm::SavePopulationToFile(std::string fileName)
{
	std::ofstream fout(fileName.c_str());
	if(fout)
	{
		OutputPopulation(fout);
	}
	fout.close();
}

void GeneticAlgorithm::InputPopulation(std::ifstream & in)
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
    if(population_size_ != populationSize || chromosomeSize != population_[0].GetChromosome().size()){
		throw std::logic_error("Incorrect input file (maybe old settings - Population size, Chromosome size etc.)");
    }
    for(int i = 0;i < populationSize;i++){
        in >> population_[i];
    }
}

void GeneticAlgorithm::ReadPopulationFromFile()
{
	std::ifstream fin(population_file_name_.c_str());
	if(fin)
	{
		InputPopulation(fin);
	}
	fin.close();
}

void GeneticAlgorithm::Optimize(const IObjectiveFunction &function_to_optimize, IParameters* parametrs_to_optimize)
{
	IDiscreteParameters* discreteParameters = dynamic_cast<IDiscreteParameters*>(parametrs_to_optimize);

	Initialize(discreteParameters);
	if(!population_file_name_.empty())
	{
		ReadPopulationFromFile();
	}
	for (int n = 0; n < max_number_of_generations_; n++)
	{
		fitness_counter_->obtainFitness(&population_, function_to_optimize);

		Individual bestCurrentIndivid(population_[0]);

		for (int i = 1; i < population_size_; i++)
		{
			if (bestCurrentIndivid.get_fitness() < population_[i].get_fitness())
			{
				bestCurrentIndivid = population_[i];
			}
		}

		if( (!best_individ_.HasFitness()) ||  best_individ_.get_fitness() < bestCurrentIndivid.get_fitness())
		{
			best_individ_ = bestCurrentIndivid;
		}

		std::list<std::string> filesToSave;
		std::list<IndividualStatistics> allStatistics;

		std::copy (population_statistics_.begin (), population_statistics_.end (), std::back_inserter (allStatistics));
		allStatistics.sort(IndividualStatistics::greater);

		GenerationStatistics currentPopulationStatistics(GetPopulationAveradgeFitness(),
				best_individ_.GetParametersAccordingToChromosome(),
				best_individ_.get_fitness(),
				n,
				fitness_counter_->getCacheHits(),
				invalid_chromosomes_,
				&filesToSave,
				allStatistics);

		FireNextGenerationReady(currentPopulationStatistics);

		for(std::list<std::string>::iterator it = filesToSave.begin(); it != filesToSave.end(); it++)
		{
			SavePopulationToFile(*it);
		}

		filesToSave.clear();

		fitness_counter_->resetCacheHits();
		invalid_chromosomes_ = 0;

		if(best_individ_.get_fitness() >= fitness_stop_criteria_)
		{
			discreteParameters->SetFromChromosome(
					best_individ_.GetChromosome().begin(),
					best_individ_.GetChromosome().end() );
			return;
		}

		GenerateNextPopulation();
		Mutate();
	}

	discreteParameters->SetFromChromosome(
						best_individ_.GetChromosome().begin(),
						best_individ_.GetChromosome().end() );

	return;
}

void GeneticAlgorithm::GatherAllIndividualsStatistics()
{
	for(int i = 0; i < population_size_; i++)
	{
		population_statistics_[i] = population_[i].get_individual_statistics();
	}
}

}/* namespace optimize */
}/* namespace k52 */
