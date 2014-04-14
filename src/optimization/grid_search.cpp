#include <k52/optimization/grid_search.h>

#include <math.h>
#include <stdexcept>
#include <algorithm>

#include <k52/optimization/params/i_continuous_parameters.h>

#include "objective_function_counter.h"

using ::std::vector;

namespace k52
{
namespace optimization
{

GridSearch::GridSearch(double precision, double lower_bound, double upper_bound)
{
    fitness_counter_ = ObjectiveFunctionCounter::shared_ptr(new ObjectiveFunctionCounter(-1));
    lower_bound_ = lower_bound;
    upper_bound_ = upper_bound;
    precision_ = precision;
}

void GridSearch::Optimize(const IObjectiveFunction& function_to_optimize, IParameters* parametrs_to_optimize)
{
    IContinuousParameters* continuous_parameters = dynamic_cast<IContinuousParameters*> (parametrs_to_optimize);

    vector<double> initial_parameters = continuous_parameters->GetValues();

    int size_per_parameter = floor((upper_bound_ - lower_bound_)/precision_) + 1;

    if(size_per_parameter <= 0)
    {
        throw std::invalid_argument("upperBound, lowerBound, or precision was set incorrect");
    }

    size_t number_of_parameters = initial_parameters.size();
    size_t total_size = IntegerPow(size_per_parameter, number_of_parameters);

    vector<IContinuousParameters::shared_ptr> parameters_storages(total_size);
    vector<const IParameters*> parameters(total_size);
    //Fill all parameters
    for(size_t i = 0; i < total_size; i++)
    {
        vector<double> values(number_of_parameters);

        for(size_t j = 0; j < number_of_parameters; j++)
        {
            size_t index = i / IntegerPow(size_per_parameter, j);
            values[j] = (index % size_per_parameter) * precision_ + lower_bound_;
        }

        continuous_parameters->SetValues(values);
        parameters_storages[i] = IContinuousParameters::shared_ptr(continuous_parameters->Clone());

        //TODO FIX do not return local ptr
        parameters[i] = parameters_storages[i].get();
    }

    vector<double> counted_values = fitness_counter_->CountObjectiveFunctionValues(parameters, function_to_optimize);
    size_t best_index = distance(counted_values.begin(), max_element(counted_values.begin(), counted_values.end()));

    continuous_parameters->SetValues( parameters_storages[best_index]->GetValues() );
}

GridSearch* GridSearch::Clone() const
{
    throw std::logic_error("Cloning is not implemented for GridSearch");
}

#ifdef BUILD_WITH_MPI
void GridSearch::Send(boost::mpi::communicator* communicator, int target) const
{
    throw std::logic_error("Send is not implemented for GridSearch");
}

void GridSearch::Receive(boost::mpi::communicator* communicator)
{
    throw std::logic_error("Receive is not implemented for GridSearch");
}
#endif

size_t GridSearch::IntegerPow(size_t value, size_t pow)
{
    size_t result = 1;

    for(size_t i = 0; i < pow; i++)
    {
        result *= value;
    }

    return result;
}

}/* namespace optimization */
}/* namespace k52 */
