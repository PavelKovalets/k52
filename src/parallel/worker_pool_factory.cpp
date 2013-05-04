#include <k52/parallel/worker_pool_factory.h>

#include <stdexcept>

#include "sequential_worker_pool.h"
using ::k52::parallel::SequentialWorkerPool;

#ifdef BUILD_WITH_BOOST_THREAD
#include "thread/thread_worker_pool.h"
using ::k52::parallel::thread::ThreadWorkerPool;
#endif

#ifdef BUILD_WITH_MPI
#include "mpi/mpi_worker_pool.h"
using ::k52::parallel::mpi::MpiWorkerPool;
#endif

namespace k52
{
namespace parallel
{

IWorkerPool::shared_ptr WorkerPoolFactory::CreateBestWorkerPool()
{
    IWorkerPool::shared_ptr best_worker_pool;

    WorkerPoolType worker_pool_type;
    for(int i=0; i<3; i++)
    {
        switch (i)
        {
        case 0:
            worker_pool_type = WorkerPoolFactory::kMpiWorkerPool;
            break;
        case 1:
            worker_pool_type = WorkerPoolFactory::kThreadWorkerPool;
            break;
        case 2:
            worker_pool_type = WorkerPoolFactory::kSequentialWorkerPool;
            break;
        default:
            throw std::runtime_error("Bug in WorkerPoolFactory::CreateBestWorkerPool");
        }

        best_worker_pool = WorkerPoolFactory::CreateWorkerPool(worker_pool_type);
        if(best_worker_pool->IsValid())
        {
            return best_worker_pool;
        }
    }

    throw std::runtime_error("Can not create valid best_worker_pool.");
}

IWorkerPool::shared_ptr WorkerPoolFactory::CreateWorkerPool(WorkerPoolType worker_pool_type)
{
    switch (worker_pool_type)
    {
    case kThreadWorkerPool:
#ifdef BUILD_WITH_BOOST_THREAD
        return ThreadWorkerPool::shared_ptr (new ThreadWorkerPool());
#else
        throw std::runtime_error("k52::parallel was build with boost::thread support. Try define BUILD_WITH_BOOST_THREAD.");
#endif


    case kMpiWorkerPool:
#ifdef BUILD_WITH_MPI
        if(WorkerPoolFactory::was_mpi_worker_pool_created_)
        {
            throw std::runtime_error("MpiWorkerPool was already created. Only one creation of this type is allowed.");
        }
        else
        {
            was_mpi_worker_pool_created_ = true;
            return MpiWorkerPool::shared_ptr (new MpiWorkerPool());
        }
#else
        throw std::runtime_error("k52::parallel was not build with MPI support. Try define BUILD_WITH_MPI.");
#endif

    case kSequentialWorkerPool:
        return SequentialWorkerPool::shared_ptr (new SequentialWorkerPool());

    default:
        throw std::runtime_error("WorkerPoolType not supported.");
    }
}

bool WorkerPoolFactory::CanCreateWorkerPool(WorkerPoolType worker_pool_type)
{
    switch (worker_pool_type)
    {
    case kThreadWorkerPool:
#ifdef BUILD_WITH_BOOST_THREAD
        return true;
#else
        return false;
#endif

    case kMpiWorkerPool:
#ifdef BUILD_WITH_MPI
        return !WorkerPoolFactory::was_mpi_worker_pool_created_;
#else
        return false;
#endif

    case kSequentialWorkerPool:
        return true;

    default:
        return false;
    }
}

bool WorkerPoolFactory::was_mpi_worker_pool_created_ = false;

} /* namespace parallel */
} /* namespace k52 */
