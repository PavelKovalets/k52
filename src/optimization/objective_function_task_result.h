#ifndef OBJECTIVEFUNCTIONTASKRESULT_H_
#define OBJECTIVEFUNCTIONTASKRESULT_H_

#include <k52/parallel/i_task_result.h>

#ifdef BUILD_WITH_MPI
#include <k52/parallel/mpi/i_mpi_task_result.h>
#endif

namespace k52
{
namespace optimization
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

    virtual k52::parallel::mpi::AsyncCallChain::shared_ptr ReceiveAsync(boost::mpi::communicator* communicator, int source);

    virtual void Send(boost::mpi::communicator* communicator);

#endif

private:

#ifdef BUILD_WITH_MPI

    boost::mpi::request ReceiveAsyncCall();
    boost::mpi::communicator* communicator_;
    int source_;

#endif

    double objective_function_value_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* OBJECTIVEFUNCTIONTASKRESULT_H_ */
