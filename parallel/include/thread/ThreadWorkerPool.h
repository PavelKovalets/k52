/*
 * ThreadWorkerPool.h
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#ifndef THREADWORKERPOOL_H_
#define THREADWORKERPOOL_H_

#include "../IWorkerPool.h"
#include "../../src/thread/ThreadWorkerPoolTask.h"
#include "../../src/thread/ThreadWorkerPoolTemplated.h"

namespace k52
{
	namespace parallel
	{
		namespace thread
		{
			class ThreadWorkerPool : public IWorkerPool
			{
			public:
				ThreadWorkerPool(int numberOfWorkers);

				virtual std::vector< boost::shared_ptr<ITaskResult> > doTasks (
						const std::vector<const ITask*>& tasks
						);

			private:
				ThreadWorkerPoolTemplated<ThreadWorkerPoolTask> _workerPool;

				ThreadWorkerPool(const ThreadWorkerPool& a);
				ThreadWorkerPool& operator = (const ThreadWorkerPool& a);
			};
		}
	}
}
#endif /* THREADWORKERPOOL_H_ */
