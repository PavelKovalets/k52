#ifndef I_MUTATOR_H_
#define I_MUTATOR_H_

#include <boost/shared_ptr.hpp>

#include <k52/optimization/chromosome.h>

namespace k52
{
namespace optimization
{

class IMutator
{
public:
    typedef boost::shared_ptr<IMutator> shared_ptr;

    virtual ~IMutator() {}

    virtual void MutateChromosome(ChromosomeType* chromosome) = 0;

};

}/* namespace optimization */
}/* namespace k52 */

#endif /* I_MUTATOR_H_ */