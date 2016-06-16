#include "optimizers_provider.h"

#include <k52/optimization/bounded_nelder_mead.h>
#include <k52/optimization/conjugate_gradient_method.h>
#include <k52/optimization/hleborodov_rosenbrock_method.h>
#include <k52/optimization/random_search.h>
#include <k52/optimization/simulated_annealing.h>
#include <k52/optimization/steepest_descent_method.h>
#include <k52/common/constants.h>
#include <k52/optimization/hooke_jeeves_method.h>

#include "consts.h"


using ::std::vector;

using ::k52::common::Constants;
using ::k52::optimization::ContinuousOptimizer;
using ::k52::optimization::BoundedNelderMead;
using ::k52::optimization::ConjugateGradientMethod;
using ::k52::optimization::HleborodovRosenbrockMethod;
using ::k52::optimization::RandomSearch;
using ::k52::optimization::SimulatedAnnealing;
using ::k52::optimization::HookeJeevesMethod;
using ::k52::optimization::SteepestDescentMethod;

using ::k52::optimization_tests::consts::global_lower_bound;
using ::k52::optimization_tests::consts::global_upper_bound;

namespace k52
{
namespace optimization_tests
{

vector< ContinuousOptimizer::shared_ptr > OptimizersProvider::get_optimizers() const
{
    vector< ContinuousOptimizer::shared_ptr > optimizers;

    optimizers.push_back( get_bounded_nelder_mead() );
    optimizers.push_back( get_hleborodov_rosenbrock() );
    optimizers.push_back( get_conjugate_gradient() );
    optimizers.push_back( get_random_search() );
    optimizers.push_back( get_hooke_jeeves() );
    optimizers.push_back(get_simulated_annealing() );
    optimizers.push_back(get_steepest_descent_method() );

    return optimizers;
}

ContinuousOptimizer::shared_ptr OptimizersProvider::get_bounded_nelder_mead() const
{
    double l = 10;

    return ContinuousOptimizer::shared_ptr(
            new BoundedNelderMead (
                    l, Constants::Eps, global_lower_bound, global_upper_bound
            )
    );
}

ContinuousOptimizer::shared_ptr OptimizersProvider::get_hleborodov_rosenbrock() const
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

ContinuousOptimizer::shared_ptr OptimizersProvider::get_conjugate_gradient() const
{
    return ConjugateGradientMethod::shared_ptr(
            new ConjugateGradientMethod()
    );
}

ContinuousOptimizer::shared_ptr OptimizersProvider::get_random_search() const
{
    size_t number_of_points = 10;

    return RandomSearch::shared_ptr(
            new RandomSearch(
                    number_of_points, global_lower_bound, global_upper_bound
            )
    );
}

k52::optimization::ContinuousOptimizer::shared_ptr OptimizersProvider::get_simulated_annealing() const
{
    size_t max_iteration_number = 1000;

    return SimulatedAnnealing::shared_ptr(
            new SimulatedAnnealing(max_iteration_number, global_lower_bound, global_upper_bound)
    );
}

k52::optimization::ContinuousOptimizer::shared_ptr OptimizersProvider::get_hooke_jeeves() const
{
    double acceleration = 3.5;
    double init_step = 1;
    size_t max_iteration_number = 1000;
    double step_divider = 10;

    return HookeJeevesMethod::shared_ptr(
        new HookeJeevesMethod(
        acceleration, init_step, max_iteration_number, Constants::Eps, step_divider)
    );
}

ContinuousOptimizer::shared_ptr OptimizersProvider::get_steepest_descent_method() const
{
    double increment_of_the_argument = 0.00001;
    size_t max_iteration_number = 100;

    return ContinuousOptimizer::shared_ptr(
        new SteepestDescentMethod(
            increment_of_the_argument,
            max_iteration_number,
            Constants::Eps 			
            )
        );
}

}/* namespace optimization_tests */
}/* namespace k52 */
