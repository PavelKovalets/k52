#include "optimization_task_result.h"

#include <string>
#include <stdexcept>

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <boost/bind.hpp>
#include <k52/parallel/mpi/constants.h>
#include <k52/parallel/mpi/identifyable_objects_manager.h>

using ::k52::parallel::mpi::AsyncCallChain;

#endif

namespace k52
{
namespace optimization
{

OptimizationTaskResult::OptimizationTaskResult(const IParameters* optimal_parameters)

#ifdef BUILD_WITH_MPI
    : communicator_(), source_(0)
#endif

{
    optimal_parameters_ = IParameters::shared_ptr( optimal_parameters->Clone() );
}

IParameters::shared_ptr OptimizationTaskResult::get_optimal_parameters() const
{
    return optimal_parameters_;
}

#ifdef BUILD_WITH_MPI

AsyncCallChain::shared_ptr OptimizationTaskResult::ReceiveAsync(boost::mpi::communicator* communicator, int source)
{
    //TODO fix partial copypaste from CountObjectiveFunctionTask::Receive
    communicator_ = communicator;
    source_ = source;

    AsyncCallChain::shared_ptr call_chain = AsyncCallChain::CreateAsyncCallChain(
        boost::bind(&OptimizationTaskResult::ReceiveParametersIdAsyncCall, this)
    );
    call_chain->Add(boost::bind(&OptimizationTaskResult::ReceiveParametersAsyncCall, this));
    return call_chain;
}

void OptimizationTaskResult::Send(boost::mpi::communicator* communicator)
{
    //TODO fix copypaste from CountObjectiveFunctionTask::Send
    communicator->send(k52::parallel::mpi::constants::kServerRank,
                       k52::parallel::mpi::constants::kCommonTag,
                       k52::parallel::mpi::IdentifyableObjectsManager::GetId(*optimal_parameters_));
    optimal_parameters_->Send(communicator, k52::parallel::mpi::constants::kServerRank);
}

boost::mpi::request OptimizationTaskResult::ReceiveParametersIdAsyncCall()
{
    return communicator_->irecv(source_, k52::parallel::mpi::constants::kCommonTag, parameters_id_);
}

boost::optional<boost::mpi::request> OptimizationTaskResult::ReceiveParametersAsyncCall()
{
    const IParameters* parameters = dynamic_cast<const IParameters*>( k52::parallel::mpi::IdentifyableObjectsManager::Instance().GetObject(parameters_id_) );
    if (!parameters)
    {
        throw std::runtime_error("Unexpected parameters object received");
    }
    optimal_parameters_ = IParameters::shared_ptr( parameters->Clone() );

    //TODO implement ReceiveAsync for even more effectivness
    optimal_parameters_->Receive(communicator_, source_);

    return boost::optional<boost::mpi::request>();
}
#endif

}/* namespace optimization */
}/* namespace k52 */