#ifndef THREADWORKERPOOLTASK_H_
#define THREADWORKERPOOLTASK_H_

#include <k52/parallel/i_worker_pool.h>

namespace k52
{
namespace parallel
{
namespace thread
{

class ThreadWorkerPoolTask
{
public:
    ThreadWorkerPoolTask();

    ThreadWorkerPoolTask(
        const ITask* task_to_do,
        ITaskResult::shared_ptr* result_to_be_written);

    void DoTask();

private:
    const ITask* task_to_do_;
    ITaskResult::shared_ptr* result_to_be_written_;
};

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif /* THREADWORKERPOOLTASK_H_ */
