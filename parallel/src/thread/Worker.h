/*
 * Worker.h
 *
 *  Created on: Mar 15, 2012
 *      Author: feanor
 */

#ifndef WORKER_H_
#define WORKER_H_

#include "ThreadSafeQueue.h"
#include <iostream>

namespace k52
{
namespace parallel
{
namespace thread
{

template <class Task>
class Worker
{
public:
	Worker();

	void start(ThreadSafeQueue<Task>* tasksToDo, ThreadSafeQueue<Task>* doneTasks);

	void stop();

	void join();

protected:

	void processTasksQueue(ThreadSafeQueue<Task>* tasksToDo, ThreadSafeQueue<Task>* doneTasks);

private:

	boost::thread _thread;
};


template <class Task>
Worker<Task>::Worker()
{
}

template <class Task>
void Worker<Task>::start(ThreadSafeQueue<Task>* tasksToDo, ThreadSafeQueue<Task>* doneTasks)
{
	_thread = boost::thread(&Worker::processTasksQueue, this, tasksToDo, doneTasks);
}

template <class Task>
void Worker<Task>::stop()
{
	_thread.interrupt();
}

template <class Task>
void Worker<Task>::join()
{
	_thread.join();
}

template <class Task>
void Worker<Task>::processTasksQueue(ThreadSafeQueue<Task>* tasksToDo, ThreadSafeQueue<Task>* doneTasks)
{
	while(true)
	{
		try
		{
			//boost::this_thread::disable_interruption di;
			Task toDo;
			tasksToDo->waitAndPop(toDo);
			toDo.doTask();
			doneTasks->push(toDo);
		}
		catch(boost::thread_interrupted& ex)
		{
			std::cout << "Incorrect finish" << std::endl;
			break;
		}
		catch(const std::exception& ex)
		{
			std::cout << "Incorrect task: " << ex.what()<<std::endl;
		}

		try
		{
			boost::this_thread::interruption_point();
		}
		catch(boost::thread_interrupted& ex)
		{
			std::cout<<"Correct finish."<<std::endl;
			break;
		}
	}
}

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif /* WORKER_H_ */
