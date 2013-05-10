#ifndef OPTIMIZATION_PARAMETERS_PROCESSOR_H
#define OPTIMIZATION_PARAMETERS_PROCESSOR_H

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/parallel/i_worker_pool.h>
#include <k52/optimization/i_optimizer.h>

#include "i_parameters_processor.h"

namespace k52
{
namespace optimization
{

class OptimizationParametersProcessor : public IParametersProcessor
{
public:
    typedef boost::shared_ptr<OptimizationParametersProcessor> shared_ptr;

    OptimizationParametersProcessor(const IOptimizer* optimizer);

    virtual IContinuousParameters::shared_ptr ProcessParameters(const IObjectiveFunction& function_to_optimize,
                                    const std::vector< IContinuousParameters::shared_ptr >& parameters,
                                    bool maximize);

private:
    parallel::IWorkerPool::shared_ptr worker_pool_;
    const IOptimizer* optimizer_;

    DISALLOW_COPY_AND_ASSIGN(OptimizationParametersProcessor);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* OPTIMIZATION_PARAMETERS_PROCESSOR_H */
