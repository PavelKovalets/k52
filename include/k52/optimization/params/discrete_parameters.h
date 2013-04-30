#ifndef DISCRETEPARAMETERS_H_
#define DISCRETEPARAMETERS_H_

#include <k52/optimization/params/i_discrete_parameters.h>

namespace k52
{
namespace optimization
{

class DiscreteParameters : public IDiscreteParameters
{
public:
    typedef boost::shared_ptr<DiscreteParameters> shared_ptr;

    virtual ~DiscreteParameters() {}

    virtual DiscreteParameters* Clone() const = 0;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator);
#endif
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* DISCRETEPARAMETERS_H_ */
