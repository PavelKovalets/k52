#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include <boost/shared_ptr.hpp>

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/common/settings_manager.h>
#include <k52/optimization/discrete_optimizer.h>
#include <k52/optimization/individual.h>
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
class GeneticAlgorithm: public DiscreteOptimizer
{
public:
    typedef boost::shared_ptr<GeneticAlgorithm> shared_ptr;

    ///Creates an instance of GA with specified parameters
    ///@param population_size - size of population that will be used during GA
    ///@param elitism_pairs - number of best pairs in population to be copied to the next population every time
    ///(for example if elitism_pairs=1, 2 best individuals will be transfered to the next population)
    ///@param max_number_of_generations - maximum number of generations for population. One of the stop criteria
    ///@param mutator - mutation operator chosen
    ///@param cache_data_limit_in_megabytes - maximum memory size allowed for cache. If this parameter is less or equal to 0, cache will not be used
    ///@param fitness_stop_criteria - the value of objective function witch consider to be optimal and further optimization has no need. One of the stop criteria.
    ///@param population_file_name - file to load population from(if no load is needed - pass empty string or ignore)
    static GeneticAlgorithm::shared_ptr Create(int population_size,
                                               int elitism_pairs,
                                               int max_number_of_generations,
                                               IMutator::shared_ptr mutator,
                                               double cache_data_limit_in_megabytes = 0,
                                               double fitness_stop_criteria = 10000000,
                                               std::string population_file_name = "");

    ///Overload for convinence
    ///It gets all settings via SettingsManager
    static GeneticAlgorithm::shared_ptr Create(const SettingsManager& settings_manager);

    void Optimize(const DiscreteObjectiveFunction &function_to_optimize,
        IDiscreteParameters* parameters_to_optimize,
        bool maximize);

    void SetInitialParameters(std::vector<IDiscreteParameters::shared_ptr> initial_parameters);

    void OnNextGenerationReadyConnect(NextGenerationReadyCallback callback);

    ///Creates deep clone of an object with resource allocation. See ICloneable
    ///@return deep clone of an object
    virtual GeneticAlgorithm* Clone() const;

    virtual std::string get_name() const;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator, int source);
#endif

protected:
    void Initialize(const IDiscreteParameters* parameters_to_optimize);
    void ValidateInitialParameters(const IDiscreteParameters* parameters_to_optimize);
    void RunIterationsAndSetBestIndivid(const DiscreteObjectiveFunction &function_to_optimize);
    void Mutate();
    void GenerateNextPopulation();
    void UpdateBestIndivid();
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
    GeneticAlgorithm(int population_size,
        int elitism_pairs,
        int max_number_of_generations,
        IMutator::shared_ptr mutator,
        double cache_data_limit_in_megabytes = 0,
        double fitness_stop_criteria = 10000000,
        std::string population_file_name = "");

    Individual::shared_ptr best_individ_;
    std::vector<Individual::shared_ptr> population_;
    std::vector<IndividualStatistics> population_statistics_;

    std::vector<IDiscreteParameters::shared_ptr> initial_parameters_;
    bool were_initial_parameters_set_;

    boost::shared_ptr<ObjectiveFunctionCounter> fitness_counter_;
    NextGenerationReadyCallback callback_function_;
    double fitness_stop_criteria_ ;
    IMutator::shared_ptr mutator_;
    int elitism_pairs_;
    int max_number_of_generations_;
    std::size_t population_size_;
    int invalid_chromosomes_;
    std::string population_file_name_;

    DISALLOW_COPY_AND_ASSIGN(GeneticAlgorithm);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* GENETICALGORITHM_H_ */
