#include <stdexcept>
#include <k52/common/random.h>
#include <k52/optimization/linear_mutator.h>

using ::k52::common::Random;

namespace k52
{
namespace optimization
{

LinearMutator::LinearMutator(double start_gen_mutation_probability, double end_gen_mutation_probability)
    : start_mutation_value_(start_gen_mutation_probability), end_mutation_value_(end_gen_mutation_probability)
{
    Random::ValidateProbability(start_gen_mutation_probability);
    Random::ValidateProbability(end_gen_mutation_probability);
}

bool LinearMutator::ShouldMutateCurrentGen()
{
    return Random::Instance().CheckEventOutcome( GetCurrentGenMutationProbability() );
}

double LinearMutator::GetCurrentGenMutationProbability()
{
    double current = get_mutation_context().current_generation;
    double max = get_mutation_context().max_number_of_generations - 1;
    return (end_mutation_value_ - start_mutation_value_) * current / max + start_mutation_value_;
}
}/* namespace optimization */
}/* namespace k52 */
