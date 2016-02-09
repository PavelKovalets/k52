#include <k52/optimization/continuous_objective_function.h>

#include <stdexcept>

namespace k52
{
namespace optimization
{

double ContinuousObjectiveFunction::operator () (const IParameters* const parameters) const
{
    const IContinuousParameters* continuous_parameters = dynamic_cast<const IContinuousParameters*>(parameters);

    if (!continuous_parameters)
    {
        throw std::logic_error("ContinuousObjectiveFunction must accept IContinuousParameters");
    }

    return (*this) (continuous_parameters);
}

double ContinuousObjectiveFunction::operator () (const IContinuousParameters* const parameters) const
{
    return (*this) (parameters->GetValues());
}

}/* namespace optimization */
}/* namespace k52 */