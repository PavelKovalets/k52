#ifndef CONTINUOUSOPTIMIZER_H_
#define CONTINUOUSOPTIMIZER_H_

#include <k52/optimization/i_optimizer.h>
#include <k52/optimization/continuous_objective_function.h>

namespace k52
{
namespace optimization
{

class ContinuousOptimizer : public IOptimizer
{
public:
    typedef boost::shared_ptr<ContinuousOptimizer> shared_ptr;

    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~ContinuousOptimizer() {}

    virtual void Optimize(const IObjectiveFunction &function_to_optimize,
        IParameters* parametrs_to_optimize,
        bool maximize);

    virtual void Optimize(const ContinuousObjectiveFunction &function_to_optimize,
        IContinuousParameters* parametrs_to_optimize,
        bool maximize) = 0;

    ///Creates deep clone of an object with resource allocation. See ICloneable
    ///@return deep clone of an object
    virtual ContinuousOptimizer* Clone() const = 0;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* CONTINUOUSOPTIMIZER_H_ */