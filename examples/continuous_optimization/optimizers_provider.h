#ifndef CONTINUOUS_OPTIMIZATION_EXAMPLE_OPTIMIZERS_PROVIDER_H
#define CONTINUOUS_OPTIMIZATION_EXAMPLE_OPTIMIZERS_PROVIDER_H

#include <k52/optimization/continuous_optimizer.h>

namespace k52
{
namespace optimization_tests
{

class OptimizersProvider
{
public:
    std::vector<k52::optimization::ContinuousOptimizer::shared_ptr> get_optimizers();

protected:
    k52::optimization::ContinuousOptimizer::shared_ptr get_bounded_nelder_mead();
    k52::optimization::ContinuousOptimizer::shared_ptr get_hleborodov_rosenbrock();
    k52::optimization::ContinuousOptimizer::shared_ptr get_conjugate_gradient();
    k52::optimization::ContinuousOptimizer::shared_ptr get_random_search();
};

}/* namespace optimization_tests */
}/* namespace k52 */

#endif //CONTINUOUS_OPTIMIZATION_EXAMPLE_OPTIMIZERS_PROVIDER_H
