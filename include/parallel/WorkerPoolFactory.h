/*
 * WorkerPoolFactory.h
 *
 *  Created on: Mar 9, 2013
 *      Author: feanor
 */

#ifndef WORKERPOOLFACTORY_H_
#define WORKERPOOLFACTORY_H_

#include <common/disallow_copy_and_assign.h>
#include <parallel/i_worker_pool.h>

namespace k52
{
namespace parallel
{

enum WorkerPoolType
{
	kThreadWorkerPool = 0,
	kMpiWorkerPool,
	kSequentialWorkerPool
};

class WorkerPoolFactory
{
public:
	static IWorkerPool::shared_ptr createWorkerPool(WorkerPoolType workerPoolType);

	static bool canCreateWorkerPool(WorkerPoolType workerPoolType);

private:
	static bool _wasMpiWorkerPoolCreated;

	DISALLOW_COPY_AND_ASSIGN(WorkerPoolFactory);
};

} /* namespace parallel */
} /* namespace k52 */
#endif /* WORKERPOOLFACTORY_H_ */
