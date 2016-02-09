#include <iostream>

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
    double precision = 1e-30;
    k52::optimization::BoundedNelderMead bounded_nelder_mead(l,
                                                             precision,
                                                             global_lower_bound,
                                                             global_upper_bound);
    k52::optimization::ContinuousOptimizer* optimizer = &bounded_nelder_mead;

    tester.Test(optimizer);

    return 0;
}
