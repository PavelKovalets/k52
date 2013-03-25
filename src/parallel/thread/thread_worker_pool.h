#ifndef THREADWORKERPOOL_H_
#define THREADWORKERPOOL_H_

#ifdef BUILD_WITH_BOOST_THREAD

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/parallel/i_worker_pool.h>

#include "thread_worker_pool_task.h"
#include "thread_worker_pool_templated.h"

namespace k52
{
namespace parallel
{
namespace thread
{

class ThreadWorkerPool : public IWorkerPool
{
public:
    typedef boost::shared_ptr<ThreadWorkerPool> shared_ptr;

    ThreadWorkerPool() {}

    virtual std::vector< ITaskResult::shared_ptr > DoTasks(
        const std::vector<const ITask*>& tasks);

    virtual std::vector< WorkerStatistics > GetStatistics();

private:
    ThreadWorkerPoolTemplated<ThreadWorkerPoolTask> worker_pool_;

    DISALLOW_COPY_AND_ASSIGN(ThreadWorkerPool);
};

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif

#endif /* THREADWORKERPOOL_H_ */
