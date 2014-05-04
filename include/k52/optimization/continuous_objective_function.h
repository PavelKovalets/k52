#ifndef CONTINUOUSOBJECTIVEFUNCTION_H_
#define CONTINUOUSOBJECTIVEFUNCTION_H_

#include <k52/optimization/i_objective_function.h>
#include <k52/optimization/params/i_continuous_parameters.h>

namespace k52
{
namespace optimization
{

class ContinuousObjectiveFunction : public IObjectiveFunction
{
public:
    typedef boost::shared_ptr<ContinuousObjectiveFunction> shared_ptr;

    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~ContinuousObjectiveFunction() {}

    virtual double operator () (const IParameters* const parameters) const;

    virtual double operator () (const IContinuousParameters* const parameters) const;

    virtual double operator () (const std::vector<double>& values) const = 0;

    virtual ContinuousObjectiveFunction* Clone() const = 0;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* CONTINUOUSOBJECTIVEFUNCTION_H_ */