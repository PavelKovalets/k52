#ifdef BUILD_WITH_MPI

#include "mpi_worker_pool.h"

#include <boost/mpi.hpp>
#include <boost/mpi/request.hpp>
#include <boost/serialization/vector.hpp>

#include <k52/parallel/mpi/constants.h>
#include <k52/parallel/mpi/identifyable_objects_manager.h>
#include "delay_supplier.h"

namespace k52
{
namespace parallel
{
namespace mpi
{

struct ResultExpectation
{
    int worker_rank;
    boost::mpi::request request;
};

MpiWorkerPool::MpiWorkerPool()
{
    was_finalized_ = false;
    environment_ = new boost::mpi::environment();
    communicator_ = new boost::mpi::communicator();

    std::cout<<"Rank "<<communicator_->rank()<<" of "<<
             communicator_->size()<<" starded on "<<
             environment_->processor_name()<<" processor."<<std::endl;

    if(communicator_->rank() != constants::kServerRank)
    {
        //Worker Logic
        RunWorkerLoop();
    }
}

MpiWorkerPool::~MpiWorkerPool()
{
    FinalizeWorkers();
    Clean();
}

std::vector< ITaskResult::shared_ptr > MpiWorkerPool::DoTasks (const std::vector<const ITask*>& tasks)
{
    CheckIfServer();
    CheckAwailableWorkers();

    int current_worker_rank = 1;
    bool was_first_part_sent = false;

    std::list<ResultExpectation> result_expectations;
    std::vector< ITaskResult::shared_ptr > results(tasks.size());

    for(size_t i = 0; i < tasks.size(); i++)
    {
        const IMpiTask* current_task = GetMpiTask(tasks[i]);
        ResultExpectation task_expectation = SendTask(current_task, current_worker_rank, &(results[i]));
        result_expectations.push_back( task_expectation );

        if(!was_first_part_sent)
        {
            current_worker_rank ++;
            if(current_worker_rank >= communicator_->size())
            {
                was_first_part_sent = true;
            }
        }

        if(was_first_part_sent)
        {
            ResultExpectation received_expectation = WaitAndPopNextExpectation(result_expectations);
            current_worker_rank = received_expectation.worker_rank;
        }
    }

    //receiving last tasks
    while(!result_expectations.empty())
    {
        WaitAndPopNextExpectation(result_expectations);
    }

    return results;
}

std::vector< WorkerStatistics > MpiWorkerPool::GetStatistics()
{
    return statistics_aggregator_.GetStatistics();
}

ResultExpectation MpiWorkerPool::SendTask(const IMpiTask* task,
                                          int current_worker_rank,
                                          ITaskResult::shared_ptr* result_to_set)
{
    communicator_->send(current_worker_rank, constants::kCommonTag, IdentifyableObjectsManager::GetId(*task));
    task->Send(communicator_, current_worker_rank);

    IMpiTaskResult::shared_ptr mpi_task_result = task->CreateEmptyResult();
    (*result_to_set) = mpi_task_result;

    ResultExpectation expectaton;
    expectaton.request = mpi_task_result->ReceiveAsync(communicator_, current_worker_rank);
    expectaton.worker_rank = current_worker_rank;

    return expectaton;
}

ResultExpectation MpiWorkerPool::WaitAndPopNextExpectation(std::list<ResultExpectation>& result_expectations)
{
    DelaySupplier delay_supplier;
    while(true)
    {        
        for(std::list<ResultExpectation>::iterator it = result_expectations.begin();
                        it!=result_expectations.end();
                        it++)
        {
            bool received = (*it).request.test();

            if(received)
            {
                ResultExpectation received_expectation = *it;
                result_expectations.erase(it);

                statistics_aggregator_.RegisterCount(received_expectation.worker_rank);

                return received_expectation;
            }
        }
        delay_supplier.SleepWithCurrentDelay();
        delay_supplier.IncreaseDelay();
    }
}

IMpiTask::shared_ptr MpiWorkerPool::CreateTask(std::string task_id)
{
    const IMpiTask* task = dynamic_cast<const IMpiTask*>(IdentifyableObjectsManager::Instance().GetObject(task_id));

    if(task == NULL)
    {
        std::stringstream message;
        message << "Object with id " << task_id << " was registered "
                        "but is not derived from ITask .";

        throw std::invalid_argument(message.str());
    }

    return IMpiTask::shared_ptr( task->Clone() );
}

const IMpiTask* MpiWorkerPool::GetMpiTask(const ITask* task)
{
    const IMpiTask* mpi_task = dynamic_cast<const IMpiTask*>( task );

    if(mpi_task == NULL)
    {
        throw std::logic_error("MpiWorkerPool can process only IMpiTask, not simple ITask.");
    }

    return mpi_task;
}

void MpiWorkerPool::RunWorkerLoop()
{
    int counted = 0;
    int errors = 0;

    while(true)
    {
        std::string task_id;

        communicator_->recv(constants::kServerRank, constants::kCommonTag, task_id);

        if(task_id == constants::kEndOfWorkTaskId)
        {
            Clean();
            exit(0);
        }

        counted++;

        IMpiTask::shared_ptr next_task = CreateTask(task_id);
        next_task->Receive(communicator_);
        IMpiTaskResult::shared_ptr result = next_task->PerformMpi();
        result->Send(communicator_);
    }
}

void MpiWorkerPool::CheckAwailableWorkers()
{
    if(communicator_->size() < 2)
    {
        throw std::runtime_error("No worker threads available. "
                        "Try to run program like following example: "
                        "\'mpirun -np x ./MyExeName\' where x > 1.");
    }
}

void MpiWorkerPool::FinalizeWorkers()
{
    CheckIfServer();

    for(int i=1; i<communicator_->size(); i++)
    {
        communicator_->send(i, constants::kCommonTag, std::string(constants::kEndOfWorkTaskId));
    }

    was_finalized_ = true;
}

void MpiWorkerPool::CheckIfServer()
{
    if(communicator_->rank() != constants::kServerRank)
    {
        std::stringstream message;
        message << "Critical error on " << communicator_->rank() << " node. "
                        "Requested action that requires server node status.";

        throw std::logic_error(message.str());
    }
}

void MpiWorkerPool::Clean()
{
    if(communicator_ != NULL)
    {
        delete communicator_;
        communicator_ = NULL;
    }

    if(environment_ != NULL)
    {
        delete environment_;
        environment_ = NULL;
    }
}

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif
