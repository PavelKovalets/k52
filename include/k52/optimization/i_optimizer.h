#ifndef IOPTIMIZER_H_
#define IOPTIMIZER_H_

#include <k52/optimization/i_objective_function.h>

namespace k52
{
namespace optimization
{

/**
@class IOptimizer
Provides optimization of certain objective function
over the parameters within the bounds of certain constraints.
Optimization is performed in terms of minimization or maximization
*/
class IOptimizer : public k52::common::ICloneable

#ifdef BUILD_WITH_MPI
    ,public k52::parallel::mpi::ITransferable
#endif

{
public:
    typedef boost::shared_ptr<IOptimizer> shared_ptr;

    ///Virtual destructor for correct deallocation of resources in derived classes
    virtual ~IOptimizer() {}

    ///Performs optimization of parametersToOptimize according to functionToOptimize
    ///@param function_to_optimize - the target function to be optimized for maximum
    ///@param parameters_to_optimize - this will be set to the optimal values after method's invocation
    ///@param maximize - if true function's maximum to be found, if false - minimum
    virtual void Optimize(const IObjectiveFunction &function_to_optimize,
                          IParameters* parameters_to_optimize,
                          bool maximize) = 0;

    ///Creates deep clone of an object with resource allocation. See ICloneable
    ///@return deep clone of an object
    virtual IOptimizer* Clone() const = 0;

    ///Provides a user-friendly name of the optimiser
    virtual std::string get_name() const = 0;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* IOPTIMIZER_H_ */
