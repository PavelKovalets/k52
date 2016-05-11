#include <k52/common/random.h>
#include <k52/optimization/genetic_algorithm.h>

#include <stdexcept>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <istream>
#include <iterator>
#include <algorithm>
#include <typeinfo>

#include "../objective_function_counter.h"

using ::std::vector;
using ::k52::common::Random;

namespace
{
const std::string kGeneticSettingsPrefix  ("genetic_algorithm.");
const std::string kElitizmPairsParameter  (kGeneticSettingsPrefix + "elitizm_pairs");
const std::string kPopulationSizeParameter(kGeneticSettingsPrefix + "population_size");
const std::string kCacheDataLimitInMegabytesParameter(kGeneticSettingsPrefix + "cache_data_limit_in_megabytes");
const std::string kFitnessStopCriteriaParameter (kGeneticSettingsPrefix + "fitness_stop_criteria");
const std::string kPopulationFileNameParameter  (kGeneticSettingsPrefix + "population_filename");
const std::string kMaxNumberOfGenerationsParameter(kGeneticSettingsPrefix + "maximum_number_of_generations");

// Some default values
const double kCacheDataLimitInMegabytes = 100;
const double kFitnessStopCriteria  = 10000000;
const std::string kPopulationFileName("");
}

namespace k52
{
namespace optimization
{

GeneticAlgorithm::shared_ptr GeneticAlgorithm::Create(const SettingsManager& settings_manager)
{
    GeneticAlgorithm::shared_ptr genetic_algorithm;

    throw std::runtime_error("Not implemented Create");
    //TODO find architectural sulution to inject interfaces (e.g. IMutator)
    //genetic_algorithm.reset(new GeneticAlgorithm(settings_manager.get<size_t>(kPopulationSizeParameter),
    //                                             settings_manager.get<size_t>(kElitizmPairsParameter),
    //                                             settings_manager.get<size_t>(kMaxNumberOfGenerationsParameter),
    //                                             settings_manager.get<double>(kCacheDataLimitInMegabytesParameter, kCacheDataLimitInMegabytes),
    //                                             settings_manager.get<double>(kFitnessStopCriteriaParameter, kFitnessStopCriteria),
    //                                             settings_manager.get<std::string>(kPopulationFileNameParameter, kPopulationFileName)));

    return genetic_algorithm;
}

GeneticAlgorithm::shared_ptr GeneticAlgorithm::Create(int population_size,
                                                      int elitism_pairs,
                                                      int max_number_of_generations,
                                                      IMutator::shared_ptr mutator,
                                                      double cache_data_limit_in_megabytes,
                                                      double fitness_stop_criteria,
                                                      std::string population_file_name)
{
    GeneticAlgorithm::shared_ptr genetic_algorithm;
    try
    {
        genetic_algorithm.reset(new GeneticAlgorithm(population_size, elitism_pairs, max_number_of_generations,
            mutator, cache_data_limit_in_megabytes, fitness_stop_criteria, population_file_name));
    }
    catch(std::exception& ex)
    {
        std::cerr << "Failed to create new instance of genetic algorithm : " << ex.what() << std::endl;
    }

    return genetic_algorithm;
}

GeneticAlgorithm::GeneticAlgorithm(
    int population_size,
    int elitism_pairs,
    int max_number_of_generations,
    IMutator::shared_ptr mutator,
    double cache_data_limit_in_megabytes,
    double fitness_stop_criteria,
    std::string population_file_name)
        :population_(0),
         population_statistics_(0),
         fitness_counter_(new ObjectiveFunctionCounter(cache_data_limit_in_megabytes))
{
    if(population_size%2!=0)
    {
        throw std::invalid_argument("Population_size must be even");
    }

    if(population_size<=0)
    {
        throw std::invalid_argument("population_size <= 0!");
    }

    if(max_number_of_generations<=0)
    {
        throw std::invalid_argument("max_number_of_generations <= 0!");
    }

    if (!mutator)
    {
        throw std::invalid_argument("mutator was not set.");
    }

    callback_function_ = NULL;
    elitism_pairs_ = elitism_pairs;
    population_size_ = population_size;
    mutator_ = mutator;
    fitness_stop_criteria_ = fitness_stop_criteria;
    max_number_of_generations_ = max_number_of_generations;
    population_file_name_ = population_file_name;
    invalid_chromosomes_ = 0;
    were_initial_parameters_set_ = false;
}

void GeneticAlgorithm::Optimize(const DiscreteObjectiveFunction &function_to_optimize,
    IDiscreteParameters* parameters_to_optimize,
    bool maximize)
{
    if(!maximize)
    {
        throw std::invalid_argument("GeneticAlgorithm currently can only maximize function.");
    }

    Initialize(parameters_to_optimize);

    if(!population_file_name_.empty())
    {
        ReadPopulationFromFile();
    }

    RunIterationsAndSetBestIndivid(function_to_optimize);

    parameters_to_optimize->SetFromChromosome(
        best_individ_->GetChromosome().begin(),
        best_individ_->GetChromosome().end() );
}

void GeneticAlgorithm::SetInitialParameters(std::vector<IDiscreteParameters::shared_ptr> initial_parameters)
{
    initial_parameters_ = std::vector<IDiscreteParameters::shared_ptr>(population_size_);

    for (std::size_t i = 0; i < population_size_; ++i)
    {
        initial_parameters_[i] = IDiscreteParameters::shared_ptr((initial_parameters[i])->Clone());
    }

    were_initial_parameters_set_ = true;
}

void GeneticAlgorithm::OnNextGenerationReadyConnect(NextGenerationReadyCallback callback_function)
{
    callback_function_ = callback_function;
}

GeneticAlgorithm* GeneticAlgorithm::Clone() const
{
    throw std::logic_error("Cloning is not implemented for GA");
}

std::string GeneticAlgorithm::get_name() const
{
    return "Genetic Algorithm";
}

#ifdef BUILD_WITH_MPI
void GeneticAlgorithm::Send(boost::mpi::communicator* communicator, int target) const
{
    throw std::logic_error("Send is not implemented for GA");
}

void GeneticAlgorithm::Receive(boost::mpi::communicator* communicator, int source)
{
    throw std::logic_error("Receive is not implemented for GA");
}
#endif

void GeneticAlgorithm::Initialize(const IDiscreteParameters* parameters_to_optimize)
{
    population_ = vector<Individual::shared_ptr>(population_size_);
    population_statistics_ = vector<IndividualStatistics>(population_size_);

    if (were_initial_parameters_set_)
    {
        ValidateInitialParameters(parameters_to_optimize);
    }

    for (std::size_t i = 0; i < population_size_; i++)
    {
        population_[i] = Individual::shared_ptr(new Individual());

        if (were_initial_parameters_set_)
        {
            population_[i]->Initialize(initial_parameters_[i].get());
        }
        else
        {
            population_[i]->Initialize(parameters_to_optimize);
            invalid_chromosomes_ += population_[i]->SetRandomChromosome();
        }
    }
    best_individ_ = Individual::shared_ptr(new Individual(parameters_to_optimize) );
}

void GeneticAlgorithm::ValidateInitialParameters(const IDiscreteParameters* parameters_to_optimize)
{
    if (initial_parameters_.size() != population_size_)
    {
        throw std::invalid_argument("Initial parameters must have same size as population.");
    }

    const std::type_info* parameters_to_optimize_type = &typeid(*parameters_to_optimize);

    for (std::size_t i = 0; i < population_size_; i++)
    {
        IParameters* parameters = initial_parameters_[i].get();
        const std::type_info* parameters_type = &typeid(*parameters);

        if ( (*parameters_type) != (*parameters_to_optimize_type) )
        {
            throw std::invalid_argument("Parameters to optimize must be of the same type as initial parameters.");
        }

        // check that all parameters have same class-wide settings (for chromosome to have same meaning and size)
        if (!initial_parameters_[i]->HasSameMetaParameters(parameters_to_optimize))
        {
            throw std::invalid_argument("Initial parameters have defferent chromosome representation. "
                "Check if their meta-parameters are equal to parameters_to_optimeze's.");
        }
    }
}

void GeneticAlgorithm::RunIterationsAndSetBestIndivid(const DiscreteObjectiveFunction &function_to_optimize)
{
    for (int n = 0; n < max_number_of_generations_; n++)
    {
        fitness_counter_->ObtainFitness(function_to_optimize, &population_);

        UpdateBestIndivid();

        if (callback_function_ != NULL)
        {
            ProcessStatistics(n);
        }

        fitness_counter_->ResetCacheHits();
        invalid_chromosomes_ = 0;

        if (best_individ_->get_fitness() >= fitness_stop_criteria_)
        {
            return;
        }

        GenerateNextPopulation();

        MutationContext mutation_context;
        mutation_context.current_generation = n;
        mutation_context.max_number_of_generations = max_number_of_generations_;

        Mutate(mutation_context);
    }
}

void GeneticAlgorithm::Mutate(const MutationContext& mutation_context)
{
    mutator_->ApplyNewMutationContext(mutation_context);

    for (std::size_t i = 0; i < population_size_; i++)
    {
        invalid_chromosomes_ += population_[i]->Mutate(mutator_);
    }
}

void GeneticAlgorithm::GenerateNextPopulation()
{
    double total_fitness = 0;

    vector<Individual::shared_ptr> sorted_population(population_size_);

    for(std::size_t i = 0; i < population_size_; i++)
    {
        total_fitness += population_[i]->get_fitness();
        population_[i]->ResetTimesChosenForCrossover();
        sorted_population[i] = population_[i];
    }
    sort(sorted_population.begin(), sorted_population.end(), GreaterFitness);
    vector<Individual::shared_ptr> next_population(population_size_);

    int elitism_ready = 0;
    for(std::size_t i = 0; i < population_size_; i+=2)
    {
        if(elitism_ready<elitism_pairs_)
        {
            next_population[i] = Individual::shared_ptr( new Individual( *(sorted_population[i]) ) );
            next_population[i+1] = Individual::shared_ptr( new Individual( *(sorted_population[i+1]) ) );
            //elitism
            elitism_ready++;
        }
        else
        {
            //crossover
            Individual::shared_ptr first_child, second_child;

            bool success = true;
            do
            {
                success = true;

                int first_parent_index = SelectRandomIndividualIndexForCrossover(total_fitness);
                int second_parent_index  = SelectRandomIndividualIndexForCrossover(total_fitness);

                first_child = Individual::shared_ptr( new Individual( *(population_[first_parent_index]) ) );
                second_child = Individual::shared_ptr( new Individual( *(population_[second_parent_index]) ) );

                population_[first_parent_index]->IncreaseTimesChosenForCrossover();
                population_[second_parent_index]->IncreaseTimesChosenForCrossover();

                success = first_child->Crossover(second_child.get());

                if(!success)
                {
                    invalid_chromosomes_ ++;
                }

            }while(!success);

            next_population[i] = first_child;
            next_population[i+1] = second_child;
        }
    }

    //TODO refactor - move all statistics logic to separate class
    GatherAllIndividualsStatistics();

    population_ = next_population;
}

void GeneticAlgorithm::UpdateBestIndivid()
{
    Individual::shared_ptr best_current_individ = population_[0];

    for (std::size_t i = 1; i < population_size_; i++)
    {
        if (best_current_individ->get_fitness() < population_[i]->get_fitness())
        {
            best_current_individ = population_[i];
        }
    }

    if ((!best_individ_->HasFitness()) || best_individ_->get_fitness() < best_current_individ->get_fitness())
    {
        best_individ_ = best_current_individ;
    }
}

int GeneticAlgorithm::SelectRandomIndividualIndexForCrossover(double total_fitness)
{
    double roulette_result = Random::Instance().GetBaseRandomQuantity() * total_fitness;

    double current = 0;

    for(std::size_t i = 0; i < population_size_; i++)
    {
        current += population_[i]->get_fitness();
        if(roulette_result <= current)
        {
            return i;
        }
    }

    //This point should be unreachable
    throw std::logic_error("Something wrong with fitness calculation. Possible < 0");
}

void GeneticAlgorithm::ProcessStatistics(int number_of_generation)
{
    std::list<std::string> files_to_save;
    std::list<IndividualStatistics> all_statistics;

    std::copy (population_statistics_.begin (), population_statistics_.end (), std::back_inserter (all_statistics));
    all_statistics.sort(IndividualStatistics::Greater);

    GenerationStatistics current_population_statistics(
        GetPopulationAveradgeFitness(),
        best_individ_->GetParametersAccordingToChromosome(),
        best_individ_->get_fitness(),
        number_of_generation,
        fitness_counter_->get_cache_hits(),
        invalid_chromosomes_,
        &files_to_save,
        all_statistics);

    FireNextGenerationReady(current_population_statistics);


    for(std::list<std::string>::iterator it = files_to_save.begin(); it != files_to_save.end(); ++it)
    {
        SavePopulationToFile(*it);
    }

    files_to_save.clear();
}

double GeneticAlgorithm::GetPopulationAveradgeFitness()
{
    double averadge = 0;
    for(std::size_t i = 0; i < population_size_; i++)
    {
        averadge += population_[i]->get_fitness();
    }
    averadge = averadge / population_size_;
    return averadge;
}

void GeneticAlgorithm::GatherAllIndividualsStatistics()
{
    for(std::size_t i = 0; i < population_size_; i++)
    {
        population_statistics_[i] = population_[i]->get_individual_statistics();
    }
}

void GeneticAlgorithm::FireNextGenerationReady(const GenerationStatistics& statistics)
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
    else
    {
        throw std::runtime_error("Unable to open file " + population_file_name_);
    }
    fin.close();
}

void GeneticAlgorithm::OutputPopulation(std::ostream& out)
{
    out << "Population_size: " << std::endl;
    out << population_.size() << std::endl;
    out << "Chromosome_size: " << std::endl;
    out << population_[0]->GetChromosome().size() << std::endl;
    for(size_t i = 0;i < population_.size();i++)
    {
        out << *population_[i];
    }
}

void GeneticAlgorithm::InputPopulation(std::ifstream & in)
{
    std::string info_string;
    std::size_t population_size = 0;
    std::size_t chromosome_size = 0;
    in >> info_string; //"Population_size: "
    in >> population_size;
    std::cout << info_string << population_size << std::endl;
    in >> info_string; //"Chromosome_size: "
    in >> chromosome_size;
    std::cout << info_string << chromosome_size << std::endl;
    if (population_size_ != population_size || chromosome_size != population_[0]->GetChromosome().size())
    {
        throw std::logic_error("Incorrect input file (maybe old settings - Population size, Chromosome size etc.)");
    }

    for(std::size_t i = 0;i < population_size; i++)
    {
        in >> *(population_[i]);
        if( !(population_[i])->IsValid() )
        {
            throw std::logic_error("The Individual read from file does not satisfy constraints. "
                                   "The file may be corrupted or used with wrong GA settings.");
        }
    }

    GatherAllIndividualsStatistics();
}

bool GeneticAlgorithm::GreaterFitness(Individual::shared_ptr first, Individual::shared_ptr second)
{
    return (first->get_fitness()) > (second->get_fitness());
}

}/* namespace optimization */
}/* namespace k52 */
