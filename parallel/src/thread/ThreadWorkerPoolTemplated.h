/*
 * ThreadWorkerPoolTemplated.h
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#ifndef THREADWORKERPOOLTEMPLATED_H_
#define THREADWORKERPOOLTEMPLATED_H_

#include "Worker.h"

namespace k52
{
namespace parallel
{
namespace thread
{

template <class Task>
class ThreadWorkerPoolTemplated
{
public:
	ThreadWorkerPoolTemplated();

	ThreadWorkerPoolTemplated(int numberOfWorkers);

	~ThreadWorkerPoolTemplated();

	void doTasks(std::queue<Task> tasks);

private:

	ThreadWorkerPoolTemplated(const ThreadWorkerPoolTemplated& a);
	ThreadWorkerPoolTemplated& operator = (const ThreadWorkerPoolTemplated& a);

	void initialize();

	int _numberOfWorkers;
	Worker<Task>* _workers;
	ThreadSafeQueue<Task> _tasksToDo;
	ThreadSafeQueue<Task> _doneTasks;
};

template <class Task>
void ThreadWorkerPoolTemplated<Task>::initialize()
{
	if(_numberOfWorkers <= 0)
	{
		throw std::invalid_argument("numberOfWorkers must be positive");
	}

	_workers = new Worker<Task> [_numberOfWorkers];

	//TODO do not start immediatelly?
	for(int i=0; i<_numberOfWorkers; i++)
	{
		_workers[i].start(&_tasksToDo, &_doneTasks);
	}
}

template <class Task>
ThreadWorkerPoolTemplated<Task>::ThreadWorkerPoolTemplated()
{
	_numberOfWorkers = boost::thread::hardware_concurrency();
	initialize();
}

template <class Task>
ThreadWorkerPoolTemplated<Task>::ThreadWorkerPoolTemplated(int numberOfWorkers)
{
	_numberOfWorkers = numberOfWorkers;
	initialize();
}

template <class Task>
ThreadWorkerPoolTemplated<Task>::~ThreadWorkerPoolTemplated()
{
	for(int i=0; i<_numberOfWorkers; i++)
	{
		_workers[i].stop();
	}

	//Wait for correct finalization of all threads
	for(int i=0; i<_numberOfWorkers; i++)
	{
		_workers[i].join();
	}

	delete [] _workers;
}

template <class Task>
void ThreadWorkerPoolTemplated<Task>::doTasks(std::queue<Task> tasks)
{
	int n = tasks.size();

	while(!tasks.empty())
	{
		_tasksToDo.push(tasks.front());
		tasks.pop();
	}

	for(int i=0; i<n; i++)
	{
		Task doneTask;
		_doneTasks.waitAndPop(doneTask);
	}
}

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif /* THREADWORKERPOOLTEMPLATED_H_ */
