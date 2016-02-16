#ifndef IPARAMETERS_H_
#define IPARAMETERS_H_

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/common/i_cloneable.h>

#ifdef BUILD_WITH_MPI
#include <k52/parallel/mpi/i_transferable.h>
#endif

namespace k52
{
namespace optimization
{

/**
@class IParameters
Encapsulates optimization parameters and constraints logic.
May be used to represent multiple as well as single parameter.
Also can be used as a basic interface for pattern Conpositor:
Class wich derives from IParameters will also contain a collection
of IParameters and extend their behaviour by adding additional constraints etc.
*/
class IParameters
    : public k52::common::ICloneable
#ifdef BUILD_WITH_MPI
    ,public k52::parallel::mpi::ITransferable
#endif
{
public:
    typedef boost::shared_ptr<IParameters> shared_ptr;

    ///Default counstructor should be explicitelly defined if DISALLOW_COPY_AND_ASSIGN used
    IParameters() {}

    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~IParameters() {}

    ///Checks all constraints to be satisfied for currently set value(s) of parameter(s)
    ///@return TRUE if constraints are satisfied, otherwise FALSE
    virtual bool CheckConstraints() const = 0;

    ///Creates deep clone of an object with resource allocation. See ICloneable
    ///@return deep clone of an object
    virtual IParameters* Clone() const = 0;

private:
    DISALLOW_COPY_AND_ASSIGN(IParameters);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* IPARAMETERS_H_ */
