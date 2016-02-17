#include <iostream>
#include <fstream>

#include "optimizer_tester.h"
#include "optimizers_provider.h"
#include "test_functions_provider.h"

void OutputResults(std::ostream &out,
        const std::vector < std::vector < k52::optimization_tests::OptimizerTestResult::shared_ptr > >& results)
{
    out << "Function \t" << "Solution value \t";
    for (size_t j = 0; j < results[0].size(); j++)
    {
        out << results[0][j]->get_optimizer_name() << "\t";
    }
    out << std::endl;

    for (size_t i = 0; i < results.size(); i++)
    {
        out << results[i][0]->get_test_function()->get_analitical_form() << "\t" <<
        results[i][0]->get_test_function()->get_solution_value() << "\t" ;

        for (size_t j = 0; j < results[i].size(); j++)
        {
            out << results[i][j]->get_found_value() << "\t";
        }

        out << std::endl;
    }
}

int main()
{
    //Tester must be created first to register all objects correctly
    k52::optimization_tests::OptimizerTester tester;

    k52::optimization_tests::OptimizersProvider optimizersProvider;
    k52::optimization_tests::TestFunctionsProvider functionsProvider;

    std::vector < std::vector < k52::optimization_tests::OptimizerTestResult::shared_ptr > > results =
            tester.Test(optimizersProvider, functionsProvider);

    std::ofstream fileout("optimizers_output.txt");
    OutputResults(fileout, results);

    std::cout << "Finished" << std::endl;

    return 0;
}
