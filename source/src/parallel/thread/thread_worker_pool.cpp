#ifdef BUILD_WITH_BOOST_THREAD

#include "thread_worker_pool.h"

namespace k52
{
namespace parallel
{
namespace thread
{

bool ThreadWorkerPool::IsValid()
{
    return AreAvailableWorkers();
}

std::vector< ITaskResult::shared_ptr > ThreadWorkerPool::DoTasks (
    const std::vector<const ITask*>& tasks)
{
    CheckAvailableWorkers();

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

bool ThreadWorkerPool::AreAvailableWorkers() const
{
    return worker_pool_.get_number_of_workers() >= 2;
}

void ThreadWorkerPool::CheckAvailableWorkers() const
{
    if(!AreAvailableWorkers())
    {
        throw std::runtime_error("No worker threads available. "
                        "There will be no performance gain using ThreadWorkerPool.");
    }
}

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif
