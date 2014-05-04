#include <k52/optimization/continuous_optimizer.h>

#include <stdexcept>

namespace k52
{
namespace optimization
{

void ContinuousOptimizer::Optimize(const IObjectiveFunction &function_to_optimize,
    IParameters* parametrs_to_optimize,
    bool maximize)
{
    IContinuousParameters* continuous_parametrs_to_optimize = dynamic_cast<IContinuousParameters*>(parametrs_to_optimize);

    if (!continuous_parametrs_to_optimize)
    {
        throw std::logic_error("ContinuousOptimizer must accept IContinuousParameters");
    }

    const ContinuousObjectiveFunction& continuous_function_to_optimize = dynamic_cast<const ContinuousObjectiveFunction&>(function_to_optimize);

    this->Optimize(continuous_function_to_optimize, continuous_parametrs_to_optimize, maximize);
}

}/* namespace optimization */
}/* namespace k52 */