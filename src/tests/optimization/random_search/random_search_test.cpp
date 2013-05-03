#include <iostream>

#include <k52/optimization/random_search.h>
#include "../common/test_function.h"

using namespace std;
using namespace k52::optimization;
using namespace k52::optimization_tests;

int main()
{
    double lower_bound = -10000;
    double upper_bound = 10000;
    size_t number_of_points = 1000000;
    k52::optimization::RandomSearch random_search(number_of_points, lower_bound, upper_bound);
    k52::optimization::IOptimizer* optimizer = &random_search;

    std::vector<TestFunction::shared_ptr> test_functions = TestFunction::get_test_functions();

    //TODO fix copypaste
    for (size_t i = 0; i<test_functions.size(); i++)
    {
        TestFunction& current_test_function = *test_functions[i];
        double solution_value = current_test_function.get_objective_function()(current_test_function.get_solution());
        IParameters::shared_ptr parameters (current_test_function.get_start_point()->Clone());
        optimizer->Optimize(current_test_function.get_objective_function(), parameters.get(), current_test_function.maximize());
        cout<<"Solution value for "<<current_test_function.get_analitical_form()<<" is "<<solution_value<<endl;
        cout<<"Found with RandomSearch "<<current_test_function.get_objective_function()(parameters.get())<<endl;

    }
    return 0;
}
