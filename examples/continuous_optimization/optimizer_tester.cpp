#include "optimizer_tester.h"
#include "test_functions_provider.h"

#include <k52/common/helpers.h>
#include <iostream>

using ::std::cout;
using ::std::endl;
using ::std::vector;
using ::k52::common::Helpers;
using ::k52::optimization::IContinuousParameters;
using ::k52::optimization::ContinuousOptimizer;

namespace k52
{
namespace optimization_tests
{

OptimizerTester::OptimizerTester(bool verbose)
        : verbose_(verbose)
{
}

vector < vector < OptimizerTestResult::shared_ptr > >  OptimizerTester::Test(
        const OptimizersProvider& optimizersProvider,
        const TestFunctionsProvider& functionsProvider)
{
    vector<ContinuousOptimizer::shared_ptr> optimizers = optimizersProvider.get_optimizers();
    vector<TestFunction::shared_ptr> test_functions = functionsProvider.get_test_functions();

    vector < vector < OptimizerTestResult::shared_ptr > > results(test_functions.size());

    for (size_t i = 0; i < test_functions.size(); i++)
    {
        vector < OptimizerTestResult::shared_ptr > test_function_results(optimizers.size());

        for (size_t j = 0; j < optimizers.size(); j++)
        {
            test_function_results[j] = TestSingleFunction(test_functions[i], optimizers[j]);
        }

        results[i] = test_function_results;
    }

    return results;
}

OptimizerTestResult::shared_ptr OptimizerTester::TestSingleFunction(
        TestFunction::shared_ptr function,
        ContinuousOptimizer::shared_ptr optimizer)
{
    if (verbose_)
    {
        cout << "---- Testing " << function->get_analitical_form() << " "
            << (function->maximize() ? "max" : "min") << " ----" << endl;
    }

    const k52::optimization::ContinuousObjectiveFunction& objective_function
        = function->get_objective_function();

    const IContinuousParameters* start_point = function->get_start_point();

    IContinuousParameters::shared_ptr parameters (start_point->Clone());
    optimizer->Optimize(objective_function, parameters.get(), function->maximize());

    const IContinuousParameters* found_solution = parameters.get();
    double found_value = objective_function(found_solution);

    return OptimizerTestResult::shared_ptr(
            new OptimizerTestResult(optimizer->get_name(), function, parameters, found_value)
    );
}

}/* namespace optimization_tests */
}/* namespace k52 */
