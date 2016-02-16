#ifndef MPIWORKERPOOL_H_
#define MPIWORKERPOOL_H_

#include <vector>
#include <list>
#include <boost/shared_ptr.hpp>

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/parallel/mpi/boost_mpi_declaration.h>
#include <k52/parallel/mpi/i_mpi_task.h>
#include <k52/parallel/i_worker_pool.h>

#include "../statistics_aggregator.h"

namespace k52
{
namespace parallel
{
namespace mpi
{

struct ResultExpectation;

class MpiWorkerPool : public IWorkerPool
{
public:
    typedef boost::shared_ptr<MpiWorkerPool> shared_ptr;

    MpiWorkerPool();
    ~MpiWorkerPool();
    virtual bool IsValid();
    virtual std::vector< ITaskResult::shared_ptr > DoTasks (const std::vector<const ITask*>& tasks);
    virtual std::vector< WorkerStatistics > GetStatistics();

private:
    ResultExpectation SendTask(const IMpiTask* task,
                               int current_worker_rank,
                               ITaskResult::shared_ptr* result_to_set);
    ResultExpectation WaitAndPopNextExpectation(std::list<ResultExpectation>& result_expectations);
    IMpiTask::shared_ptr CreateTask(std::string task_id);
    const IMpiTask* GetMpiTask(const ITask* task);
    void RunWorkerLoop();
    bool AreAvailableWorkers() const;
    void CheckAvailableWorkers() const;
    void FinalizeWorkers();
    void CheckIfServer();
    void Clean();

    boost::mpi::environment* environment_;
    boost::mpi::communicator* communicator_;
    StatisticsAggregator statistics_aggregator_;
    bool was_finalized_;

    DISALLOW_COPY_AND_ASSIGN(MpiWorkerPool);
};

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */

#endif /* MPIWORKERPOOL_H_ */
