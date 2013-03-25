#ifndef IMPITASK_H_
#define IMPITASK_H_

#include <k52/parallel/i_task.h>
#include <k52/parallel/mpi/i_transferable.h>
#include <k52/parallel/mpi/i_mpi_task_result.h>

namespace k52
{
namespace parallel
{
namespace mpi
{

class IMpiTask : public k52::parallel::ITask, public k52::common::ICloneable, public ITransferable
{
public:
    typedef boost::shared_ptr<IMpiTask> shared_ptr;

    //TODO is it correct solving of contrvariant return problem
    virtual ITaskResult::shared_ptr Perform() const
    {
        return PerformMpi();
    }

    virtual IMpiTaskResult::shared_ptr PerformMpi() const = 0;

    virtual IMpiTaskResult::shared_ptr CreateEmptyResult() const = 0;

    virtual IMpiTask* Clone() const = 0;

    virtual void Send(boost::mpi::communicator* communicator, int target) const = 0;

    virtual void Receive(boost::mpi::communicator* communicator) = 0;
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* IMPITASK_H_ */
