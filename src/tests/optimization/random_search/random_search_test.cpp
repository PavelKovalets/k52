#include <k52/optimization/random_search.h>
#include <k52/optimization/bounded_nelder_mead.h>

#include "../common/optimizer_tester.h"

int main()
{
    //Must be created first to register all objects correctly
    k52::optimization_tests::OptimizerTester tester;

    double lower_bound = -10000;
    double upper_bound = 10000;
    double l = 10;
    double precision = 1e-10;
    size_t number_of_points = 30;

    k52::optimization::BoundedNelderMead bounded_nelder_mead(l,
                                                             precision,
                                                             lower_bound,
                                                             upper_bound);

    k52::optimization::RandomSearch random_search(number_of_points,
                                                  lower_bound,
                                                  upper_bound,
                                                  &bounded_nelder_mead);
    k52::optimization::IOptimizer* optimizer = &random_search;

    tester.Test(optimizer);

    return 0;
}
