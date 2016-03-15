#ifndef I_MUTATOR_H_
#define I_MUTATOR_H_

#include <boost/shared_ptr.hpp>

#include <k52/optimization/chromosome.h>

namespace k52
{
namespace optimization
{

struct MutationContext
{
public:
    int current_generation;
    int max_number_of_generations;
};

class IMutator
{
public:
    typedef boost::shared_ptr<IMutator> shared_ptr;

    virtual ~IMutator() {}

    virtual void ApplyNewMutationContext(const MutationContext& mutation_context) = 0;

    virtual void MutateChromosome(ChromosomeType* chromosome) = 0;

};

}/* namespace optimization */
}/* namespace k52 */

#endif /* I_MUTATOR_H_ */