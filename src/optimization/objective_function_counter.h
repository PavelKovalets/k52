#ifndef OBJECTIVEFUNCTIONCOUNTER_H_
#define OBJECTIVEFUNCTIONCOUNTER_H_

#include <map>
#include <vector>
#include <queue>

#include <boost/functional/hash.hpp>

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/parallel/i_worker_pool.h>
#include <k52/optimization/i_objective_function.h>
#include <k52/optimization/individual.h>

#include "cache.h"
#include "count_objective_function_task.h"
#include "objective_function_task_result.h"

namespace k52
{
namespace optimization
{

class ObjectiveFunctionCounter
{
public:
    typedef boost::shared_ptr<ObjectiveFunctionCounter> shared_ptr;

    explicit ObjectiveFunctionCounter(bool use_value_caching, double cache_data_limit_in_megabytes);

    void ObtainFitness(
        const IObjectiveFunction& objective_function,
        std::vector<Individual::shared_ptr>* population);

    std::vector<double> CountObjectiveFunctionValues(
        const std::vector<const IParameters*>& parameters_to_count,
        const IObjectiveFunction& objective_function);

    void ResetCacheHits();
    int get_cache_hits() const;
    int get_objective_function_counts() const;

protected:
    void ProcessPopulation(
        std::vector<Individual::shared_ptr>* population,
        std::vector<const IParameters*>* parameters_to_count,
        std::vector<int>* indexes_to_count);

    std::vector< ObjectiveFunctionTaskResult::shared_ptr > Count(
        const std::vector<CountObjectiveFunctionTask::shared_ptr>& raw_tasks);

    std::vector< CountObjectiveFunctionTask::shared_ptr > CreateRawTasks(
        const std::vector<const IParameters*>& parameters_to_count,
        const IObjectiveFunction& objective_function);

    std::vector< const k52::parallel::ITask* > CreateRawTaskPointersVector(
        const std::vector<CountObjectiveFunctionTask::shared_ptr>& raw_tasks);

    void AddNewCacheValues(
        std::vector<Individual::shared_ptr>* population,
        const std::vector<int>& new_cache_indexes);

private:
    bool use_value_caching_;
    k52::parallel::IWorkerPool::shared_ptr fitness_worker_pool_;
    k52::optimization::Cache::shared_ptr cache_;
    boost::hash< std::vector<bool> > chromosome_hash_function_;
    int objective_function_counts_;
    int cache_hits_;

    DISALLOW_COPY_AND_ASSIGN(ObjectiveFunctionCounter);
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* OBJECTIVEFUNCTIONCOUNTER_H_ */
