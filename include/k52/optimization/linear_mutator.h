#ifndef K52_LINEAR_MUTATOR_H
#define K52_LINEAR_MUTATOR_H

#include <k52/optimization/i_mutator.h>
#include <k52/optimization/gen_mutator_base.h>

namespace k52
{
namespace optimization
{

class LinearMutator : public GenMutatorBase
{
public:
    LinearMutator(double start_gen_mutation_probability, double end_gen_mutation_probability);

protected:
    bool ShouldMutateCurrentGen();
    double GetCurrentGenMutationProbability();

private:
    double start_mutation_value_;
    double end_mutation_value_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif //K52_LINEAR_MUTATOR_H
