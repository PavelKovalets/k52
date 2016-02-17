#include <k52/optimization/simulated_annealing.h>

using ::std::vector;

namespace k52
{
namespace optimization
{

vector<double> SimulatedAnnealing::FindOptimalParameters(const vector<double>& initial_values)
{
    vector<double> optimal_values = initial_values;


    return optimal_values;
}

std::string SimulatedAnnealing::get_name() const
{
    return "Simulated Annealing";
}

}/* namespace optimization */
}/* namespace k52 */