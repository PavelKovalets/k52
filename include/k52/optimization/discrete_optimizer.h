#ifndef DISCRETEOPTIMIZER_H_
#define DISCRETEOPTIMIZER_H_

#include <k52/optimization/i_optimizer.h>
#include <k52/optimization/discrete_objective_function.h>

namespace k52
{
namespace optimization
{

class DiscreteOptimizer : public IOptimizer
{
public:
    typedef boost::shared_ptr<DiscreteOptimizer> shared_ptr;

    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~DiscreteOptimizer() {}

    virtual void Optimize(const DiscreteObjectiveFunction &function_to_optimize,
        IDiscreteParameters* parametrs_to_optimize,
        bool maximize) = 0;

    virtual void Optimize(const IObjectiveFunction &function_to_optimize,
        IParameters* parametrs_to_optimize,
        bool maximize);

    ///Creates deep clone of an object with resource allocation. See ICloneable
    ///@return deep clone of an object
    virtual DiscreteOptimizer* Clone() const = 0;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* DISCRETEOPTIMIZER_H_ */