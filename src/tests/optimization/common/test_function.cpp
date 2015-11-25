#include "test_function.h"

#ifdef BUILD_WITH_MPI
#include <k52/parallel/mpi/identifyable_objects_manager.h>
#endif

#include <k52/optimization/params/continuous_parameters_array.h>

#include "test_objective_functions.h"

using ::k52::optimization::ContinuousObjectiveFunction;
using ::k52::optimization::IContinuousParameters;
using ::k52::optimization::ContinuousParametersArray;

namespace k52
{
namespace optimization_tests
{

bool TestFunction::was_initialized_ = false;
std::vector<TestFunction::shared_ptr> TestFunction::test_functions_;

const ContinuousObjectiveFunction& TestFunction::get_objective_function() const
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

void TestFunction::Register(ContinuousObjectiveFunction::shared_ptr function,
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
}

void TestFunction::Initialize()
{
    ContinuousObjectiveFunction::shared_ptr square_objective_function(new SquareObjectiveFunction());

    std::vector<double> square_solution_values(2);
    square_solution_values[0] = M_SQRT2;
    square_solution_values[1] = M_SQRT2;
    IContinuousParameters::shared_ptr square_solution( new ContinuousParametersArray(square_solution_values));

    std::vector<double> square_start_point_values(2);
    square_start_point_values[0] = 11;
    square_start_point_values[1] = 7;
    IContinuousParameters::shared_ptr square_start_point( new ContinuousParametersArray(square_start_point_values));

    Register(square_objective_function, square_solution, square_start_point, "1/|x^2-2|", true);

//TODO fix
#ifdef BUILD_WITH_MPI
    k52::parallel::mpi::IdentifyableObjectsManager::Instance().RegisterObject( *square_objective_function );
    k52::parallel::mpi::IdentifyableObjectsManager::Instance().RegisterObject( *square_start_point );
#endif

    //---------

    ContinuousObjectiveFunction::shared_ptr simple_square_objective_function(new SimpleSquareObjectiveFunction());
    Register(simple_square_objective_function, square_solution, square_start_point, "(x^2-2)^2", false);

//TODO fix
#ifdef BUILD_WITH_MPI
    k52::parallel::mpi::IdentifyableObjectsManager::Instance().RegisterObject( *simple_square_objective_function );
#endif

    //---------
    ContinuousObjectiveFunction::shared_ptr difraction_objective_function(new DifractionObjectiveFunction());

    std::vector<double> zero_solution_values(2);
    zero_solution_values[0] = 0;
    zero_solution_values[1] = 0;
    IContinuousParameters::shared_ptr zero_solution( new ContinuousParametersArray(zero_solution_values));

    std::vector<double> difraction_start_point_values(2);
    difraction_start_point_values[0] = 100;
    difraction_start_point_values[1] = 100;
    IContinuousParameters::shared_ptr difraction_start_point( new ContinuousParametersArray(difraction_start_point_values));

    Register(difraction_objective_function, zero_solution, difraction_start_point, "SUMM( sin(Xi) / Xi )", true);
    
//TODO fix
#ifdef BUILD_WITH_MPI
    k52::parallel::mpi::IdentifyableObjectsManager::Instance().RegisterObject( *difraction_objective_function );
#endif

    //---------
    ContinuousObjectiveFunction::shared_ptr square_summ_objective_function(new SquareSummObjectiveFunction());
    Register(square_summ_objective_function, zero_solution, difraction_start_point, "SUMM( Xi^2 )", false);

//TODO fix
#ifdef BUILD_WITH_MPI
    k52::parallel::mpi::IdentifyableObjectsManager::Instance().RegisterObject( *square_summ_objective_function );
#endif

    //---------
    ContinuousObjectiveFunction::shared_ptr multiminimum_objective_function(new MultiminimumObjectiveFunction());

    Register(multiminimum_objective_function, zero_solution, difraction_start_point, "x sin(4 x) + 1.1y sin(2 y)", false);

//TODO fix
#ifdef BUILD_WITH_MPI
    k52::parallel::mpi::IdentifyableObjectsManager::Instance().RegisterObject( *multiminimum_objective_function );
#endif
}

}/* namespace optimization_tests */
}/* namespace k52 */
