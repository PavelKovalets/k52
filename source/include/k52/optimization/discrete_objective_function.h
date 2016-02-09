#ifndef DISCRETEOBJECTIVEFUNCTION_H_
#define DISCRETEOBJECTIVEFUNCTION_H_

#include <k52/optimization/i_objective_function.h>
#include <k52/optimization/params/i_discrete_parameters.h>

namespace k52
{
namespace optimization
{

class DiscreteObjectiveFunction : public IObjectiveFunction
{
public:
    typedef boost::shared_ptr<DiscreteObjectiveFunction> shared_ptr;

    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~DiscreteObjectiveFunction() {}

    virtual double operator () (const IDiscreteParameters* const parameters) const = 0;

    virtual double operator () (const IParameters* const parameters) const;

    virtual DiscreteObjectiveFunction* Clone() const = 0;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* DISCRETEOBJECTIVEFUNCTION_H_ */