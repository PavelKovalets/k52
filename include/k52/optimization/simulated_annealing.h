#ifndef SIMULATEDANNEALING_H_
#define SIMULATEDANNEALING_H_

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/optimization/continuous_optimizer.h>

namespace k52
{
namespace optimization
{

class SimulatedAnnealing : ContinuousOptimizer
{
public:
    SimulatedAnnealing() {}
    virtual std::string get_name() const;

protected:
    virtual std::vector<double> FindOptimalParameters(const std::vector<double>& initial_values);

private:

    DISALLOW_COPY_AND_ASSIGN(SimulatedAnnealing);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* SIMULATEDANNEALING_H_ */
