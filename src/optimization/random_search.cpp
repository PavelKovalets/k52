#include <k52/optimization/random_search.h>

#include <stdexcept>

#include <k52/common/random.h>
#include <k52/optimization/params/i_continuous_parameters.h>

#include "simple_parameters_processor.h"
#include "optimization_parameters_processor.h"

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

void RandomSearch::Optimize(const ContinuousObjectiveFunction &function_to_optimize,
    IContinuousParameters* parametrs_to_optimize,
    bool maximize)
{
    size_t vector_size = parametrs_to_optimize->GetValues().size();

    std::vector< IParameters::shared_ptr > random_parameters(number_of_random_points_);
    for(size_t i=0; i<number_of_random_points_; i++)
    {
        IContinuousParameters::shared_ptr tmp = IContinuousParameters::shared_ptr(parametrs_to_optimize->Clone());
        tmp->SetValues(GenerateRandomPoint(vector_size));
        random_parameters[i] = tmp;
    }

    IParameters::shared_ptr best_parameters =
            parameters_processor_->ProcessParameters(function_to_optimize, random_parameters, maximize);

    IContinuousParameters::shared_ptr best_continuous_parameters = boost::dynamic_pointer_cast<IContinuousParameters>(best_parameters);

    if (best_continuous_parameters)
    {
        parametrs_to_optimize->SetValues(best_continuous_parameters->GetValues());
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
