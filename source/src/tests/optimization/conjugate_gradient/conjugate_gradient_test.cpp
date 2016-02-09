#include <k52/optimization/conjugate_gradient_method.h>

#include "../common/optimizer_tester.h"
#include "../common/consts.h"

int main()
{
    //Must be created first to register all objects correctly
    k52::optimization_tests::OptimizerTester tester;

    k52::optimization::ConjugateGradientMethod conjugate_gradient;

    k52::optimization::ContinuousOptimizer* optimizer = &conjugate_gradient;

    tester.Test(optimizer);

    return 0;
}
