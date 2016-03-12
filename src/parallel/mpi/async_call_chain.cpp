#ifdef BUILD_WITH_MPI

#include <k52/parallel/mpi/async_call_chain.h>

#include <boost/mpi.hpp>
#include <boost/mpi/request.hpp>

namespace k52
{
namespace parallel
{
namespace mpi
{

AsyncCallChain::shared_ptr AsyncCallChain::CreateAsyncCallChain(AsyncFunctionCall first_call)
{
    return AsyncCallChain::shared_ptr(new AsyncCallChain(first_call));
}

AsyncCallChain::AsyncCallChain(AsyncFunctionCall first_call)
{
    current_request_ = boost::shared_ptr< boost::optional<boost::mpi::request> >(
        new boost::optional< boost::mpi::request >()
    );
    current_request_finished_ = false;

    Add(first_call);
}

void AsyncCallChain::Add(AsyncFunctionCall next_call)
{
    calls_queue_.push(next_call);
}

bool AsyncCallChain::IsCurrentCallFinished()
{
    //It is necessary to store state in a member variable because after
    //boost::mpi::request.test() was positive another call to it will throw an exception.
    if(current_request_finished_)
    {
        return true;
    }

    if(current_request_->is_initialized())
    {
        //There is a real request
        current_request_finished_ = current_request_->get().test().is_initialized();
    }
    else
    {
        //There is no actual request to wait - we can continue
        current_request_finished_ = true;
    }

    return current_request_finished_;
}

bool AsyncCallChain::WillBeNextCall() const
{
    return !calls_queue_.empty();
}

void AsyncCallChain::MakeNextCall()
{
    if(! IsCurrentCallFinished() )
    {
        throw std::runtime_error("You cannot make next call"
            " in chain untill current one is not finished.");
    }

    AsyncFunctionCall next_call = calls_queue_.front();
    calls_queue_.pop();
    (*current_request_) = next_call();
    current_request_finished_ = false;
}

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif
