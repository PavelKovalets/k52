#ifndef TEST_OBJECTIVE_FUNCTIONS_H_
#define TEST_OBJECTIVE_FUNCTIONS_H_

#include <vector>
#include <string>
#include <math.h>

#include <boost/shared_ptr.hpp>

#include <k52/optimization/i_objective_function.h>
#include <k52/optimization/params/i_continuous_parameters.h>

namespace k52
{
namespace optimization_tests
{

class SquareObjectiveFunction : public k52::optimization::IObjectiveFunction
{
public:

    virtual double operator () (const k52::optimization::IParameters* const parameters) const
    {
        const k52::optimization::IContinuousParameters* const continuous_parametrs =
                dynamic_cast<const k52::optimization::IContinuousParameters* const>(parameters);

        double summ = 0;
        std::vector<double> values = continuous_parametrs->GetValues();

        for(size_t i=0; i<values.size(); i++)
        {
            double value = values[i];
            summ += 1/fabs(value*value - 2);
        }

        return -summ;
    }

    virtual IObjectiveFunction* Clone() const
    {
        return new SquareObjectiveFunction();
    }
};

}/* namespace optimization_tests */
}/* namespace k52 */

#endif /* TEST_OBJECTIVE_FUNCTIONS_H_ */
