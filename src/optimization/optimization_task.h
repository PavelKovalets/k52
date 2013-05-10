#ifndef OPTIMIZATION_TASK_H
#define OPTIMIZATION_TASK_H

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/optimization/params/i_parameters.h>
#include <k52/optimization/i_objective_function.h>

#ifdef BUILD_WITH_MPI

#include <k52/parallel/mpi/i_mpi_task.h>
#include <k52/parallel/mpi/i_mpi_task_result.h>

#endif

namespace k52
{
namespace optimization
{

class OptimizationTask :

#ifdef BUILD_WITH_MPI
    public k52::parallel::mpi::IMpiTask
#else
    public k52::parallel::ITask
#endif

{
public:
    typedef boost::shared_ptr<OptimizationTask> shared_ptr;

    //TODO remove as needed only for registering
    OptimizationTask() {}

    OptimizationTask(const IParameters* initial_parameters,
                     const IObjectiveFunction* function_to_optimize);

#ifdef BUILD_WITH_MPI

    virtual k52::parallel::mpi::IMpiTaskResult::shared_ptr CreateEmptyResult() const;

    virtual OptimizationTask* Clone() const;

    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator);

    virtual k52::parallel::mpi::IMpiTaskResult* Perform() const;

#else

    virtual k52::parallel::ITaskResult* Perform() const;

#endif

private:
    IParameters::shared_ptr initial_parameters_;
    IObjectiveFunction::shared_ptr function_to_optimize_;
    bool maximize_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* OPTIMIZATION_TASK_H */
