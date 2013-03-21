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

#include "Random.h"
#include "ObjectiveFunctionCounter.h"

using ::std::vector;

namespace k52
{
namespace optimize
{

GeneticAlgorithm::GeneticAlgorithm(
    int population_size,
    int elitism_pairs,
    int max_number_of_generations,
    bool use_fitness_value_caching,
    double fitness_stop_criteria,
    double mutation_probability,
    std::string population_file_name)
        :population_(0),
         population_statistics_(0),
         fitness_counter_(new ObjectiveFunctionCounter(use_fitness_value_caching))
{
    if(population_size%2!=0)
    {
        std::cout<<"population_size must be even!"<<std::endl;
        exit(-1);
    }

    if(population_size<=0)
    {
        std::cout<<"population_size <= 0!"<<std::endl;
        exit(-1);
    }

    if(max_number_of_generations<=0)
    {
        std::cout<<"max_number_of_generations <= 0!"<<std::endl;
        exit(-1);
    }

    callback_function_ = NULL;
    elitism_pairs_ = elitism_pairs;
    population_size_ = population_size;
    mutation_probability_ = mutation_probability;
    fitness_stop_criteria_ = fitness_stop_criteria;
    max_number_of_generations_ = max_number_of_generations;
    population_file_name_ = population_file_name;
    invalid_chromosomes_ = 0;
}

void GeneticAlgorithm::Optimize(const IObjectiveFunction &function_to_optimize, IParameters* parametrs_to_optimize)
{
    IDiscreteParameters* discrete_parameters = dynamic_cast<IDiscreteParameters*>(parametrs_to_optimize);
    if(discrete_parameters == NULL)
    {
        throw std::invalid_argument("GeneticAlgorithm currently can optimize only IDiscreteParameters.");
    }
    Initialize(discrete_parameters);

    if(!population_file_name_.empty())
    {
        ReadPopulationFromFile();
    }

    for (int n = 0; n < max_number_of_generations_; n++)
    {
        fitness_counter_->obtainFitness(&population_, function_to_optimize);

        Individual best_current_individ(population_[0]);

        for (int i = 1; i < population_size_; i++)
        {
            if (best_current_individ.get_fitness() < population_[i].get_fitness())
            {
                best_current_individ = population_[i];
            }
        }

        if( (!best_individ_.HasFitness()) ||  best_individ_.get_fitness() < best_current_individ.get_fitness())
        {
            best_individ_ = best_current_individ;
        }

        std::list<std::string> files_to_save;
        std::list<IndividualStatistics> all_statistics;

        std::copy (population_statistics_.begin (), population_statistics_.end (), std::back_inserter (all_statistics));
        all_statistics.sort(IndividualStatistics::Greater);

        GenerationStatistics current_population_statistics(
            GetPopulationAveradgeFitness(),
            best_individ_.GetParametersAccordingToChromosome(),
            best_individ_.get_fitness(),
            n,
            fitness_counter_->getCacheHits(),
            invalid_chromosomes_,
            &files_to_save,
            all_statistics);

        FireNextGenerationReady(current_population_statistics);

        for(std::list<std::string>::iterator it = files_to_save.begin(); it != files_to_save.end(); it++)
        {
            SavePopulationToFile(*it);
        }

        files_to_save.clear();

        fitness_counter_->resetCacheHits();
        invalid_chromosomes_ = 0;

        if(best_individ_.get_fitness() >= fitness_stop_criteria_)
        {
            discrete_parameters->SetFromChromosome(
                best_individ_.GetChromosome().begin(),
                best_individ_.GetChromosome().end() );
            return;
        }

        GenerateNextPopulation();
        Mutate();
    }

    discrete_parameters->SetFromChromosome(
        best_individ_.GetChromosome().begin(),
        best_individ_.GetChromosome().end() );

    return;
}

void GeneticAlgorithm::OnNextGenerationReadyConnect(NextGenerationReadyCallback callback_function)
{
    callback_function_ = callback_function;
}

void GeneticAlgorithm::Initialize(IDiscreteParameters* parametrs_to_optimize)
{
    population_ = vector<Individual>(population_size_);
    population_statistics_ = vector<IndividualStatistics>(population_size_);

    for(int i =0; i<population_size_; i++)
    {
        population_[i].Initialize(parametrs_to_optimize);
        invalid_chromosomes_ += population_[i].SetRandomChromosome();
    }
    best_individ_ = Individual(parametrs_to_optimize);
}

void GeneticAlgorithm::Mutate()
{
    for(int i =0; i<population_size_; i++)
    {
        invalid_chromosomes_ += population_[i].Mutate(mutation_probability_);
    }
}

void GeneticAlgorithm::GenerateNextPopulation()
{
    double total_fitness = 0;

    vector<Individual*> sorted_population(population_size_);

    for(int i =0; i<population_size_; i++)
    {
        total_fitness += population_[i].get_fitness();
        population_[i].ResetTimesChosenForCrossover();
        sorted_population[i] = &(population_[i]);
    }
    sort(sorted_population.begin(), sorted_population.end(), GreaterFitness);
    vector<Individual> next_population(population_size_);

    int elitism_ready = 0;
    for(int i =0; i<population_size_; i+=2)
    {
        if(elitism_ready<elitism_pairs_)
        {
            next_population[i] = *(sorted_population[i]);
            next_population[i+1] = *(sorted_population[i+1]);
            //elitism
            elitism_ready++;
        }
        else
        {
            //crossover
            Individual first_parent, second_parent;

            bool success = true;
            do
            {
                success = true;

                int first_parent_index = SelectRandomIndividualIndexForCrossover(total_fitness);
                int second_parent_index  = SelectRandomIndividualIndexForCrossover(total_fitness);

                first_parent = population_[first_parent_index];
                second_parent = population_[second_parent_index];

                population_[first_parent_index].IncreaseTimesChosenForCrossover();
                population_[second_parent_index].IncreaseTimesChosenForCrossover();

                success = first_parent.Crossover(&second_parent);

                if(!success)
                {
                    invalid_chromosomes_ ++;
                }

            }while(!success);

            next_population[i] = first_parent; // first Child
            next_population[i+1] = second_parent; // second Child
        }
    }

    GatherAllIndividualsStatistics();

    population_ = next_population;
}

int GeneticAlgorithm::SelectRandomIndividualIndexForCrossover(double total_fitness)
{
    double roulette_result = Random::Instance().getBaseRandomQuantity() * total_fitness;

    double current = 0;

    for(int i =0; i<population_size_; i++)
    {
        current += population_[i].get_fitness();
        if(roulette_result <= current)
        {
            return i;
        }
    }

    //This point should be unreachable
    throw std::logic_error("Something wrong with fitness calculation. Possible < 0");
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

void GeneticAlgorithm::GatherAllIndividualsStatistics()
{
    for(int i = 0; i < population_size_; i++)
    {
        population_statistics_[i] = population_[i].get_individual_statistics();
    }
}

void GeneticAlgorithm::FireNextGenerationReady(GenerationStatistics statistics)
{
    if(callback_function_ != NULL)
    {
        callback_function_(statistics);
    }
}

void GeneticAlgorithm::SavePopulationToFile(std::string file_name)
{
    std::ofstream fout(file_name.c_str());
    if(fout)
    {
        OutputPopulation(fout);
    }
    fout.close();
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

void GeneticAlgorithm::OutputPopulation(std::ostream& out)
{
    out << "Population_size: " << std::endl;
    out << population_.size() << std::endl;
    out << "Chromosome_size: " << std::endl;
    out << population_[0].GetChromosome().size() << std::endl;
    for(size_t i = 0;i < population_.size();i++){
        out << population_[i];
    }
}

void GeneticAlgorithm::InputPopulation(std::ifstream & in)
{
    std::string s;
    int population_size = 0;
    size_t chromosome_size = 0;
    in >> s; //"Population_size: "
    in >> population_size;
    std::cout << population_size << std::endl;
    in >> s; //"Chromosome_size: "
    in >> chromosome_size;
    std::cout << chromosome_size << std::endl;
    if(population_size_ != population_size || chromosome_size != population_[0].GetChromosome().size()){
        throw std::logic_error("Incorrect input file (maybe old settings - Population size, Chromosome size etc.)");
    }
    for(int i = 0;i < population_size;i++){
        in >> population_[i];
    }
}

bool GeneticAlgorithm::GreaterFitness(const Individual* first, const Individual* second)
{
    return (first->get_fitness()) > (second->get_fitness());
}

}/* namespace optimize */
}/* namespace k52 */
