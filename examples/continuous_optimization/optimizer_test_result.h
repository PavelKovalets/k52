#ifndef K52_OPTIMIZER_TEST_RESULT_H
#define K52_OPTIMIZER_TEST_RESULT_H

#include "test_function.h"

namespace k52
{
namespace optimization_tests
{

class OptimizerTestResult
{
public:
    typedef boost::shared_ptr<OptimizerTestResult> shared_ptr;

    OptimizerTestResult(
            std::string optimizer_name,
            TestFunction::shared_ptr test_function,
            optimization::IContinuousParameters::shared_ptr found_solution,
            double found_value);

    std::string get_optimizer_name() const;
    TestFunction::shared_ptr get_test_function() const;
    optimization::IContinuousParameters::shared_ptr get_found_solution() const;
    double get_found_value() const;

private:
    DISALLOW_COPY_AND_ASSIGN(OptimizerTestResult);

    std::string optimizer_name_;
    TestFunction::shared_ptr test_function_;
    optimization::IContinuousParameters::shared_ptr found_solution_;
    double found_value_;
};

}/* namespace optimization_tests */
}/* namespace k52 */

#endif //K52_OPTIMIZER_TEST_RESULT_H
