#ifndef OBJECTIVEFUNCTIONTASKRESULT_H_
#define OBJECTIVEFUNCTIONTASKRESULT_H_

#include <k52/parallel/i_task_result.h>

#ifdef BUILD_WITH_MPI
#include <k52/parallel/mpi/i_mpi_task_result.h>
#endif

namespace k52
{
namespace optimize
{

class ObjectiveFunctionTaskResult: 

#ifdef BUILD_WITH_MPI
    public k52::parallel::mpi::IMpiTaskResult
#else
    public k52::parallel::ITaskResult
#endif

{
public:
    typedef boost::shared_ptr<ObjectiveFunctionTaskResult> shared_ptr;

    virtual ~ObjectiveFunctionTaskResult() {}

    double get_objective_function_value() const;

    void set_objective_function_value(double objective_function_value);

#ifdef BUILD_WITH_MPI

    virtual boost::mpi::request ReceiveAsync(boost::mpi::communicator* communicator, int source);

    virtual void Send(boost::mpi::communicator* communicator);

#endif

private:
    double objective_function_value_;
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* OBJECTIVEFUNCTIONTASKRESULT_H_ */
