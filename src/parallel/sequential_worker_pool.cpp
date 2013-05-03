#include "sequential_worker_pool.h"

namespace k52
{
namespace parallel
{

SequentialWorkerPool::SequentialWorkerPool(){}

bool SequentialWorkerPool::IsValid()
{
    return true;
}

std::vector<ITaskResult::shared_ptr> SequentialWorkerPool::DoTasks (const std::vector<const ITask*>& tasks)
{
    std::vector<ITaskResult::shared_ptr> results(tasks.size());

    for(size_t i = 0; i < tasks.size(); i++)
    {
        results[i] = ITaskResult::shared_ptr( tasks[i]->Perform() );
        statistics_.IncreaseCounted();
    }

    return results;
}

std::vector<WorkerStatistics> SequentialWorkerPool::GetStatistics()
{
    std::vector<WorkerStatistics> statistics(1);
    statistics[0] = statistics_;
    return statistics;
}

} /* parallel */
} /* k52 */
