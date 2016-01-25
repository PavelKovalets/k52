#include "optimizer_tester.h"
#include "test_functions_provider.h"

#include <iostream>

using ::std::cout;
using ::std::endl;
using ::k52::optimization::IContinuousParameters;
using ::k52::optimization::ContinuousOptimizer;

namespace k52
{
namespace optimization_tests
{

void OptimizerTester::Test(ContinuousOptimizer* optimizer)
{
    TestFunctionsProvider provider;
    std::vector<TestFunction::shared_ptr> test_functions = provider.get_test_functions();

    for (size_t i = 0; i<test_functions.size(); i++)
    {
        TestSingleFunction( *(test_functions[i]), optimizer );
    }
}

void OptimizerTester::TestSingleFunction(const TestFunction& function,
                                         ContinuousOptimizer* optimizer)
{
    cout<<"---- Testing "<<function.get_analitical_form()<<" "
        << (function.maximize() ? "max" : "min") << " ----"<<endl;

    const k52::optimization::ContinuousObjectiveFunction& objective_function
        = function.get_objective_function();

    const IContinuousParameters* solution = function.get_solution();
    double solution_value = objective_function(solution);

    const IContinuousParameters* start_point = function.get_start_point();
    cout<<"Starting at point"<<endl;
    PrintParameters(start_point);
    IContinuousParameters::shared_ptr parameters (start_point->Clone());
    optimizer->Optimize(objective_function, parameters.get(), function.maximize());

    const IContinuousParameters* found_solution = parameters.get();
    double found_value = objective_function(found_solution);


    cout<<"The solution value is " <<solution_value<<" at point"<<endl;
    PrintParameters(solution);

    cout<<"The value found is "<<found_value<<" at point"<<endl;
    PrintParameters(found_solution);

    cout<<endl;
}

void OptimizerTester::PrintParameters(const IContinuousParameters* parameters) const
{
    std::vector<double> values = parameters->GetValues();
    cout.precision(15);

    cout<<"[ ";
    for(size_t i=0; i<values.size(); i++)
    {
        cout<< values[i];
        if(i != values.size() - 1)
        {
            cout<<"; ";
        }
    }
    cout<<" ]"<<endl;
}

}/* namespace optimization_tests */
}/* namespace k52 */
