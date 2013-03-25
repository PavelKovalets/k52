#ifndef IMPITASKRESULT_H_
#define IMPITASKRESULT_H_

#include <parallel/mpi/boost_mpi_declaration.h>
#include <parallel/i_task_result.h>

namespace k52
{
namespace parallel
{
namespace mpi
{

class IMpiTaskResult : public k52::parallel::ITaskResult
{
public:
    typedef boost::shared_ptr<IMpiTaskResult> shared_ptr;

    virtual boost::mpi::request ReceiveAsync(boost::mpi::communicator* communicator, int source) = 0;

    virtual void Send(boost::mpi::communicator* communicator) = 0;
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* IMPITASKRESULT_H_ */
