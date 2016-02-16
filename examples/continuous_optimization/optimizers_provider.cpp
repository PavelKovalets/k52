#include "optimizers_provider.h"

#include <k52/optimization/bounded_nelder_mead.h>
#include <k52/optimization/conjugate_gradient_method.h>
#include <k52/optimization/hleborodov_rosenbrock_method.h>
#include <k52/optimization/random_search.h>
#include <k52/common/constants.h>

#include "consts.h"


using ::std::vector;

using ::k52::common::Constants;
using ::k52::optimization::ContinuousOptimizer;
using ::k52::optimization::BoundedNelderMead;
using ::k52::optimization::ConjugateGradientMethod;
using ::k52::optimization::HleborodovRosenbrockMethod;
using ::k52::optimization::RandomSearch;

using ::k52::optimization_tests::consts::global_lower_bound;
using ::k52::optimization_tests::consts::global_upper_bound;

namespace k52
{
namespace optimization_tests
{

vector< ContinuousOptimizer::shared_ptr > OptimizersProvider::get_optimizers()
{
    vector< ContinuousOptimizer::shared_ptr > optimizers;

    optimizers.push_back( get_bounded_nelder_mead() );
    optimizers.push_back( get_hleborodov_rosenbrock() );
    optimizers.push_back( get_conjugate_gradient() );
    optimizers.push_back( get_random_search() );

    return optimizers;
}

ContinuousOptimizer::shared_ptr OptimizersProvider::get_bounded_nelder_mead()
{
    double l = 10;

    return ContinuousOptimizer::shared_ptr(
            new BoundedNelderMead (
                    l, Constants::Eps, global_lower_bound, global_upper_bound
            )
    );
}

ContinuousOptimizer::shared_ptr OptimizersProvider::get_hleborodov_rosenbrock()
{
    size_t max_iteration_number = 1000;
    double first_step = 1;
    double max_step = 3;

    return HleborodovRosenbrockMethod::shared_ptr(
            new HleborodovRosenbrockMethod(
                    Constants::Eps, max_iteration_number, first_step, max_step
            )
    );
}

ContinuousOptimizer::shared_ptr OptimizersProvider::get_conjugate_gradient()
{
    return ConjugateGradientMethod::shared_ptr(
            new ConjugateGradientMethod()
    );
}

ContinuousOptimizer::shared_ptr OptimizersProvider::get_random_search()
{
    size_t number_of_points = 10;

    return RandomSearch::shared_ptr(
            new RandomSearch(
                    number_of_points, global_lower_bound, global_upper_bound
            )
    );
}

}/* namespace optimization_tests */
}/* namespace k52 */
