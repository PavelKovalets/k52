#include "thread_worker_pool_task.h"

namespace k52
{
namespace parallel
{
namespace thread
{

ThreadWorkerPoolTask::ThreadWorkerPoolTask()
    :task_to_do_(NULL), result_to_be_written_(NULL) {}

ThreadWorkerPoolTask::ThreadWorkerPoolTask(
    const ITask* task_to_do,
    ITaskResult::shared_ptr* result_to_be_written)
        :task_to_do_(task_to_do), result_to_be_written_(result_to_be_written) {}

void ThreadWorkerPoolTask::DoTask()
{
    (*result_to_be_written_) = task_to_do_->Perform();
}

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */
