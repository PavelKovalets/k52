#ifndef OPTIMIZER_TESTER_H
#define OPTIMIZER_TESTER_H

#include <vector>

#include <k52/optimization/continuous_optimizer.h>

#include "test_function.h"

namespace k52
{
namespace optimization_tests
{

class OptimizerTester
{
public:
    void Test(k52::optimization::ContinuousOptimizer* optimizer);

protected:
    void TestSingleFunction(const TestFunction& function,
                            k52::optimization::ContinuousOptimizer* optimizer);

    void PrintParameters(const k52::optimization::IContinuousParameters* parameters) const;

};

}/* namespace optimization_tests */
}/* namespace k52 */

#endif /* OPTIMIZER_TESTER_H */
