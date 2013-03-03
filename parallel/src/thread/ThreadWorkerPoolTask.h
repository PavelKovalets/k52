/*
 * ThreadWorkerPoolTask.h
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#ifndef THREADWORKERPOOLTASK_H_
#define THREADWORKERPOOLTASK_H_

#include "../../include/IWorkerPool.h"

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
						boost::shared_ptr<ITaskResult>* resultToBeWritten);

				void doTask();

			private:
				const ITask* _taskToDo;
				boost::shared_ptr<ITaskResult>* _resultToBeWritten;
			};
		}
	}
}
#endif /* THREADWORKERPOOLTASK_H_ */
