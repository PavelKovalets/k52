#include <iostream>

#ifdef BUILD_WITH_MPI
#include <k52/parallel/mpi/identifyable_objects_manager.h>
#endif


#include <k52/optimization/random_search.h>
#include <k52/optimization/bounded_nelder_mead.h>
#include "../common/test_function.h"

using namespace std;
using namespace k52::optimization;
using namespace k52::optimization_tests;

int main()
{
    double lower_bound = -10000;
    double upper_bound = 10000;
    double l = 10;
    double precision = 1e-10;
    size_t number_of_points = 30;

    k52::optimization::BoundedNelderMead bounded_nelder_mead(l,
                                                             precision,
                                                             lower_bound,
                                                             upper_bound);

    std::vector<TestFunction::shared_ptr> test_functions = TestFunction::get_test_functions();

    k52::optimization::RandomSearch random_search(number_of_points,
                                                  lower_bound,
                                                  upper_bound,
                                                  &bounded_nelder_mead);
    k52::optimization::IOptimizer* optimizer = &random_search;

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
