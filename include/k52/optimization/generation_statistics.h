#ifndef GENERATIONSTATISTICS_H_
#define GENERATIONSTATISTICS_H_

#include <list>
#include <string>

#include <k52/optimization/params/i_parameters.h>
#include <k52/optimization/individual_statistics.h>

namespace k52
{
namespace optimization
{

/**
@class GenerationStatistics
Represents statistics about Genetic Algorithm population
*/
class GenerationStatistics
{
public:
    ///Creates GenerationStatistics instance and copies currentlyBestParameters to it
    GenerationStatistics(
        double average_fitness,
        const IParameters* const best_parameters,
        double best_fitness,
        size_t number_of_generation,
        int cache_hits,
        int invalid_chromosomes,
        std::list<std::string>* files_to_save,
        std::list<IndividualStatistics> all_individuals_statistics);

    ///Creates a copy of a GenerationStatistics
    ///@param a - GenerationStatistics to copy
    GenerationStatistics(const GenerationStatistics& a);

    ///Creates a copy of an GenerationStatistics
    ///@param a - GenerationStatistics to copy
    GenerationStatistics& operator =(const GenerationStatistics& a);

    ///Indicates that current population should be saved to file
    ///ATTENTION! Saving itself will not occur immediately, but only after all NextGenerationReadyCallback functions will be called
    ///It is guaranteed only that it will be saved before next call to current NextGenerationReadyCallback function
    ///@param file_name - name of file save population to
    void SaveCurrentPopulationToFile(std::string file_name);

    ///Returns the best parameters during current population (or generation)
    ///@return - parameters to be set to the best values
    ///ATTENTION! Returned value points to the inner variable of this
    ///GenerationStatistics object and no longer valid and MUST NOT be used
    ///when this GenerationStatistics object's destructor is called
    const IParameters* const get_best_parameters() const;

    ///Returns fitness for parameters, returned by getBestParameters() method
    ///@return - fitness, counted for the best parameters during current population (or generation)
    double get_best_fitness() const;

    ///@return average fitness value of current population (or generation)
    double get_average_fitness() const;

    ///@return sequential number of current population (or generation)
    size_t get_number_of_generation() const;

    ///@return number of hits to the fitness cache for current population (or generation)
    int get_cache_hits() const;

    ///@return number of invalid chromosomes generated during current population (or generation)
    int get_invalid_chromosomes() const;

    ///@return statistics for all individuals in current population
    std::list<IndividualStatistics> get_all_individuals_statistics() const;

private:
    IParameters::shared_ptr best_parameters_;
    double best_fitness_;
    double average_fitness_;
    size_t number_of_generation_;
    int cache_hits_;
    int invalid_chromosomes_;
    std::list<IndividualStatistics> all_individuals_statistics_;
    std::list<std::string>* files_to_save_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* GENERATIONSTATISTICS_H_ */
