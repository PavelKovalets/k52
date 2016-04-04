#include <k52/common/random.h>
#include <k52/optimization/gen_mutator_base.h>

using ::k52::common::Random;

namespace k52
{
namespace optimization
{

void GenMutatorBase::ApplyNewMutationContext(const MutationContext &mutation_context)
{
    mutation_context_ = mutation_context;
}

void GenMutatorBase::MutateChromosome(ChromosomeType* chromosome)
{
    for (size_t i = 0; i < chromosome->size(); i++)
    {
        bool mutate = ShouldMutateCurrentGen();

        if ( mutate )
        {
            (*chromosome)[i] = !(*chromosome)[i];
        }

        AfterGenProcessed(mutate);
    }
}

void GenMutatorBase::AfterGenProcessed(bool wasMutated)
{
}

const MutationContext& GenMutatorBase::get_mutation_context() const
{
    return mutation_context_;
}

}/* namespace optimization */
}/* namespace k52 */
