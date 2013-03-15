/*
 * ThreadWorkerPool.h
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#ifndef THREADWORKERPOOL_H_
#define THREADWORKERPOOL_H_

#ifdef BUILD_WITH_BOOST_THREAD

#include <parallel/IWorkerPool.h>
#include "ThreadWorkerPoolTask.h"
#include "ThreadWorkerPoolTemplated.h"

#include <common/disallow_copy_and_assign.h>

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

	ThreadWorkerPool();

	virtual std::vector< ITaskResult::shared_ptr > doTasks (
			const std::vector<const ITask*>& tasks
			);

	virtual std::vector< WorkerStatistics > getStatistics();

private:
	ThreadWorkerPoolTemplated<ThreadWorkerPoolTask> _workerPool;

	DISALLOW_COPY_AND_ASSIGN(ThreadWorkerPool);
};



} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif

#endif /* THREADWORKERPOOL_H_ */
