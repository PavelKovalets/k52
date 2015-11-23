#include <k52/optimization/flip_bit_mutator.h>
#include <k52/common/random.h>

#include <cmath>
#include <stdexcept>

namespace k52
{
namespace optimization
{

void FlipBitMutator::MutateChromosome(ChromosomeType* chromosome)
{
    for (size_t i = 0; i < chromosome->size(); i++)
    {
        if(currently_skipped_gens_>=gens_to_skip_now_)
        {
            (*chromosome)[i] = !(*chromosome)[i];
            SetGensToSkipNow();
        }
        else
        {
            currently_skipped_gens_ ++;
        }
    }
}

FlipBitMutator::FlipBitMutator(double gen_mutation_probability)
{
    mutation_probability_ = gen_mutation_probability;

    max_number_of_skipped_gens_ = (int)std::floor(1 / mutation_probability_) - 1;

    if (max_number_of_skipped_gens_ <= 0)
    {
        throw std::invalid_argument("gen_mutation_probability was set incorrectly");
    }

    SetGensToSkipNow();
}

void FlipBitMutator::SetGensToSkipNow()
{
    gens_to_skip_now_ = Random::Instance().GetUniformlyDistributedDiscreteRandomQuantity(0, max_number_of_skipped_gens_);
    currently_skipped_gens_ = 0;
}

}/* namespace optimization */
}/* namespace k52 */
