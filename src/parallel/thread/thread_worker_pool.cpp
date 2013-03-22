#ifdef BUILD_WITH_BOOST_THREAD

#include "thread_worker_pool.h"

namespace k52
{
namespace parallel
{
namespace thread
{

std::vector< ITaskResult::shared_ptr > ThreadWorkerPool::DoTasks (
    const std::vector<const ITask*>& tasks)
{
    std::vector< ITaskResult::shared_ptr > results(tasks.size());
    std::queue<ThreadWorkerPoolTask> tasks_queue;

    for(size_t i=0; i<tasks.size(); i++)
    {
        tasks_queue.push( ThreadWorkerPoolTask(tasks[i], &(results[i])) );
    }

    worker_pool_.DoTasks(tasks_queue);
    return results;
}

std::vector< WorkerStatistics > ThreadWorkerPool::GetStatistics()
{
    throw std::logic_error("getStatistics for ThreadWorkerPool is not yet implemented");
}

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif
