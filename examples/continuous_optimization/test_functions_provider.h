#ifndef K52_TEST_FUNCTIONS_PROVIDER_H
#define K52_TEST_FUNCTIONS_PROVIDER_H

#include "test_function.h"

namespace k52
{
namespace optimization_tests
{

class TestFunctionsProvider
{
public:
    TestFunctionsProvider();

    std::vector<TestFunction::shared_ptr> get_test_functions() const;

protected:
    TestFunction::shared_ptr get_square() const;
    TestFunction::shared_ptr get_simple_square() const;
    TestFunction::shared_ptr get_difraction() const;
    TestFunction::shared_ptr get_square_summ() const;
    TestFunction::shared_ptr get_multiminimum() const;

private:
    DISALLOW_COPY_AND_ASSIGN(TestFunctionsProvider);

    ::k52::optimization::IContinuousParameters::shared_ptr square_solution_;
    ::k52::optimization::IContinuousParameters::shared_ptr square_start_point_;

    ::k52::optimization::IContinuousParameters::shared_ptr zero_solution_;
    ::k52::optimization::IContinuousParameters::shared_ptr difraction_start_point_;
};

}/* namespace optimization_tests */
}/* namespace k52 */

#endif //K52_TEST_FUNCTIONS_PROVIDER_H
