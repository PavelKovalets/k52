#include <k52/optimization/random_search.h>
#include <k52/optimization/bounded_nelder_mead.h>

#include "../common/optimizer_tester.h"
#include "../common/consts.h"

using ::k52::optimization_tests::consts::global_lower_bound;
using ::k52::optimization_tests::consts::global_upper_bound;

int main()
{
    //Must be created first to register all objects correctly
    k52::optimization_tests::OptimizerTester tester;

    double l = 10;
    double precision = 1e-10;
    size_t number_of_points = 30;

    k52::optimization::BoundedNelderMead bounded_nelder_mead(l,
                                                             precision,
                                                             global_lower_bound,
                                                             global_upper_bound);

    k52::optimization::RandomSearch random_search(number_of_points,
                                                  global_lower_bound,
                                                  global_upper_bound,
                                                  &bounded_nelder_mead);
    k52::optimization::IOptimizer* optimizer = &random_search;

    tester.Test(optimizer);

    return 0;
}
