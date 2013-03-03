/*
 * ThreadWorkerPool.cpp
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#include "../../include/thread/ThreadWorkerPool.h"

namespace k52
{
	namespace parallel
	{
		namespace thread
		{
			ThreadWorkerPool::ThreadWorkerPool(int numberOfWorkers):
					_workerPool(numberOfWorkers) {}

			std::vector< boost::shared_ptr<ITaskResult> > ThreadWorkerPool::doTasks (
					const std::vector<const ITask*>& tasks
					)
			{
				std::vector< boost::shared_ptr<ITaskResult> > results(tasks.size());
				std::queue<ThreadWorkerPoolTask> tasksQueue;

				for(size_t i=0; i<tasks.size(); i++)
				{
					tasksQueue.push( ThreadWorkerPoolTask(tasks[i], &(results[i])) );
				}

				_workerPool.doTasks(tasksQueue);

				return results;
			}
		}
	}
}
