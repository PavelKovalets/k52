#include <iostream>

#include "optimizer_tester.h"
#include "optimizers_provider.h"

int main()
{
    //Tester must be created first to register all objects correctly
    k52::optimization_tests::OptimizerTester tester;
    k52::optimization_tests::OptimizersProvider provider;

    std::vector< k52::optimization::ContinuousOptimizer::shared_ptr > optimizers = provider.get_optimizers();

    for (size_t i = 0; i<optimizers.size(); i++)
    {
        tester.Test(optimizers[i].get());
    }

    return 0;
}
