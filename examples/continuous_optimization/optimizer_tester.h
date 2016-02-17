#ifndef OPTIMIZER_TESTER_H
#define OPTIMIZER_TESTER_H

#include <vector>

#include <k52/optimization/continuous_optimizer.h>

#include "test_function.h"
#include "optimizer_test_result.h"
#include "optimizers_provider.h"
#include "test_functions_provider.h"

namespace k52
{
namespace optimization_tests
{

class OptimizerTester
{
public:
    OptimizerTester(bool verbose = false);
    std::vector < std::vector < OptimizerTestResult::shared_ptr > > Test(
            const OptimizersProvider& optimizersProvider,
            const TestFunctionsProvider& functionsProvider);

protected:
    OptimizerTestResult::shared_ptr TestSingleFunction(
            TestFunction::shared_ptr function,
            k52::optimization::ContinuousOptimizer::shared_ptr optimizer);

private:
    DISALLOW_COPY_AND_ASSIGN(OptimizerTester);
    bool verbose_;
};

}/* namespace optimization_tests */
}/* namespace k52 */

#endif /* OPTIMIZER_TESTER_H */
