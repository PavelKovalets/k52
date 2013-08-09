#include <iostream>

#include <k52/optimization/hleborodov_rosenbrock_method.h>
#include "../common/optimizer_tester.h"

int main()
{
    //Must be created first to register all objects correctly
    k52::optimization_tests::OptimizerTester tester;

    double precision = 1e-30;
    size_t max_iteration_number = 1e3;
    double first_step = 1;
    double max_step = 3;
    k52::optimization::HleborodovRosenbrockMethod hleborodov_rosenbrock_method(precision, max_iteration_number, first_step, max_step);
    k52::optimization::IOptimizer* optimizer = &hleborodov_rosenbrock_method;

    tester.Test(optimizer);
    return 0;
}
