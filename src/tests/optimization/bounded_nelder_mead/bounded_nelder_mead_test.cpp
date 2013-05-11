#include <iostream>

#include <k52/optimization/bounded_nelder_mead.h>
#include "../common/optimizer_tester.h"

int main()
{
    //Must be created first to register all objects correctly
    k52::optimization_tests::OptimizerTester tester;

    double l = 10;
    double precision = 1e-30;
    double lower_bound = -10000;
    double upper_bound = 10000;
    k52::optimization::BoundedNelderMead bounded_nelder_mead(l, precision, lower_bound, upper_bound);
    k52::optimization::IOptimizer* optimizer = &bounded_nelder_mead;

    tester.Test(optimizer);

    return 0;
}
