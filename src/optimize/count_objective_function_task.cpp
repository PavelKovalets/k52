#include "count_objective_function_task.h"

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <parallel/mpi/constants.h>
#include <parallel/mpi/identifyable_objects_manager.h>

#endif

#include "objective_function_task_result.h"

namespace k52
{
namespace optimize
{

CountObjectiveFunctionTask::CountObjectiveFunctionTask()
    :parameters_(NULL), function_to_optimize_(NULL), was_created_(false) {}

CountObjectiveFunctionTask::CountObjectiveFunctionTask(
    const IParameters*  parameters,
    const IObjectiveFunction* function_to_optimize)
    :parameters_(parameters), function_to_optimize_(function_to_optimize), was_created_(true) {}

#ifdef BUILD_WITH_MPI

k52::parallel::mpi::IMpiTaskResult::shared_ptr CountObjectiveFunctionTask::PerformMpi() const
{
    double value = get_objective_function()->operator ()( get_parameters() );
    ObjectiveFunctionTaskResult::shared_ptr result ( new ObjectiveFunctionTaskResult() );
    result->set_objective_function_value(value);
    return result;
}

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

void CountObjectiveFunctionTask::Receive(boost::mpi::communicator* communicator)
{
    std::string objective_function_id;
    communicator->recv(k52::parallel::mpi::constants::kServerRank, k52::parallel::mpi::constants::kCommonTag, objective_function_id);
    const IObjectiveFunction* functionToOptimize = dynamic_cast<const IObjectiveFunction*>( k52::parallel::mpi::IdentifyableObjectsManager::Instance().GetObject(objective_function_id) );
    received_function_ = IObjectiveFunction::shared_ptr( functionToOptimize->Clone() );

    std::string parameters_id;
    communicator->recv(k52::parallel::mpi::constants::kServerRank, k52::parallel::mpi::constants::kCommonTag, parameters_id);
    const IParameters* parameters = dynamic_cast<const IParameters*>( k52::parallel::mpi::IdentifyableObjectsManager::Instance().GetObject(parameters_id) );
    received_parameters_ = IParameters::shared_ptr( parameters->Clone() );
    received_parameters_->Receive(communicator);
}
#else

//TODO use polymorphysm and fix conflict with base class
k52::parallel::ITaskResult::shared_ptr CountObjectiveFunctionTask::Perform() const
{
    double value = function_to_optimize_->operator ()(parameters_);
    ObjectiveFunctionTaskResult::shared_ptr result ( new ObjectiveFunctionTaskResult() );
    result->set_objective_function_value(value);
    return result;
}

#endif

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

}/* namespace optimize */
}/* namespace k52 */
