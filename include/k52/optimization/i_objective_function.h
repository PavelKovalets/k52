#ifndef IOBJECTIVEFUNCTION_H_
#define IOBJECTIVEFUNCTION_H_

#include <k52/common/i_cloneable.h>
#include <k52/optimization/params/i_parameters.h>

namespace k52
{
namespace optimization
{

/**
@class IObjectiveFunction
Functor that counts objective function value
*/
class IObjectiveFunction : public k52::common::ICloneable
{
public:
    typedef boost::shared_ptr<IObjectiveFunction> shared_ptr;

    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~IObjectiveFunction() {}

    ///Operator that implements counting of objective function value
    ///@param parameters - parameters to count objective function value for
    virtual double operator () (const IParameters* const parameters) const = 0;

    virtual IObjectiveFunction* Clone() const = 0;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* IOBJECTIVEFUNCTION_H_ */
