#ifndef WORKERPOOLFACTORY_H_
#define WORKERPOOLFACTORY_H_

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/parallel/i_worker_pool.h>

namespace k52
{
namespace parallel
{

class WorkerPoolFactory
{
public:
    enum WorkerPoolType
    {
        kThreadWorkerPool = 0,
        kMpiWorkerPool,
        kSequentialWorkerPool
    };

    static IWorkerPool::shared_ptr CreateWorkerPool(WorkerPoolType worker_pool_type);

    static bool CanCreateWorkerPool(WorkerPoolType worker_pool_type);

private:
    static bool was_mpi_worker_pool_created_;

    DISALLOW_COPY_AND_ASSIGN(WorkerPoolFactory);
};

} /* namespace parallel */
} /* namespace k52 */
#endif /* WORKERPOOLFACTORY_H_ */
