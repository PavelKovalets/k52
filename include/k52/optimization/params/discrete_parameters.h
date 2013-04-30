#ifndef DISCRETEPARAMETERS_H_
#define DISCRETEPARAMETERS_H_

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/optimization/params/i_discrete_parameters.h>

namespace k52
{
namespace optimization
{

class DiscreteParameters : public IDiscreteParameters
{
public:
    typedef boost::shared_ptr<DiscreteParameters> shared_ptr;

    ///Default counstructor should be explicitelly defined if DISALLOW_COPY_AND_ASSIGN used
    DiscreteParameters() {}

    virtual ~DiscreteParameters() {}

    virtual DiscreteParameters* Clone() const = 0;

#ifdef BUILD_WITH_MPI
    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator);
#endif

private:
    DISALLOW_COPY_AND_ASSIGN(DiscreteParameters);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* DISCRETEPARAMETERS_H_ */
