/*
 * ThreadWorkerPoolTask.cpp
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#include "ThreadWorkerPoolTask.h"

namespace k52
{
namespace parallel
{
namespace thread
{

ThreadWorkerPoolTask::ThreadWorkerPoolTask():
				_taskToDo(NULL), _resultToBeWritten(NULL) {}

ThreadWorkerPoolTask::ThreadWorkerPoolTask(
		const ITask* taskToDo,
		ITaskResult::shared_ptr* resultToBeWritten):
				_taskToDo(taskToDo), _resultToBeWritten(resultToBeWritten)	{}

void ThreadWorkerPoolTask::doTask()
{
	(*_resultToBeWritten) = _taskToDo->perform();
}

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */
