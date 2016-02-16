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

    virtual IMpiTaskResult* Perform() const = 0;

    virtual IMpiTaskResult::shared_ptr CreateEmptyResult() const = 0;

    virtual IMpiTask* Clone() const = 0;
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* IMPITASK_H_ */
