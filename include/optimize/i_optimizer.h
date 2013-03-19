#ifndef IOPTIMIZER_H_
#define IOPTIMIZER_H_

#include <optimize/i_objective_function.h>

namespace k52
{
namespace optimize
{

/**
@class IOptimizer
Provides optimization of certain objective function
over the parameters within the bounds of certain constraints.
Optimization is performed in terms of minimization or maximization
*/
class IOptimizer
{
public:
    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~IOptimizer() {}

    ///Performs optimization of parametrsToOptimize according to functionToOptimize
    ///@param function_to_optimize - the target function to be optimized for maximum
    ///@param parametrs_to_optimize - this will be set to the optimal values after method's invocation
    virtual void Optimize(const IObjectiveFunction &function_to_optimize, IParameters* parametrs_to_optimize) = 0;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* IOPTIMIZER_H_ */
