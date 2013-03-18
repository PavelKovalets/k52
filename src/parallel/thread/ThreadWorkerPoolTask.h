/*
 * ThreadWorkerPoolTask.h
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#ifndef THREADWORKERPOOLTASK_H_
#define THREADWORKERPOOLTASK_H_

#include <parallel/i_worker_pool.h>

namespace k52
{
namespace parallel
{
namespace thread
{

class ThreadWorkerPoolTask
{
public:
	ThreadWorkerPoolTask();

	ThreadWorkerPoolTask(
			const ITask* taskToDo,
			ITaskResult::shared_ptr* resultToBeWritten);

	void doTask();

private:
	const ITask* _taskToDo;
	ITaskResult::shared_ptr* _resultToBeWritten;
};

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif /* THREADWORKERPOOLTASK_H_ */
