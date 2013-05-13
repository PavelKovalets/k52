#include "optimization_task.h"

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <k52/parallel/mpi/constants.h>
#include <k52/parallel/mpi/identifyable_objects_manager.h>

#endif

//TODO implement to use IOptimizer in general
#include <k52/optimization/bounded_nelder_mead.h>

#include "optimization_task_result.h"

namespace k52
{
namespace optimization
{

OptimizationTask::OptimizationTask()
{
#ifdef BUILD_WITH_MPI
    //TODO remove temporary fix
    BoundedNelderMead bnm(1,1,1,1);
    k52::parallel::mpi::IdentifyableObjectsManager::Instance().RegisterObject(bnm);
#endif
}

OptimizationTask::OptimizationTask(const IOptimizer* optimizer,
                     const IParameters* initial_parameters,
                     const IObjectiveFunction* function_to_optimize,
                     bool maximize)
    : maximize_(maximize)
{
    initial_parameters_ = IParameters::shared_ptr( initial_parameters->Clone() );
    function_to_optimize_ = IObjectiveFunction::shared_ptr( function_to_optimize->Clone() );
    optimizer_ = IOptimizer::shared_ptr( optimizer->Clone() );
}

#ifdef BUILD_WITH_MPI

k52::parallel::mpi::IMpiTaskResult::shared_ptr OptimizationTask::CreateEmptyResult() const
{
    return OptimizationTaskResult::shared_ptr( new OptimizationTaskResult(initial_parameters_.get()) );
}

OptimizationTask* OptimizationTask::Clone() const
{
    if(initial_parameters_ != NULL &&
       function_to_optimize_!= NULL &&
       optimizer_ != NULL )
    {
        return new OptimizationTask(optimizer_.get(),
                                    initial_parameters_.get(),
                                    function_to_optimize_.get(),
                                    maximize_);
    }
    else
    {
        return new OptimizationTask();
    }
}

void OptimizationTask::Send(boost::mpi::communicator* communicator, int target) const
{
    communicator->send(target,
                       k52::parallel::mpi::constants::kCommonTag,
                       k52::parallel::mpi::IdentifyableObjectsManager::GetId(*function_to_optimize_));
    communicator->send(target,
                       k52::parallel::mpi::constants::kCommonTag,
                       k52::parallel::mpi::IdentifyableObjectsManager::GetId(*initial_parameters_));
    initial_parameters_->Send(communicator, target);
    communicator->send(target,
                       k52::parallel::mpi::constants::kCommonTag,
                       k52::parallel::mpi::IdentifyableObjectsManager::GetId(*optimizer_));
    optimizer_->Send(communicator, target);
    communicator->send(target, k52::parallel::mpi::constants::kCommonTag, maximize_);
}

void OptimizationTask::Receive(boost::mpi::communicator* communicator)
{
    std::string objective_function_id;
    communicator->recv(k52::parallel::mpi::constants::kServerRank,
                       k52::parallel::mpi::constants::kCommonTag,
                       objective_function_id);
    const IObjectiveFunction* function_to_optimize =
        dynamic_cast<const IObjectiveFunction*>(
            k52::parallel::mpi::IdentifyableObjectsManager::Instance()
                .GetObject(objective_function_id)
        );
    function_to_optimize_ = IObjectiveFunction::shared_ptr( function_to_optimize->Clone() );

    std::string parameters_id;
    communicator->recv(k52::parallel::mpi::constants::kServerRank,
                       k52::parallel::mpi::constants::kCommonTag,
                       parameters_id);
    const IParameters* parameters =
        dynamic_cast<const IParameters*>(
            k52::parallel::mpi::IdentifyableObjectsManager::Instance()
                .GetObject(parameters_id)
        );
    initial_parameters_ = IParameters::shared_ptr( parameters->Clone() );
    initial_parameters_->Receive(communicator);

    std::string optimizer_id;
    communicator->recv(k52::parallel::mpi::constants::kServerRank,
                       k52::parallel::mpi::constants::kCommonTag,
                       optimizer_id);
    const IOptimizer* optimizer =
        dynamic_cast<const IOptimizer*>(
            k52::parallel::mpi::IdentifyableObjectsManager::Instance()
                .GetObject(optimizer_id)
        );
    optimizer_ = IOptimizer::shared_ptr( optimizer->Clone() );
    optimizer_->Receive(communicator);

    communicator->recv(k52::parallel::mpi::constants::kServerRank,
                       k52::parallel::mpi::constants::kCommonTag,
                       maximize_);
}

k52::parallel::mpi::IMpiTaskResult* OptimizationTask::Perform() const

#else

k52::parallel::ITaskResult* OptimizationTask::Perform() const

#endif
{
    optimizer_->Optimize(*function_to_optimize_, initial_parameters_.get(), maximize_);

    OptimizationTaskResult* result = new OptimizationTaskResult(initial_parameters_.get());
    return result;
}

}/* namespace optimization */
}/* namespace k52 */