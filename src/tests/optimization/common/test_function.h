#ifndef TEST_FUNCTION_H_
#define TEST_FUNCTION_H_

#include <vector>
#include <string>

#include <boost/shared_ptr.hpp>

#include <k52/optimization/continuous_objective_function.h>
#include <k52/optimization/params/i_continuous_parameters.h>

namespace k52
{
namespace optimization_tests
{

class TestFunction
{
public:
    typedef boost::shared_ptr<TestFunction> shared_ptr;

    const optimization::ContinuousObjectiveFunction& get_objective_function() const;
    const optimization::IContinuousParameters* get_solution() const;
    const optimization::IContinuousParameters* get_start_point() const;
    std::string get_analitical_form() const;
    bool maximize() const;

    static void Register(optimization::ContinuousObjectiveFunction::shared_ptr function,
                         optimization::IContinuousParameters::shared_ptr solution,
                         optimization::IContinuousParameters::shared_ptr start_point,
                         std::string analitical_form,
                         bool maximize);
    static std::vector<TestFunction::shared_ptr> get_test_functions();

private:
    TestFunction(optimization::ContinuousObjectiveFunction::shared_ptr function,
                 optimization::IContinuousParameters::shared_ptr solution,
                 optimization::IContinuousParameters::shared_ptr start_point,
                 std::string analitical_form,
                 bool maximize);

    optimization::ContinuousObjectiveFunction::shared_ptr function_;
    optimization::IContinuousParameters::shared_ptr solution_;
    optimization::IContinuousParameters::shared_ptr start_point_;
    std::string analitical_form_;
    bool maximize_;

    static void Initialize();

    static bool was_initialized_;
    static std::vector<TestFunction::shared_ptr> test_functions_;
};

}/* namespace optimization_tests */
}/* namespace k52 */

#endif /* TEST_FUNCTION_H_ */
