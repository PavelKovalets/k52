#include <k52/optimization/random_search.h>

#include <stdexcept>

#include <k52/common/random.h>
#include <k52/optimization/params/i_continuous_parameters.h>

#include "simple_parameters_processor.h"
#include "optimization_parameters_processor.h"

using ::std::vector;

namespace k52
{
namespace optimization
{

RandomSearch::RandomSearch(size_t number_of_random_points,
                           double lower_bound,
                           double upper_bound,
                           const ContinuousOptimizer* optimizer) :
    number_of_random_points_(number_of_random_points),
    lower_bound_(lower_bound),
    upper_bound_(upper_bound)
{
    if(optimizer == NULL)
    {
        parameters_processor_ = SimpleParametersProcessor::shared_ptr(
            new SimpleParametersProcessor()
        );
    }
    else
    {
        parameters_processor_ = OptimizationParametersProcessor::shared_ptr(
            new OptimizationParametersProcessor(optimizer)
        );
    }
}

vector<double> RandomSearch::FindOptimalParameters(const vector<double>& initial_values)
{
    size_t vector_size = initial_values.size();

    vector< IParameters::shared_ptr > random_parameters(number_of_random_points_);
    for(size_t i=0; i<number_of_random_points_; i++)
    {
        IContinuousParameters::shared_ptr tmp = IContinuousParameters::shared_ptr(get_parameters_to_optimize()->Clone());
        tmp->SetValues(Random::Instance().GenerateRandomVector(vector_size, lower_bound_, upper_bound_));
        random_parameters[i] = tmp;
    }

    IParameters::shared_ptr best_parameters =
            parameters_processor_->ProcessParameters(*get_function_to_optimize(), random_parameters, get_maximize());

    IContinuousParameters::shared_ptr best_continuous_parameters = boost::dynamic_pointer_cast<IContinuousParameters>(best_parameters);

    if (best_continuous_parameters)
    {
        return best_continuous_parameters->GetValues();
    }
    else
    {
        throw std::logic_error("parameters_processor must return ContinuousParameters for same input");
    }
}

RandomSearch* RandomSearch::Clone() const
{
    throw std::logic_error("Cloning is not implemented for RandomSearch");
}

#ifdef BUILD_WITH_MPI
void RandomSearch::Send(boost::mpi::communicator* communicator, int target) const
{
    throw std::logic_error("Send is not implemented for RandomSearch");
}

void RandomSearch::Receive(boost::mpi::communicator* communicator, int source)
{
    throw std::logic_error("Receive is not implemented for RandomSearch");
}
#endif

}/* namespace optimization */
}/* namespace k52 */
