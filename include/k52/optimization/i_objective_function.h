#ifndef IOBJECTIVEFUNCTION_H_
#define IOBJECTIVEFUNCTION_H_

#ifdef BUILD_WITH_MPI
#include <k52/common/i_cloneable.h>
#endif

#include <k52/optimization/params/i_parameters.h>

namespace k52
{
namespace optimization
{

/**
@class IObjectiveFunction
Functor that counts objective function value
*/
class IObjectiveFunction
#ifdef BUILD_WITH_MPI
    :public k52::common::ICloneable
#endif
{
public:
    typedef boost::shared_ptr<IObjectiveFunction> shared_ptr;

    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~IObjectiveFunction() {}

    ///Operator that implements counting of objective function value
    ///@param parameters - parameters to count objective function value for
    virtual double operator () (const IParameters* const parameters) const = 0;

#ifdef BUILD_WITH_MPI
    virtual IObjectiveFunction* Clone() const = 0;
#endif
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* IOBJECTIVEFUNCTION_H_ */
