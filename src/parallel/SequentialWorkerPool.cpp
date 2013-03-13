#include "SequentialWorkerPool.h"

namespace k52
{
namespace parallel
{

std::vector< ITaskResult::shared_ptr > SequentialWorkerPool::doTasks (const std::vector<const ITask*>& tasks)
{
	std::vector< ITaskResult::shared_ptr > results(tasks.size());

	for(int i = 0; i < tasks.size(); i++)
	{
		results[i] = tasks[i]->perform();
	}

	return results;
}

} /* parallel */
} /* k52 */
