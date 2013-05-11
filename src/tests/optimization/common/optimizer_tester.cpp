#include "optimizer_tester.h"

#include <iostream>

using ::std::cout;
using ::std::endl;
using ::k52::optimization::IParameters;

namespace k52
{
namespace optimization_tests
{

OptimizerTester::OptimizerTester()
{
    test_functions_ = TestFunction::get_test_functions();
}

void OptimizerTester::Test(k52::optimization::IOptimizer* optimizer)
{
    for (size_t i = 0; i<test_functions_.size(); i++)
    {
        TestSingleFunction( *(test_functions_[i]), optimizer );
    }
}

void OptimizerTester::TestSingleFunction(const TestFunction& function,
                                         k52::optimization::IOptimizer* optimizer)
{
    cout<<"---- Testing "<<function.get_analitical_form()<<" ----"<<endl;

    double solution_value = function.get_objective_function()(function.get_solution());
    IParameters::shared_ptr parameters (function.get_start_point()->Clone());
    optimizer->Optimize(function.get_objective_function(), parameters.get(), function.maximize());
    cout<<"Solution value for "<<function.get_analitical_form()<<" is "<<solution_value<<endl;
    cout<<"Found with optimizer "<<function.get_objective_function()(parameters.get())<<endl;

}


}/* namespace optimization_tests */
}/* namespace k52 */
