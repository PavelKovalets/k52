#include "optimizer_test_result.h"

using ::k52::optimization::IContinuousParameters;

namespace k52
{
namespace optimization_tests
{

OptimizerTestResult::OptimizerTestResult(
        std::string optimizer_name,
        TestFunction::shared_ptr test_function,
        IContinuousParameters::shared_ptr found_solution,
        double found_value) :
            optimizer_name_(optimizer_name),
            test_function_(test_function),
            found_solution_(found_solution),
            found_value_(found_value)
{
}

std::string OptimizerTestResult::get_optimizer_name() const
{
    return optimizer_name_;
}

TestFunction::shared_ptr OptimizerTestResult::get_test_function() const
{
    return test_function_;
}

optimization::IContinuousParameters::shared_ptr OptimizerTestResult::get_found_solution() const
{
    return found_solution_;
}

double OptimizerTestResult::get_found_value() const
{
    return found_value_;
}

}/* namespace optimization_tests */
}/* namespace k52 */

