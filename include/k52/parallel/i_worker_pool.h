#ifndef IWORKERPOOL_H_
#define IWORKERPOOL_H_

#include <vector>

#include <k52/parallel/i_task.h>
#include <k52/parallel/i_task_result.h>
#include <k52/parallel/worker_statistics.h>

namespace k52
{
namespace parallel
{

class IWorkerPool
{
public:
    typedef boost::shared_ptr<IWorkerPool> shared_ptr;

    virtual ~IWorkerPool(){}

    virtual std::vector< WorkerStatistics > GetStatistics() = 0;

    virtual std::vector< ITaskResult::shared_ptr > DoTasks (const std::vector<const ITask*>& tasks) = 0;
};

} /* parallel */
} /* k52 */
#endif /* IWORKERPOOL_H_ */
