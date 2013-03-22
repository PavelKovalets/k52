#ifndef COUNTOBJECTIVEFUNCTIONTASK_H_
#define COUNTOBJECTIVEFUNCTIONTASK_H_

#include <string>
#include <boost/shared_ptr.hpp>

#include <common/disallow_copy_and_assign.h>
#include <optimize/i_objective_function.h>
#include <parallel/i_task.h>

#ifdef BUILD_WITH_MPI

#include <parallel/mpi/i_mpi_task.h>
#include <parallel/mpi/i_mpi_task_result.h>

#endif

namespace k52
{
namespace optimize
{

class CountObjectiveFunctionTask

#ifdef BUILD_WITH_MPI
    : public k52::parallel::mpi::IMpiTask
#else
    : public k52::parallel::ITask
#endif

{
public:
    typedef boost::shared_ptr<CountObjectiveFunctionTask> shared_ptr;

    CountObjectiveFunctionTask();

    CountObjectiveFunctionTask(
        const IParameters* parameters,
        const IObjectiveFunction* function_to_optimize);

#ifdef BUILD_WITH_MPI

    virtual k52::parallel::mpi::IMpiTaskResult::shared_ptr PerformMpi() const;

    virtual k52::parallel::mpi::IMpiTaskResult::shared_ptr CreateEmptyResult() const;

    virtual CountObjectiveFunctionTask* Clone() const;

    virtual void Send(boost::mpi::communicator* communicator, int target) const;

    virtual void Receive(boost::mpi::communicator* communicator);

#else

    k52::parallel::ITaskResult::shared_ptr Perform() const;

#endif

protected:
    const IObjectiveFunction* get_objective_function() const;
    const IParameters* get_parameters() const;

private:
    //TODO are functors thread-safe not to copy locally them?
    const IObjectiveFunction* const function_to_optimize_;
    const IParameters* const  parameters_;

    //Indicates if task was created at once - so const pointers to be used
    //Otherwise it is received - so shared_ptr's should be used
    bool was_created_;

    IParameters::shared_ptr received_parameters_;
    IObjectiveFunction::shared_ptr received_function_;

    DISALLOW_COPY_AND_ASSIGN(CountObjectiveFunctionTask);
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* COUNTOBJECTIVEFUNCTIONTASK_H_ */
