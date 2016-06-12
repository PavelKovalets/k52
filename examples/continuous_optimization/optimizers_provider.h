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
    OptimizersProvider() {}
    std::vector<k52::optimization::ContinuousOptimizer::shared_ptr> get_optimizers() const;

protected:
    k52::optimization::ContinuousOptimizer::shared_ptr get_bounded_nelder_mead() const;
    k52::optimization::ContinuousOptimizer::shared_ptr get_hleborodov_rosenbrock() const;
    k52::optimization::ContinuousOptimizer::shared_ptr get_conjugate_gradient() const;
    k52::optimization::ContinuousOptimizer::shared_ptr get_random_search() const;
    k52::optimization::ContinuousOptimizer::shared_ptr get_simulated_annealing() const;
    k52::optimization::ContinuousOptimizer::shared_ptr get_hooke_jeeves() const;

private:
    DISALLOW_COPY_AND_ASSIGN(OptimizersProvider);
};

}/* namespace optimization_tests */
}/* namespace k52 */

#endif //CONTINUOUS_OPTIMIZATION_EXAMPLE_OPTIMIZERS_PROVIDER_H
