#ifndef THREADWORKERPOOLTEMPLATED_H_
#define THREADWORKERPOOLTEMPLATED_H_

#ifdef BUILD_WITH_BOOST_THREAD

#include <k52/common/disallow_copy_and_assign.h>
#include "worker.h"

namespace k52
{
namespace parallel
{
namespace thread
{

template <class TTask>
class ThreadWorkerPoolTemplated
{
public:
    ThreadWorkerPoolTemplated();
    explicit ThreadWorkerPoolTemplated(int number_of_workers);
    ~ThreadWorkerPoolTemplated();
    void DoTasks(std::queue<TTask> tasks);

private:
    void Initialize();

    int number_of_workers_;
    Worker<TTask>* workers_;
    ThreadSafeQueue<TTask> tasks_to_do_;
    ThreadSafeQueue<TTask> done_tasks_;

    DISALLOW_COPY_AND_ASSIGN(ThreadWorkerPoolTemplated);
};

template <class TTask>
ThreadWorkerPoolTemplated<TTask>::ThreadWorkerPoolTemplated()
{
    number_of_workers_ = boost::thread::hardware_concurrency();
    Initialize();
}

template <class TTask>
ThreadWorkerPoolTemplated<TTask>::ThreadWorkerPoolTemplated(int number_of_workers)
{
    number_of_workers_ = number_of_workers;
    Initialize();
}

template <class TTask>
ThreadWorkerPoolTemplated<TTask>::~ThreadWorkerPoolTemplated()
{
    for(int i=0; i<number_of_workers_; i++)
    {
        workers_[i].Stop();
    }

    //Wait for correct finalization of all threads
    for(int i=0; i<number_of_workers_; i++)
    {
        workers_[i].Join();
    }

    delete [] workers_;
}

template <class TTask>
void ThreadWorkerPoolTemplated<TTask>::DoTasks(std::queue<TTask> tasks)
{
    int n = tasks.size();

    while(!tasks.empty())
    {
        tasks_to_do_.Push(tasks.front());
        tasks.pop();
    }

    for(int i=0; i<n; i++)
    {
        TTask done_task;
        done_tasks_.WaitAndPop(done_task);
    }
}

template <class TTask>
void ThreadWorkerPoolTemplated<TTask>::Initialize()
{
    if(number_of_workers_ <= 0)
    {
        throw std::invalid_argument("number_of_workers must be positive");
    }

    workers_ = new Worker<TTask> [number_of_workers_];

    for(int i=0; i<number_of_workers_; i++)
    {
        workers_[i].Start(&tasks_to_do_, &done_tasks_);
    }
}

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif

#endif /* THREADWORKERPOOLTEMPLATED_H_ */
