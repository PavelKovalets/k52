#include "optimization_parameters_processor.h"

#include <stdexcept>
#include <k52/parallel/worker_pool_factory.h>

#ifdef BUILD_WITH_MPI
#include <k52/parallel/mpi/identifyable_objects_manager.h>
#endif

#include "optimization_task.h"
#include "optimization_task_result.h"

namespace k52
{
namespace optimization
{
OptimizationParametersProcessor::OptimizationParametersProcessor(const IOptimizer* optimizer)
{
#ifdef BUILD_WITH_MPI
    OptimizationTask task;
    k52::parallel::mpi::IdentifyableObjectsManager::Instance().RegisterObject(task);
#endif
    optimizer_ = optimizer;
    worker_pool_ = parallel::WorkerPoolFactory::CreateBestWorkerPool();
}

IParameters::shared_ptr OptimizationParametersProcessor::ProcessParameters(
    const IObjectiveFunction& function_to_optimize,
    const std::vector< IParameters::shared_ptr >& parameters,
    bool maximize)
{
    std::vector< OptimizationTask::shared_ptr > tasks (parameters.size());
    std::vector< const parallel::ITask* > task_pointers (parameters.size());
    for(size_t i=0; i<parameters.size(); i++)
    {
        tasks[i] = OptimizationTask::shared_ptr(
            new OptimizationTask(optimizer_,
                                 parameters[i].get(),
                                 &function_to_optimize,
                                 maximize)
        );
        task_pointers[i] = tasks[i].get();
    }

    std::vector< parallel::ITaskResult::shared_ptr > task_results
        = worker_pool_->DoTasks(task_pointers);

    //TODO FIX COPYPASTE AND REFACTOR ARCHITECTURE TO COUNT PARALLEL
    std::vector<double> values(parameters.size());
    for(size_t i=0; i<parameters.size(); i++)
    {
        values[i] = function_to_optimize(
            boost::dynamic_pointer_cast<OptimizationTaskResult>(task_results[i])
                ->get_optimal_parameters().get()
        );
    }

    size_t index = 0;
    double value = values[index];

    for(size_t i=1; i<values.size(); i++)
    {
        bool condition = values[i] > value;
        condition = maximize ? condition : (!condition);

        if(condition)
        {
            index = i;
            value = values[i];
        }
    }

    //TODO FIX
    return boost::dynamic_pointer_cast<IParameters>(
        boost::dynamic_pointer_cast<OptimizationTaskResult>(
            task_results[index]
        )->get_optimal_parameters()
    );
}

}/* namespace optimization */
}/* namespace k52 */
