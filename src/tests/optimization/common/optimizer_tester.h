#ifndef OPTIMIZER_TESTER_H
#define OPTIMIZER_TESTER_H

#include <vector>

#include <k52/optimization/i_optimizer.h>

#include "test_function.h"

namespace k52
{
namespace optimization_tests
{

class OptimizerTester
{
public:
    OptimizerTester();

    void Test(k52::optimization::IOptimizer* optimizer);

protected:
    void TestSingleFunction(const TestFunction& function,
                            k52::optimization::IOptimizer* optimizer);

    void PrintParameters(const k52::optimization::IContinuousParameters* parameters) const;

private:
    std::vector<TestFunction::shared_ptr> test_functions_;
};

}/* namespace optimization_tests */
}/* namespace k52 */

#endif /* OPTIMIZER_TESTER_H */
