#include <k52/optimization/simulated_annealing.h>
#include <cmath>
#include <stdexcept>
#include <k52/common/random.h>

using ::std::vector;
using ::k52::common::Random;

namespace k52
{
namespace optimization
{

SimulatedAnnealing::SimulatedAnnealing(
        size_t max_number_of_iterations,
        double min_parameter_value,
        double max_parameter_value)
        : max_number_of_iterations_(max_number_of_iterations),
          min_parameter_value_(min_parameter_value),
          max_parameter_value_(max_parameter_value)
{}

std::string SimulatedAnnealing::get_name() const
{
    return "Simulated Annealing";
}

SimulatedAnnealing* SimulatedAnnealing::Clone() const
{
    throw std::logic_error("Cloning is not implemented for SimulatedAnnealing");
}

#ifdef BUILD_WITH_MPI
void SimulatedAnnealing::Send(boost::mpi::communicator* communicator, int target) const
{
    throw std::logic_error("Send is not implemented for SimulatedAnnealing");
}

void SimulatedAnnealing::Receive(boost::mpi::communicator* communicator, int source)
{
    throw std::logic_error("Receive is not implemented for SimulatedAnnealing");
}
#endif

vector<double> SimulatedAnnealing::FindOptimalParameters(const vector<double>& initial_parameters)
{
    vector<double> current_parameters = initial_parameters;

    for (size_t i = 1; i <= max_number_of_iterations_; ++i)
    {
        vector<double> neighbour = GetRandomNeighbour(current_parameters);
        double current_value = CountObjectiveFunctionValueToMinimize(current_parameters);
        double neighbour_value = CountObjectiveFunctionValueToMinimize(neighbour);

        double t = CountTemperature(i);
        double probability = CountAcceptanceProbability(current_value, neighbour_value, t);

        if (Random::Instance().CheckEventOutcome(probability))
        {
            current_parameters = neighbour;
        }
    }

    return current_parameters;
}

double SimulatedAnnealing::CountTemperature(size_t current_iteration) const
{
    //The annealing schedule is linear in default implementation
    return ( ( (double)(max_number_of_iterations_ - current_iteration) ) / ( (double)max_number_of_iterations_ ) );
}

double SimulatedAnnealing::CountAcceptanceProbability(double current_value, double new_value, double temperature)
{
    if (temperature < 0)
    {
        throw std::runtime_error("Negative temperature");
    }

    if (new_value < current_value)
    {
        return 1;
    }
    else
    {
        return std::exp( (current_value - new_value) / temperature );
    }
}

std::vector<double> SimulatedAnnealing::GetRandomNeighbour(const std::vector<double> &values)
{
    int index_to_change = Random::Instance().GetUniformlyDistributedDiscreteRandomQuantity(0, values.size() - 1);
    double new_parameter_value = Random::Instance().GetContinuousRandomQuantity(min_parameter_value_, max_parameter_value_);

    vector<double> neighbour = values;
    neighbour[index_to_change] = new_parameter_value;
    return neighbour;
}

}/* namespace optimization */
}/* namespace k52 */