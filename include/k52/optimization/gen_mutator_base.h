#ifndef K52_GEN_MUTATOR_BASE_H
#define K52_GEN_MUTATOR_BASE_H

#include <k52/optimization/i_mutator.h>

namespace k52
{
namespace optimization
{

class GenMutatorBase : public IMutator
{
public:
    virtual void ApplyNewMutationContext(const MutationContext &mutation_context);
    virtual void MutateChromosome(ChromosomeType *chromosome);

protected:
    virtual bool ShouldMutateCurrentGen() = 0;
    virtual void AfterGenProcessed(bool wasMutated);

    const MutationContext& get_mutation_context() const;

private:
    MutationContext mutation_context_;
};

}/* namespace optimization */
}/* namespace k52 */


#endif //K52_GEN_MUTATOR_BASE_H
