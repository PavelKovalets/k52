#include <iostream>

#include <k52/optimization/bounded_nelder_mead.h>
#include "../common/test_function.h"

using namespace std;
using namespace k52::optimization;
using namespace k52::optimization_tests;

int main()
{
    cout<<"Hello from optimization tests"<<endl;
    double l = 10;
    double precision = 1e-9;
    double lower_bound = -10000;
    double upper_bound = 10000;
    k52::optimization::BoundedNelderMead bounded_nelder_mead(l, precision, lower_bound, upper_bound);
    k52::optimization::IOptimizer* optimizer = &bounded_nelder_mead;

    std::vector<TestFunction::shared_ptr> test_functions = TestFunction::get_test_functions();

    for (size_t i = 0; i<test_functions.size(); i++)
    {
        TestFunction& current_test_function = *test_functions[i];
        double solution_value = current_test_function.get_objective_function()(current_test_function.get_solution());
        IParameters::shared_ptr parameters (current_test_function.get_start_point()->Clone());
        optimizer->Optimize(current_test_function.get_objective_function(), parameters.get());
        cout<<"Solution value for "<<current_test_function.get_analitical_form()<<" is "<<solution_value<<endl;
        cout<<"Found with BoundedNelderMead "<<current_test_function.get_objective_function()(parameters.get())<<endl;

    }
    return 0;
}
