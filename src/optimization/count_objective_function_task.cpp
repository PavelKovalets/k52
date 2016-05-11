#include "count_objective_function_task.h"

#include <stdexcept>

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <k52/parallel/mpi/constants.h>
#include <k52/parallel/mpi/identifyable_objects_manager.h>

#endif

#include "objective_function_task_result.h"

namespace k52
{
namespace optimization
{

CountObjectiveFunctionTask::CountObjectiveFunctionTask()
    : function_to_optimize_(NULL)
    , parameters_(NULL)
    , was_created_(false)
{}

CountObjectiveFunctionTask::CountObjectiveFunctionTask(
    const IParameters*  parameters,
    const IObjectiveFunction* function_to_optimize)
    : function_to_optimize_(function_to_optimize)
    , parameters_(parameters)
    , was_created_(true) {}

#ifdef BUILD_WITH_MPI

k52::parallel::mpi::IMpiTaskResult::shared_ptr CountObjectiveFunctionTask::CreateEmptyResult() const
{
    return ObjectiveFunctionTaskResult::shared_ptr ( new ObjectiveFunctionTaskResult() );
}

CountObjectiveFunctionTask* CountObjectiveFunctionTask::Clone() const
{
    CountObjectiveFunctionTask* clone = NULL;
    if(was_created_)
    {
        clone = new CountObjectiveFunctionTask(parameters_, function_to_optimize_);
    }
    else
    {
        clone = new CountObjectiveFunctionTask();
        if(received_function_ != NULL)
        {
            clone->received_function_ = IObjectiveFunction::shared_ptr( received_function_->Clone() );
        }
        if(received_parameters_ != NULL)
        {
            clone->received_parameters_ = IParameters::shared_ptr( received_parameters_->Clone() );
        }
    }
    return clone;
}

void CountObjectiveFunctionTask::Send(boost::mpi::communicator* communicator, int target) const
{
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, k52::parallel::mpi::IdentifyableObjectsManager::GetId(*get_objective_function()));
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, k52::parallel::mpi::IdentifyableObjectsManager::GetId(*get_parameters()));
    get_parameters()->Send(communicator, target);
}

void CountObjectiveFunctionTask::Receive(boost::mpi::communicator* communicator, int source)
{
    std::string objective_function_id;
    communicator->recv(source, k52::parallel::mpi::constants::kCommonTag, objective_function_id);
    const IObjectiveFunction* function_to_optimize = dynamic_cast<const IObjectiveFunction*>( k52::parallel::mpi::IdentifyableObjectsManager::Instance().GetObject(objective_function_id) );
    if (!function_to_optimize)
    {
        throw std::runtime_error("Unexpected function object received");
    }
    received_function_ = IObjectiveFunction::shared_ptr( function_to_optimize->Clone() );

    std::string parameters_id;
    communicator->recv(source, k52::parallel::mpi::constants::kCommonTag, parameters_id);
    const IParameters* parameters = dynamic_cast<const IParameters*>( k52::parallel::mpi::IdentifyableObjectsManager::Instance().GetObject(parameters_id) );
    if (!parameters)
    {
        throw std::runtime_error("Unexpected parameters object received");
    }
    received_parameters_ = IParameters::shared_ptr( parameters->Clone() );
    received_parameters_->Receive(communicator, source);
}

k52::parallel::mpi::IMpiTaskResult* CountObjectiveFunctionTask::Perform() const

#else

k52::parallel::ITaskResult* CountObjectiveFunctionTask::Perform() const

#endif
{
    double value = get_objective_function()->operator ()( get_parameters() );
    ObjectiveFunctionTaskResult* result = new ObjectiveFunctionTaskResult();
    result->set_objective_function_value(value);
    return result;
}

const IObjectiveFunction* CountObjectiveFunctionTask::get_objective_function() const
{
    if(was_created_)
    {
        return function_to_optimize_;
    }
    else
    {
        return received_function_.get();
    }
}

const IParameters* CountObjectiveFunctionTask::get_parameters() const
{
    if(was_created_)
    {
        return parameters_;
    }
    else
    {
        return received_parameters_.get();
    }
}

}/* namespace optimization */
}/* namespace k52 */
