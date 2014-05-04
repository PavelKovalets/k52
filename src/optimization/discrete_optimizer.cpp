#include <k52/optimization/discrete_optimizer.h>

namespace k52
{
namespace optimization
{

void DiscreteOptimizer::Optimize(const IObjectiveFunction &function_to_optimize,
    IParameters* parametrs_to_optimize,
    bool maximize)
{
    IDiscreteParameters* discrete_parametrs_to_optimize = dynamic_cast<IDiscreteParameters*>(parametrs_to_optimize);

    if (!discrete_parametrs_to_optimize)
    {
        throw std::logic_error("DiscreteOptimizer must accept IDiscreteParameters");
    }

    const DiscreteObjectiveFunction& discrete_function_to_optimize = dynamic_cast<const DiscreteObjectiveFunction&>(function_to_optimize);

    this->Optimize(discrete_function_to_optimize, discrete_parametrs_to_optimize, maximize);
}

}/* namespace optimization */
}/* namespace k52 */