#include "test_function.h"

using ::k52::optimization::ContinuousObjectiveFunction;
using ::k52::optimization::IContinuousParameters;

namespace k52
{
namespace optimization_tests
{

TestFunction::TestFunction(ContinuousObjectiveFunction::shared_ptr function,
                           IContinuousParameters::shared_ptr solution,
                           IContinuousParameters::shared_ptr start_point,
                           std::string analitical_form,
                           bool maximize):
        function_(function),
        solution_(solution),
        start_point_(start_point),
        analitical_form_(analitical_form),
        maximize_(maximize)
{
    solution_value_ = function->operator()(solution.get());
}

const ContinuousObjectiveFunction& TestFunction::get_objective_function() const
{
    return *function_.get();
}

const IContinuousParameters* TestFunction::get_solution() const
{
    return solution_.get();
}

double TestFunction::get_solution_value() const
{
    return solution_value_;
}

const IContinuousParameters* TestFunction::get_start_point() const
{
    return start_point_.get();
}

std::string TestFunction::get_analitical_form() const
{
    return analitical_form_;
}

bool TestFunction::maximize() const
{
    return maximize_;
}

}/* namespace optimization_tests */
}/* namespace k52 */
