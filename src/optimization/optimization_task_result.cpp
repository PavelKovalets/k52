#include "optimization_task_result.h"

#include <string>

//TODO remove explicit dependancy
#include <k52/optimization/params/continuous_parameters_array.h>

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <k52/parallel/mpi/constants.h>
#include <k52/parallel/mpi/identifyable_objects_manager.h>

#endif

namespace k52
{
namespace optimization
{

OptimizationTaskResult::OptimizationTaskResult(const IParameters* optimal_parameters)
{
    optimal_parameters_ = IParameters::shared_ptr( optimal_parameters->Clone() );
}

#ifdef BUILD_WITH_MPI

boost::mpi::request OptimizationTaskResult::ReceiveAsync(boost::mpi::communicator* communicator, int source)
{
    //TODO fix partial copypaste from CountObjectiveFunctionTask::Receive
    //TODO fix problem with Async receiving and ONLY THEN processing parameters_id
    //std::string parameters_id;
    //communicator->irecv(k52::parallel::mpi::constants::kServerRank, k52::parallel::mpi::constants::kCommonTag, parameters_id);
    //const IParameters* parameters = dynamic_cast<const IParameters*>( k52::parallel::mpi::IdentifyableObjectsManager::Instance().GetObject(parameters_id) );
    //received_parameters_ = IParameters::shared_ptr( parameters->Clone() );
    //received_parameters_->Receive(communicator);

    ContinuousParametersArray::shared_ptr parameters = boost::dynamic_pointer_cast<ContinuousParametersArray>(optimal_parameters_);
    if(parameters == NULL)
    {
        throw std::runtime_error("Currently only ContinuousParametersArray is supported in OptimizationTaskResult.");
    }

    return communicator->irecv(source, k52::parallel::mpi::constants::kCommonTag, parameters->values_);
}

void OptimizationTaskResult::Send(boost::mpi::communicator* communicator)
{
    //TODO fix copypaste from CountObjectiveFunctionTask::Send
    communicator->send(k52::parallel::mpi::constants::kServerRank,
                        k52::parallel::mpi::constants::kCommonTag,
                        k52::parallel::mpi::IdentifyableObjectsManager::GetId(*optimal_parameters_));
    optimal_parameters_->Send(communicator, k52::parallel::mpi::constants::kServerRank);
}

#endif

}/* namespace optimization */
}/* namespace k52 */