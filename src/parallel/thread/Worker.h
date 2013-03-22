#ifndef WORKER_H_
#define WORKER_H_

#ifdef BUILD_WITH_BOOST_THREAD

#include "thread_safe_queue.h"
#include <iostream>

#include <common/disallow_copy_and_assign.h>

namespace k52
{
namespace parallel
{
namespace thread
{

template <class TTask>
class Worker
{
public:
	Worker() {}

	void start(ThreadSafeQueue<TTask>* tasksToDo, ThreadSafeQueue<TTask>* doneTasks);

	void stop();

	void join();

protected:
	void processTasksQueue(ThreadSafeQueue<TTask>* tasksToDo, ThreadSafeQueue<TTask>* doneTasks);

private:
	boost::thread _thread;

	DISALLOW_COPY_AND_ASSIGN(Worker);
};


template <class TTask>
void Worker<TTask>::start(ThreadSafeQueue<TTask>* tasksToDo, ThreadSafeQueue<TTask>* doneTasks)
{
	_thread = boost::thread(&Worker::processTasksQueue, this, tasksToDo, doneTasks);
}

template <class TTask>
void Worker<TTask>::stop()
{
	_thread.interrupt();
}

template <class TTask>
void Worker<TTask>::join()
{
	_thread.join();
}

template <class TTask>
void Worker<TTask>::processTasksQueue(ThreadSafeQueue<TTask>* tasksToDo, ThreadSafeQueue<TTask>* doneTasks)
{
	while(true)
	{
		try
		{
			//boost::this_thread::disable_interruption di;
		    TTask to_do;
			tasksToDo->WaitAndPop(to_do);
			to_do.DoTask();
			doneTasks->Push(to_do);
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

#endif

#endif /* WORKER_H_ */
