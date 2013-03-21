#ifndef SEQUENTIALWORKERPOOL_H_
#define SEQUENTIALWORKERPOOL_H_

#include <common/disallow_copy_and_assign.h>
#include <parallel/i_worker_pool.h>

namespace k52
{
namespace parallel
{

class SequentialWorkerPool : public IWorkerPool
{
public:
    typedef boost::shared_ptr<SequentialWorkerPool> shared_ptr;

    SequentialWorkerPool();

    virtual std::vector<ITaskResult::shared_ptr> DoTasks (const std::vector<const ITask*>& tasks);

    virtual std::vector<WorkerStatistics> GetStatistics();

private:
    WorkerStatistics statistics_;

    DISALLOW_COPY_AND_ASSIGN(SequentialWorkerPool);
};

} /* parallel */
} /* k52 */

#endif /* SEQUENTIALWORKERPOOL_H_ */
