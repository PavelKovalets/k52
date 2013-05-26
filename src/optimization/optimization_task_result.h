#ifndef OPTIMIZATION_TASK_RESULT_H
#define OPTIMIZATION_TASK_RESULT_H

#include <k52/parallel/i_task_result.h>
#include <k52/optimization/params/i_parameters.h>

#ifdef BUILD_WITH_MPI
#include <k52/parallel/mpi/i_mpi_task_result.h>
#endif

namespace k52
{
namespace optimization
{

class OptimizationTaskResult :

#ifdef BUILD_WITH_MPI
    public k52::parallel::mpi::IMpiTaskResult
#else
    public k52::parallel::ITaskResult
#endif

{
public:
    typedef boost::shared_ptr<OptimizationTaskResult> shared_ptr;

    OptimizationTaskResult(const IParameters* optimal_parameters);

    IParameters::shared_ptr get_optimal_parameters() const;

#ifdef BUILD_WITH_MPI

    virtual k52::parallel::mpi::AsyncCallChain::shared_ptr ReceiveAsync(boost::mpi::communicator* communicator, int source);

    virtual void Send(boost::mpi::communicator* communicator);

#endif

private:

#ifdef BUILD_WITH_MPI

    boost::mpi::request ReceiveParametersIdAsyncCall();
    boost::optional<boost::mpi::request> ReceiveParametersAsyncCall();

    boost::mpi::communicator* communicator_;
    int source_;
    std::string parameters_id_;

#endif

    IParameters::shared_ptr optimal_parameters_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* OPTIMIZATION_TASK_RESULT_H */
