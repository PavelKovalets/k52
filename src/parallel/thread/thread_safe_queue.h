/*
 * ThreadSafeQueue.h
 * This design is subject to race conditions between calls to empty,
 * front and pop if there is more than one thread removing items from the queue,
 * but in a single-consumer system (as being discussed here), this is not a problem.
 * http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
 */

#ifndef THREADSAFEQUEUE_H_
#define THREADSAFEQUEUE_H_

#ifdef BUILD_WITH_BOOST_THREAD

#include <queue>
#include <boost/thread.hpp>

#include <k52/common/disallow_copy_and_assign.h>

namespace k52
{
namespace parallel
{
namespace thread
{

template<class TElement>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue() {}
    void Push(const TElement& element);
    void WaitAndPop(TElement& popped_value);
    bool TryPop(TElement& popped_value);
    bool IsEmpty() const;

private:
    std::queue<TElement> queue_;
    boost::mutex mutex_;
    boost::condition_variable condition_variable_;

    DISALLOW_COPY_AND_ASSIGN(ThreadSafeQueue);
};

template<class TElement>
void ThreadSafeQueue<TElement>::Push(const TElement& element)
{
    boost::mutex::scoped_lock lock(mutex_);
    //bool const wasEmpty=_queue.empty();
    queue_.push(element);

    //the waiting thread might wake up immediately it is notified,
    //and before the mutex is unlocked, in which case it will have
    //to block when the mutex is reacquired on the exit from wait.
    //By rewriting the function so that the notification comes
    //after the mutex is unlocked, the waiting thread will be
    //able to acquire the mutex without blocking
    lock.unlock(); // unlock the mutex

    //If we notify with every push() then only the right number of threads are awoken.
    //if(wasEmpty)
    {
        condition_variable_.notify_one();
    }
}

//Using a reference parameter to receive the result is used to
//transfer ownership out of the queue in order to avoid the
//exception safety issues of returning data by-value:
//if the copy constructor of a by-value return throws,
//then the data has been removed from the queue, but is lost4

template<class TElement>
void ThreadSafeQueue<TElement>::WaitAndPop(TElement& popped_value)
{
    boost::mutex::scoped_lock lock(mutex_);
    while(queue_.empty())
    {
        condition_variable_.wait(lock);
    }

    popped_value=queue_.front();
    queue_.pop();
}

template<class TElement>
bool ThreadSafeQueue<TElement>::TryPop(TElement& popped_value)
{
    boost::mutex::scoped_lock lock(mutex_);
    if(queue_.empty())
    {
        return false;
    }

    popped_value=queue_.front();
    queue_.pop();
    return true;
}

template<class TElement>
bool ThreadSafeQueue<TElement>::IsEmpty() const
{
    boost::mutex::scoped_lock lock(mutex_);
    return queue_.empty();
}

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif

#endif /* THREADSAFEQUEUE_H_ */
