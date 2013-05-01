#include "test_function.h"

#include <k52/optimization/params/continuous_parameters_array.h>

#include "test_objective_functions.h"

using ::k52::optimization::IObjectiveFunction;
using ::k52::optimization::IContinuousParameters;
using ::k52::optimization::ContinuousParametersArray;

namespace k52
{
namespace optimization_tests
{

bool TestFunction::was_initialized_ = false;
std::vector<TestFunction::shared_ptr> TestFunction::test_functions_;

const IObjectiveFunction& TestFunction::get_objective_function() const
{
    return *function_.get();
}

const IContinuousParameters* TestFunction::get_solution() const
{
    return solution_.get();
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

void TestFunction::Register(IObjectiveFunction::shared_ptr function,
                            IContinuousParameters::shared_ptr solution,
                            IContinuousParameters::shared_ptr start_point,
                            std::string analitical_form,
                            bool maximize)
{
    TestFunction::shared_ptr test_function(
                new TestFunction(function,
                                 solution,
                                 start_point,
                                 analitical_form,
                                 maximize)
                );
    test_functions_.push_back(test_function);
}

std::vector<TestFunction::shared_ptr> TestFunction::get_test_functions()
{
    if(!was_initialized_)
    {
        Initialize();
    }
    return test_functions_;
}

TestFunction::TestFunction(IObjectiveFunction::shared_ptr function,
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
}

void TestFunction::Initialize()
{
    IObjectiveFunction::shared_ptr square_objective_function( new SquareObjectiveFunction() );

    std::vector<double> square_solution_values(2);
    square_solution_values[0] = 1.414213562;
    square_solution_values[1] = 1.414213562;
    IContinuousParameters::shared_ptr square_solution( new ContinuousParametersArray(square_solution_values));

    std::vector<double> square_start_point_values(2);
    square_start_point_values[0] = 11;
    square_start_point_values[1] = 7;
    IContinuousParameters::shared_ptr square_start_point( new ContinuousParametersArray(square_start_point_values));

    Register(square_objective_function, square_solution, square_start_point, "square_root(x)", false);
}

}/* namespace optimization_tests */
}/* namespace k52 */
