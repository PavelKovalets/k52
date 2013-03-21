#include "Mutator.h"

#include <math.h>
#include <stdexcept>

#include "Random.h"

namespace k52
{
namespace optimize
{

Mutator& Mutator::Instance()
{
    static Mutator self;
    return self;
}

void Mutator::MutateBoolArray(double gen_mutation_probability, std::vector<bool>* array)
{
    if(was_probability_set_)
    {
        if(mutation_probability_ != gen_mutation_probability)
        {
            throw std::logic_error("GenMutationProbability must not be changed according to current implementation of Mutator");
        }
    }
    else
    {
        SetMutationProbability(gen_mutation_probability);
    }

    for(size_t i = 0; i < array->size(); i++)
    {
        if(currently_skipped_gens_>=gens_to_skip_now_)
        {
            (*array)[i] = !(*array)[i];
            SetGensToSkipNow();
        }
        else
        {
            currently_skipped_gens_ ++;
        }
    }
}

Mutator::Mutator()
{
    max_number_of_skipped_gens_ = 0;
    mutation_probability_ = 0;
    was_probability_set_ = false;
    gens_to_skip_now_ = 0;
    currently_skipped_gens_ = 0;
}

void Mutator::SetMutationProbability(double gen_mutation_probability)
{
    mutation_probability_ = gen_mutation_probability;

    max_number_of_skipped_gens_ = floor(1/mutation_probability_) - 1;

    if(max_number_of_skipped_gens_ <= 0)
    {
        throw std::invalid_argument("genMutationProbability was set incorrectly");
    }

    SetGensToSkipNow();
}

void Mutator::SetGensToSkipNow()
{
    gens_to_skip_now_ = Random::Instance().GetUniformlyDistributedDiscreteRandomQuantity(0, max_number_of_skipped_gens_);
    currently_skipped_gens_ = 0;
}

}/* namespace optimize */
}/* namespace k52 */
