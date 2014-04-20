#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <ostream>

#include <k52/optimization/params/i_parameters.h>
#include <k52/optimization/initialization_checker.h>
#include <k52/optimization/individual_statistics.h>
#include <k52/optimization/params/discrete_parameters.h>

namespace k52
{
namespace optimization
{

//TODO make private - see field in GA class

/**
@class Individual
Encapsulates single chromosome logic in Genetic Algorithm.
Local parameters and chromosome of an Individual are always synchronized
*/
class Individual
{
public:
    typedef boost::shared_ptr<Individual> shared_ptr;

    ///Creates an Individual without initialization.
    ///For further usage initialize method of this Individual MUST be called.
    ///Otherwise exception will be thrown.
    Individual();

    ///Creates an Individual and initializes it
    ///@param parameters - parameters to be copied locally during initialization
    explicit Individual(const IDiscreteParameters* const parameters);

    ///Creates a copy of an Individual
    ///@param a - Individual to copy
    Individual(const Individual& a);

    ///Creates a copy of an Individual
    ///@param a - Individual to copy
    Individual& operator =(const Individual& a);

    ///Creates a local copy of parameters and sets chromosome according to them.
    ///MUST be called only once, otherwise exception will be thrown.
    ///@param parameters - parameters to be copied locally
    void Initialize(const IDiscreteParameters* const parameters);

    ///Gets a pointer to constant local parameters
    ///@return local parameters synchronized with current state of chromosome
    const IDiscreteParameters* const GetParametersAccordingToChromosome() const;

    ///Gets Chromosome from current individual
    ///@return Chromosome representation of current individual
    ///ATTENTION! Returned value refers to the inner variable of this
    ///individual and no longer valid and MUST NOT be used
    ///when this individual's destructor is called
    const ChromosomeType& GetChromosome() const;

    ///Set random chromosome for current Individual and synchronizes it with local parameters
    ///@return number of invalid chromosomes, generated during setting random chromosome
    int SetRandomChromosome();

    ///Performs random crossover with this and another Individuals.
    ///After crossover both will be changed to new (so called child) Individuals.
    ///@param another - an Individual to crossover this with
    ///@return true if both children are valid (satisfy conditions) otherwise false
    bool Crossover(Individual* another);

    ///Performs random mutation of an Individual
    ///@param gen_mutation_probability - mutation probability per one boolean gen
    ///@return number of invalid chromosomes, generated during mutate
    int Mutate(double gen_mutation_probability);

    ///@return true if fitness was counted for this Individual, otherwise - false
    bool HasFitness() const;

    ///This function should be called when this individual is chosen for crossover
    void IncreaseTimesChosenForCrossover();

    ///This function should be called when next generation is ready
    void ResetTimesChosenForCrossover();

    ///@return number of times this individual was chosen for crossover
    int get_times_chosen_for_crossover() const;

    ///@return fitness counted for this Individual (if hasFitness() method returns true, otherwise throws an exception because fitness was not counted)
    double get_fitness() const;

    ///@param fitness - fitness counted for this Individual' current state
    void set_fitness(double fitness);

    ///@return true if the chromosome representation satisfies parameters constraints, otherwise false
    bool IsValid() const;

    ///Fitness must be already counted, otherwise exception is thrown
    ///@return current individual's statistics
    IndividualStatistics get_individual_statistics() const;

private:
    ///Throws exception if Individual does not still have counted fitness
    void CheckForHavingFitness() const;
    void SetParametersAccordingToChromosome();

    static void BoolCrossover(ChromosomeType *first, ChromosomeType *second);

    friend std::ostream& operator<< (std::ostream& out, const Individual& individual);
    friend std::istream& operator>> (std::istream& in, Individual& individual);

    InitializationChecker  initialization_checker_;
    IDiscreteParameters::shared_ptr parameters_;
    int times_chosen_for_crossover_;
    ChromosomeType chromosome_;
    bool has_fitness_;
    double fitness_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* INDIVIDUAL_H_ */
