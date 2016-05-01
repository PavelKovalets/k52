#include <k52/common/random.h>
#include <k52/optimization/individual.h>

#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <istream>
//TODO for in>>fitness; --???
#include <iostream>
#include <stdexcept>

#include <k52/optimization/i_mutator.h>

using ::k52::common::Random;

namespace k52
{
namespace optimization
{

Individual::Individual()
    : initialization_checker_()
    , parameters_()
    , times_chosen_for_crossover_(0)
    , has_fitness_(false), fitness_(0)
{
}

Individual::Individual(const IDiscreteParameters* const parameters)
    : initialization_checker_()
    , parameters_(), fitness_(0)
{
    Initialize(parameters);
}

Individual::Individual(const Individual& a)
    : parameters_()
{
    *this = a;
}

Individual& Individual::operator=(const Individual & a)
{
    if (this != &a) // protect against invalid self-assignment
    {
        if(a.parameters_ != NULL)
        {
            parameters_ = IDiscreteParameters::shared_ptr( a.parameters_->Clone() );
        }

        chromosome_ = a.chromosome_;
        initialization_checker_ = a.initialization_checker_;
        fitness_ = a.fitness_;
        has_fitness_ = a.has_fitness_;
        times_chosen_for_crossover_ = a.times_chosen_for_crossover_;
    }
    // by convention, always return *this
    return *this;
}

void Individual::Initialize(const IDiscreteParameters* const parameters)
{
    parameters_ = IDiscreteParameters::shared_ptr(parameters->Clone());
    chromosome_ = ChromosomeType ( parameters_->GetChromosomeSize() );
    parameters->SetChromosome(chromosome_.begin(), chromosome_.end());

    has_fitness_ = false;
    times_chosen_for_crossover_ = 0;

    initialization_checker_.SetInitialized();
}

const IDiscreteParameters* const Individual::GetParametersAccordingToChromosome() const
{
    initialization_checker_.InitializationCheck();

    //TODO FIX do not return ptr from shared_ptr - maybe change return type to shared_ptr
    return parameters_.get();
}

const ChromosomeType& Individual:: GetChromosome() const
{
    initialization_checker_.InitializationCheck();
    return chromosome_;
}

int Individual::SetRandomChromosome()
{
    initialization_checker_.InitializationCheck();

    has_fitness_ = false;
    int invalid_chromosomes = 0;

    bool success = true;
    do
    {
        success = true;

        for (ChromosomeType::iterator it = chromosome_.begin(); it != chromosome_.end(); ++it)
        {
            *it = Random::Instance().GetRandomBool();
        }

        this->SetParametersAccordingToChromosome();
        success = this->parameters_->CheckConstraints();

        if(!success)
        {
            invalid_chromosomes++;
        }
    }while(!success);

    return invalid_chromosomes;
}

bool Individual::Crossover(Individual* another)
{
    initialization_checker_.InitializationCheck();

    //TODO check if Individual has changed
    another->has_fitness_ = false;
    this->has_fitness_ = false;

    BoolCrossover(&(this->chromosome_), &(another->chromosome_));

    this->SetParametersAccordingToChromosome();
    another->SetParametersAccordingToChromosome();

    if( ( !this->parameters_->CheckConstraints() ) || ( !another->parameters_->CheckConstraints() ) )
    {
        return false;
    }
    else
    {
        return true;
    }
}

int Individual::Mutate(IMutator::shared_ptr mutator)
{
    initialization_checker_.InitializationCheck();

    has_fitness_ = false;
    int invalid_chromosomes = 0;

    bool success = true;
    do
    {
        success = true;

        mutator->MutateChromosome(&chromosome_);
        this->SetParametersAccordingToChromosome();
        success = this->parameters_->CheckConstraints();

        if (!success)
        {
            invalid_chromosomes++;
        }
    } while (!success);

    return invalid_chromosomes;
}

bool Individual::HasFitness() const
{
    return has_fitness_;
}

void Individual::IncreaseTimesChosenForCrossover()
{
    times_chosen_for_crossover_++;
}

void Individual::ResetTimesChosenForCrossover()
{
    times_chosen_for_crossover_ = 0;
}

int Individual::get_times_chosen_for_crossover() const
{
    return times_chosen_for_crossover_;
}

double Individual::get_fitness() const
{
    CheckForHavingFitness();
    return fitness_;
}

void Individual::set_fitness(double fitness)
{
    if(fitness < 0)
    {
        throw std::logic_error("Currently fitness must be >= 0!");
    }

    fitness_ = fitness;
    has_fitness_ = true;
}

bool Individual::IsValid() const
{
    initialization_checker_.InitializationCheck();

    return parameters_->CheckConstraints();
}

IndividualStatistics Individual::get_individual_statistics() const
{
    IndividualStatistics statistics;

    statistics.fitness = get_fitness();
    statistics.times_chosen_for_crossover = get_times_chosen_for_crossover();

    return statistics;
}

void Individual::CheckForHavingFitness() const
{
    if(!has_fitness_)
    {
        throw std::logic_error("Fitness must be counted before this operation");
    }
}

void Individual::SetParametersAccordingToChromosome()
{
    initialization_checker_.InitializationCheck();

    parameters_->SetFromChromosome(chromosome_.begin(), chromosome_.end());
}

void Individual::BoolCrossover(ChromosomeType *first, ChromosomeType *second)
{
    if(first->size() != second->size())
    {
        throw std::invalid_argument("For crossover chromosomes must have same size");
    }

    int crossover_point = Random::Instance().GetUniformlyDistributedDiscreteRandomQuantity(0, first->size()-1);

    for(size_t i = crossover_point; i < first->size(); i++)
    {
        bool firstI = (*first)[i];
        if(firstI != (*second)[i])
        {
            (*first)[i] = !firstI;
            (*second)[i] = firstI;
        }
    }
}

std::ostream& operator<< (std::ostream& out, const Individual& individual)
{
    out<<"Chromosome:\t";
    const ChromosomeType& chromosome = individual.GetChromosome();
    for(size_t i=0; i<chromosome.size(); i++)
    {
        out<< (chromosome[i] ? '1' : '0');
    }
    out<<"\tFitness:\t"<<individual.get_fitness()<<std::endl;
    return out;
}

std::istream& operator>> (std::istream& in, Individual& individual)
{
    std::string s, chromosome;
    double fitness = 0;
    in>>s;//"Chromosome:\t"
    in>>chromosome;
    in>>s;//"\tFitness:\t"
    in>>fitness;

    size_t chromosomeSize = chromosome.size();

    if(chromosomeSize != individual.GetChromosome().size())
    {
        throw std::logic_error("Attempt to read chromosome of inappropriate size");
    }

    ChromosomeType new_chromosome(chromosomeSize);

    for(size_t i=0; i < chromosomeSize; i++)
    {
        if(chromosome[i] == '1')
        {
            new_chromosome[i] = true;
        }
        else if(chromosome[i] == '0')
        {
            new_chromosome[i] = false;
        }
        else
        {
            throw std::logic_error("Attempt to read chromosome with invalid  format");
        }
    }

    individual.chromosome_ = new_chromosome;
    individual.set_fitness(fitness);
    individual.SetParametersAccordingToChromosome();

    return in;
}

}/* namespace optimization */
}/* namespace k52 */
