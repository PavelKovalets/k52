#ifndef WORKER_H_
#define WORKER_H_

#ifdef BUILD_WITH_BOOST_THREAD

#include <iostream>
#include <k52/common/disallow_copy_and_assign.h>
#include "thread_safe_queue.h"

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
    void Start(ThreadSafeQueue<TTask>* tasks_to_do, ThreadSafeQueue<TTask>* done_tasks);
    void Stop();
    void Join();

protected:
    void ProcessTasksQueue(ThreadSafeQueue<TTask>* tasks_to_do, ThreadSafeQueue<TTask>* done_tasks);

private:
    boost::thread thread_;

    DISALLOW_COPY_AND_ASSIGN(Worker);
};

template <class TTask>
void Worker<TTask>::Start(ThreadSafeQueue<TTask>* tasks_to_do, ThreadSafeQueue<TTask>* done_tasks)
{
    thread_ = boost::thread(&Worker::ProcessTasksQueue, this, tasks_to_do, done_tasks);
}

template <class TTask>
void Worker<TTask>::Stop()
{
    thread_.interrupt();
}

template <class TTask>
void Worker<TTask>::Join()
{
    thread_.join();
}

template <class TTask>
void Worker<TTask>::ProcessTasksQueue(ThreadSafeQueue<TTask>* tasks_to_do, ThreadSafeQueue<TTask>* done_tasks)
{
    while(true)
    {
        try
        {
            //boost::this_thread::disable_interruption di;
            TTask to_do;
            tasks_to_do->WaitAndPop(to_do);
            to_do.DoTask();
            done_tasks->Push(to_do);
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
