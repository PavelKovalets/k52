#include <k52/optimization/discrete_objective_function.h>

#include <stdexcept>

namespace k52
{
namespace optimization
{

double DiscreteObjectiveFunction::operator () (const IParameters* const parameters) const
{
    const IDiscreteParameters* discrete_parametrs = dynamic_cast<const IDiscreteParameters*>(parameters);

    if (!discrete_parametrs)
    {
        throw std::logic_error("DiscreteObjectiveFunction must accept IDiscreteParameters");
    }

    return (*this) (discrete_parametrs);
}

}/* namespace optimization */
}/* namespace k52 */