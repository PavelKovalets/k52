/*
 * ThreadSafeQueue.h
 *
 *  Created on: Mar 12, 2012
 *      Author: feanor
 *      This design is subject to race conditions between calls to empty,
 *      front and pop if there is more than one thread removing items from the queue,
 *      but in a single-consumer system (as being discussed here), this is not a problem.
 * http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
 */

#ifndef THREADSAFEQUEUE_H_
#define THREADSAFEQUEUE_H_

#include <queue>
#include <boost/thread.hpp>

namespace k52
{
namespace parallel
{
namespace thread
{

template<class Element>
class ThreadSafeQueue
{
public:
	void push(const Element& element);
	bool tryPop(Element& poppedValue);
	void waitAndPop(Element& poppedValue);
	bool isEmpty() const;

private:
	std::queue<Element> _queue;
	boost::mutex _mutex;
	boost::condition_variable _conditionVariable;
};



//Using a reference parameter to receive the result is used to
//transfer ownership out of the queue in order to avoid the
//exception safety issues of returning data by-value:
//if the copy constructor of a by-value return throws,
//then the data has been removed from the queue, but is lost4

template<class Element>
void ThreadSafeQueue<Element>::waitAndPop(Element& poppedValue)
{
	boost::mutex::scoped_lock lock(_mutex);
	while(_queue.empty())
	{
		_conditionVariable.wait(lock);
	}

	poppedValue=_queue.front();
	_queue.pop();
}

template<class Element>
void ThreadSafeQueue<Element>::push(const Element& element)
{
	boost::mutex::scoped_lock lock(_mutex);
	//bool const wasEmpty=_queue.empty();
	_queue.push(element);

	//the waiting thread might wake up immediately it is notified,
	//and before the mutex is unlocked, in which case it will have
	//to block when the mutex is reacquired on the exit from wait.
	//By rewriting the function so that the notification comes
	//after the mutex is unlocked, the waiting thread will be
	//able to acquire the mutex without blocking
	lock.unlock(); // unlock the mutex

	//If we notify with every push() then only the right number of threads are woken.
	//if(wasEmpty)
	{
		_conditionVariable.notify_one();
	}
}

template<class Element>
bool ThreadSafeQueue<Element>::tryPop(Element& poppedValue)
{
	boost::mutex::scoped_lock lock(_mutex);
	if(_queue.empty())
	{
		return false;
	}

	poppedValue=_queue.front();
	_queue.pop();
	return true;
}

template<class Element>
bool ThreadSafeQueue<Element>::isEmpty() const
{
	boost::mutex::scoped_lock lock(_mutex);
	return _queue.empty();
}

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif /* THREADSAFEQUEUE_H_ */
