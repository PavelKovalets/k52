#include <k52/optimization/random_search.h>

#include <stdexcept>

#include <k52/optimization/params/i_continuous_parameters.h>

#include "simple_parameters_processor.h"
#include "optimization_parameters_processor.h"
#include "random.h"

namespace k52
{
namespace optimization
{

RandomSearch::RandomSearch(size_t number_of_random_points,
                           double lower_bound,
                           double upper_bound,
                           const IOptimizer* optimizer):
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

void RandomSearch::Optimize(const IObjectiveFunction &function_to_optimize,
                      IParameters* parametrs_to_optimize,
                      bool maximize)
{
    IContinuousParameters* continuous_parameters = dynamic_cast<IContinuousParameters*> (parametrs_to_optimize);
    if(continuous_parameters == NULL)
    {
        throw std::invalid_argument("parametrs_to_optimize must be of type IContinuousParameters for RandomSearch");
    }
    size_t vector_size = continuous_parameters->GetValues().size();

    std::vector< IContinuousParameters::shared_ptr > random_parameters(number_of_random_points_);
    for(size_t i=0; i<number_of_random_points_; i++)
    {
        random_parameters[i] = IContinuousParameters::shared_ptr( continuous_parameters->Clone() );
        random_parameters[i]->SetValues( GenerateRandomPoint(vector_size) );
    }

    IContinuousParameters::shared_ptr best_parameters =
            parameters_processor_->ProcessParameters(function_to_optimize, random_parameters, maximize);

    continuous_parameters->SetValues(best_parameters->GetValues());
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

std::vector<double> RandomSearch::GenerateRandomPoint(size_t vector_size)
{
    std::vector<double> random_point(vector_size);
    for(size_t i=0; i<vector_size; i++)
    {
        random_point[i] = Random::Instance().GetContinuousRandomQuantity(lower_bound_, upper_bound_);
    }
    return random_point;
}

}/* namespace optimization */
}/* namespace k52 */
