#include "test_functions_provider.h"

#include "test_objective_functions.h"

#include <cmath>
#include <k52/optimization/params/continuous_parameters_array.h>

using ::k52::optimization::ContinuousObjectiveFunction;
using ::k52::optimization::IContinuousParameters;
using ::k52::optimization::ContinuousParametersArray;

namespace k52
{
namespace optimization_tests
{

TestFunctionsProvider::TestFunctionsProvider()
{
    std::vector< double > square_solution_values(2);
    square_solution_values[0] = M_SQRT2;
    square_solution_values[1] = M_SQRT2;
    square_solution_ = IContinuousParameters::shared_ptr(new ContinuousParametersArray(square_solution_values));

    std::vector< double > square_start_point_values(2);
    square_start_point_values[0] = 11;
    square_start_point_values[1] = 7;
    square_start_point_ = IContinuousParameters::shared_ptr(new ContinuousParametersArray(square_start_point_values));

    std::vector< double > zero_solution_values(2);
    zero_solution_values[0] = 0;
    zero_solution_values[1] = 0;
    zero_solution_ = IContinuousParameters::shared_ptr(new ContinuousParametersArray(zero_solution_values));

    std::vector< double > difraction_start_point_values(2);
    difraction_start_point_values[0] = 100;
    difraction_start_point_values[1] = 100;
    difraction_start_point_ = IContinuousParameters::shared_ptr(
            new ContinuousParametersArray(difraction_start_point_values));
}


std::vector< TestFunction::shared_ptr > TestFunctionsProvider::get_test_functions() const
{
    std::vector< TestFunction::shared_ptr > functions;

    functions.push_back( get_square() );
    functions.push_back( get_simple_square() );
    functions.push_back( get_difraction() );
    functions.push_back( get_square_summ() );
    functions.push_back( get_multiminimum() );

    return functions;
}

TestFunction::shared_ptr TestFunctionsProvider::get_square() const
{
    ContinuousObjectiveFunction::shared_ptr square_objective_function(new SquareObjectiveFunction());

    return TestFunction::shared_ptr(
            new TestFunction(square_objective_function,
                             square_solution_,
                             square_start_point_,
                             "1/|x^2-2|",
                             true)
    );
}

TestFunction::shared_ptr TestFunctionsProvider::get_simple_square() const
{
    ContinuousObjectiveFunction::shared_ptr simple_square_objective_function(new SimpleSquareObjectiveFunction());

    return TestFunction::shared_ptr(
            new TestFunction(simple_square_objective_function,
                             square_solution_,
                             square_start_point_,
                             "(x^2-2)^2",
                             false)
    );
}

TestFunction::shared_ptr TestFunctionsProvider::get_difraction() const
{
    ContinuousObjectiveFunction::shared_ptr difraction_objective_function(new DifractionObjectiveFunction());

    return TestFunction::shared_ptr(
            new TestFunction(difraction_objective_function,
                             zero_solution_,
                             difraction_start_point_,
                             "SUMM( sin(Xi) / Xi )",
                             true)
    );
}

TestFunction::shared_ptr TestFunctionsProvider::get_square_summ() const
{
    ContinuousObjectiveFunction::shared_ptr square_summ_objective_function(new SquareSummObjectiveFunction());

    return TestFunction::shared_ptr(
            new TestFunction(square_summ_objective_function,
                             zero_solution_,
                             difraction_start_point_,
                             "SUMM( Xi^2 )",
                             false)
    );
}

TestFunction::shared_ptr TestFunctionsProvider::get_multiminimum() const
{
    ContinuousObjectiveFunction::shared_ptr multiminimum_objective_function(new MultiminimumObjectiveFunction());

    return TestFunction::shared_ptr(
            new TestFunction(multiminimum_objective_function,
                             zero_solution_,
                             difraction_start_point_,
                             "x sin(4 x) + 1.1y sin(2 y)",
                             false)
    );
}


}/* namespace optimization_tests */
}/* namespace k52 */