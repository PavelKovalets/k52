/*
 * WorkerPoolFactory.cpp
 *
 *  Created on: Mar 9, 2013
 *      Author: feanor
 */

#include <parallel/WorkerPoolFactory.h>

#ifdef BUILD_WITH_BOOST_THREAD
#include "thread/ThreadWorkerPool.h"
using ::k52::parallel::thread::ThreadWorkerPool;
#endif

#ifdef BUILD_WITH_MPI
#include "mpi/MpiWorkerPool.h"
using ::k52::parallel::mpi::MpiWorkerPool;
#endif

namespace k52
{
namespace parallel
{

bool WorkerPoolFactory::_wasMpiWorkerPoolCreated = false;

IWorkerPool::shared_ptr WorkerPoolFactory::createWorkerPool(WorkerPoolType workerPoolType)
{
	switch (workerPoolType)
	{
	case kThreadWorkerPool:
#ifdef BUILD_WITH_BOOST_THREAD
		return ThreadWorkerPool::shared_ptr (new ThreadWorkerPool());		
#else
		throw std::runtime_error("k52::parallel was build with boost::thread support. Try define BUILD_WITH_BOOST_THREAD.");
#endif


	case kMpiWorkerPool:
#ifdef BUILD_WITH_MPI
		if(WorkerPoolFactory::_wasMpiWorkerPoolCreated)
		{
			throw std::runtime_error("MpiWorkerPool was already created. Only one creation of this type is allowed.");
		}
		else
		{
			_wasMpiWorkerPoolCreated = true;
			return MpiWorkerPool::shared_ptr (new MpiWorkerPool());
		}

#else
		throw std::runtime_error("k52::parallel was not build with MPI support. Try define BUILD_WITH_MPI.");
#endif

	default:
		throw std::runtime_error("WorkerPoolType not supported.");
	}
}

bool WorkerPoolFactory::canCreateWorkerPool(WorkerPoolType workerPoolType)
{
	switch (workerPoolType)
	{
	case kThreadWorkerPool:
		return true;

	case kMpiWorkerPool:
#ifdef BUILD_WITH_MPI
		return !WorkerPoolFactory::_wasMpiWorkerPoolCreated;
#else
		return false;
#endif

	default:
		return false;
	}
}

} /* namespace parallel */
} /* namespace k52 */
