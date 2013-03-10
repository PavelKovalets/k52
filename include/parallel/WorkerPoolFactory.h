/*
 * WorkerPoolFactory.h
 *
 *  Created on: Mar 9, 2013
 *      Author: feanor
 */

#ifndef WORKERPOOLFACTORY_H_
#define WORKERPOOLFACTORY_H_

#include <parallel/IWorkerPool.h>

namespace k52
{
namespace parallel
{

enum WorkerPoolType
{
	kThreadWorkerPool,
	kMpiWorkerPool
};

class WorkerPoolFactory
{
public:
	static IWorkerPool::shared_ptr createWorkerPool(WorkerPoolType workerPoolType);

	static bool canCreateWorkerPool(WorkerPoolType workerPoolType);

private:
	static bool _wasMpiWorkerPoolCreated;
};

} /* namespace parallel */
} /* namespace k52 */
#endif /* WORKERPOOLFACTORY_H_ */
