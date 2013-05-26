#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include <boost/shared_ptr.hpp>

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/optimization/i_optimizer.h>
#include <k52/optimization/individual.h>
#include <k52/optimization/params/i_discrete_parameters.h>
#include <k52/optimization/generation_statistics.h>

namespace k52
{
namespace optimization
{

class ObjectiveFunctionCounter;

typedef void (*NextGenerationReadyCallback)(GenerationStatistics);

/**
@class GeneticAlgorithm
Performs evolutionary optimization.
Best individual of all generations is selected and returned as result.
*/
class GeneticAlgorithm: public IOptimizer
{
public:
    ///Creates an instance of GA with specified parameters
    ///@param population_size - size of population that will be used during GA
    ///@param elitism_pairs - number of best pairs in population to be copied to the next population every time 
    ///(for example if elitism_pairs=1, 2 best individuals will be transfered to the next population)
    ///@param max_number_of_generations - maximum number of generations for population. One of the stop criteria.
    ///@param use_fitness_value_caching - to use fitness cache based on chromosomes or not
    ///@param fitness_stop_criteria - the value of objective function witch consider to be optimal and further optimization has no need. One of the stop criteria.
    ///@param mutation_probability - mutation probability per one boolean gen in chromosome
    ///@param population_file_name - file to load population from(if no load is needed - pass empty string or ignore)
    GeneticAlgorithm(int population_size,
        int elitism_pairs,
        int max_number_of_generations,
        bool use_fitness_value_caching = false,
        double fitness_stop_criteria = 10000000,
        double mutation_probability = 0.005,
        std::string population_file_name = "");

    void Optimize(const IObjectiveFunction &function_to_optimize,
                  IParameters* parametrs_to_optimize,
                  bool maximize);
    void OnNextGenerationReadyConnect(NextGenerationReadyCallback callback);

    ///Creates deep clone of an object with resource allocation. See ICloneable
    ///@return deep clone of an object
    virtual GeneticAlgorithm* Clone() const;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator, int source);
#endif

protected:
    void Initialize(IDiscreteParameters* parametrs_to_optimize);
    void Mutate();
    void GenerateNextPopulation();
    int SelectRandomIndividualIndexForCrossover(double total_fitness);
    void ProcessStatistics(int number_of_generation);
    double GetPopulationAveradgeFitness();
    void GatherAllIndividualsStatistics();
    void FireNextGenerationReady(const GenerationStatistics& statistics);
    void SavePopulationToFile(std::string population_file_name);
    void ReadPopulationFromFile();
    void OutputPopulation(std::ostream& out);
    void InputPopulation(std::ifstream& in);
    static bool GreaterFitness(Individual::shared_ptr first, Individual::shared_ptr second);

private:
    Individual::shared_ptr best_individ_;
    std::vector<Individual::shared_ptr> population_;
    std::vector<IndividualStatistics> population_statistics_;
    boost::shared_ptr<ObjectiveFunctionCounter> fitness_counter_;
    NextGenerationReadyCallback callback_function_;
    double fitness_stop_criteria_ ;
    double mutation_probability_;
    int  elitism_pairs_;
    int max_number_of_generations_;
    int population_size_;    
    int invalid_chromosomes_;
    std::string population_file_name_;

    DISALLOW_COPY_AND_ASSIGN(GeneticAlgorithm);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* GENETICALGORITHM_H_ */
