#include <k52/optimization/generation_statistics.h>

#include <cstddef>

using ::std::list;

namespace k52
{
namespace optimize
{

GenerationStatistics::GenerationStatistics(
    double average_fitness,
    const IParameters* const best_parameters,
    double best_fitness,
    size_t number_of_generation,
    int cache_hits,
    int invalid_chromosomes,
    std::list<std::string>* files_to_save,
    std::list<IndividualStatistics> all_individuals_statistics)
{
    best_parameters_ = IParameters::shared_ptr( best_parameters->Clone() );
    invalid_chromosomes_ = invalid_chromosomes;
    cache_hits_ = cache_hits;
    number_of_generation_ = number_of_generation;
    average_fitness_ = average_fitness;
    best_fitness_ = best_fitness;
    files_to_save_ = files_to_save;
    all_individuals_statistics_ = all_individuals_statistics;
}

GenerationStatistics::GenerationStatistics(const GenerationStatistics& a)
{
    *this = a;
}

GenerationStatistics& GenerationStatistics::operator=(const GenerationStatistics & a)
{
    if (this != &a) // protect against invalid self-assignment
    {
        best_parameters_ = IParameters::shared_ptr( a.best_parameters_->Clone() );
        average_fitness_ = a.average_fitness_;
        number_of_generation_ = a.number_of_generation_;
        cache_hits_ = a.cache_hits_;
        invalid_chromosomes_ = a.invalid_chromosomes_;
        best_fitness_ = a.best_fitness_;
        files_to_save_ = a.files_to_save_;
        all_individuals_statistics_ = a.all_individuals_statistics_;
    }
    // by convention, always return *this
    return *this;
}

void GenerationStatistics::SaveCurrentPopulationToFile(std::string file_name)
{
    files_to_save_->push_back(file_name);
}

const IParameters* const GenerationStatistics::get_best_parameters() const
{
    //TODO FIX do not return inner ptr
    return best_parameters_.get();
}

double GenerationStatistics::get_best_fitness() const
{
    return best_fitness_;
}

double GenerationStatistics::get_average_fitness() const
{
    return average_fitness_;
}

size_t GenerationStatistics::get_number_of_generation() const
{
    return number_of_generation_;
}

int GenerationStatistics::get_cache_hits() const
{
    return cache_hits_;
}

int GenerationStatistics::get_invalid_chromosomes() const
{
    return invalid_chromosomes_;
}

list<IndividualStatistics> GenerationStatistics::get_all_individuals_statistics() const
{
    return all_individuals_statistics_;
}

}/* namespace optimize */
}/* namespace k52 */
