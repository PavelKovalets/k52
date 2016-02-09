#include "objective_function_task_result.h"

#ifdef BUILD_WITH_MPI

#include <boost/mpi.hpp>
#include <boost/bind.hpp>
#include <k52/parallel/mpi/constants.h>

#endif

namespace k52
{
namespace optimization
{

double ObjectiveFunctionTaskResult::get_objective_function_value() const
{
    return objective_function_value_;
}

void ObjectiveFunctionTaskResult::set_objective_function_value(double objective_function_value)
{
    objective_function_value_ = objective_function_value;
}

#ifdef BUILD_WITH_MPI

k52::parallel::mpi::AsyncCallChain::shared_ptr ObjectiveFunctionTaskResult::ReceiveAsync(boost::mpi::communicator* communicator, int source)
{
    //TODO fix common copypaste of following 2 lines
    communicator_ = communicator;
    source_ = source;
    return k52::parallel::mpi::AsyncCallChain::CreateAsyncCallChain(boost::bind(&ObjectiveFunctionTaskResult::ReceiveAsyncCall, this));
}

void ObjectiveFunctionTaskResult::Send(boost::mpi::communicator* communicator)
{
    communicator->send(k52::parallel::mpi::constants::kServerRank, k52::parallel::mpi::constants::kCommonTag, objective_function_value_);
}

boost::mpi::request ObjectiveFunctionTaskResult::ReceiveAsyncCall()
{
    return communicator_->irecv(source_, k52::parallel::mpi::constants::kCommonTag, objective_function_value_);
}

#endif

}/* namespace optimization */
}/* namespace k52 */
