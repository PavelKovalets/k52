#ifndef ASYNC_CALL_CHAIN_H
#define ASYNC_CALL_CHAIN_H

#include <queue>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/optional.hpp>

#include <k52/parallel/mpi/boost_mpi_declaration.h>

namespace k52
{
namespace parallel
{
namespace mpi
{

class AsyncCallChain
{
public:
    typedef boost::shared_ptr<AsyncCallChain> shared_ptr;
    typedef boost::function<boost::optional<boost::mpi::request> ()> AsyncFunctionCall;

    static AsyncCallChain::shared_ptr CreateAsyncCallChain(AsyncFunctionCall first_call);

    AsyncCallChain(AsyncFunctionCall first_call);

    void Add(AsyncFunctionCall next_call);

    bool IsCurrentCallFinished();

    bool WillBeNextCall() const;

    void MakeNextCall();

private:
    std::queue<AsyncFunctionCall> calls_queue_;
    boost::shared_ptr< boost::optional< boost::mpi::request > > current_request_;
    bool current_request_finished_;
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* ASYNC_CALL_CHAIN_H */
