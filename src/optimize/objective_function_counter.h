#ifndef OBJECTIVEFUNCTIONCOUNTER_H_
#define OBJECTIVEFUNCTIONCOUNTER_H_

#include <map>
#include <vector>
#include <queue>

#include <common/disallow_copy_and_assign.h>
#include <parallel/i_worker_pool.h>
#include <optimize/i_objective_function.h>
#include <optimize/individual.h>

#include "stored_value.h"
#include "count_objective_function_task.h"
#include "objective_function_task_result.h"

namespace k52
{
namespace optimize
{

class ObjectiveFunctionCounter
{
public:
    typedef boost::shared_ptr<ObjectiveFunctionCounter> shared_ptr;

    explicit ObjectiveFunctionCounter(bool use_value_caching);

    void ObtainFitness(
        const IObjectiveFunction& objective_function,
        std::vector<Individual>* population);

    std::vector<double> CountObjectiveFunctionValues(
        const std::vector<const IParameters*>& parameters_to_count,
        const IObjectiveFunction& objective_function);

    void ResetCacheHits();
    int get_cache_hits() const;
    int get_objective_function_counts() const;

protected:
    void ProcessPopulation(
        std::vector<Individual>* population,
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
        std::vector<Individual>* population,
        const std::vector<int>& new_cache_indexes);

private:
    bool use_value_caching_;
    k52::parallel::IWorkerPool::shared_ptr fitness_worker_pool_;
    std::map<std::vector<bool>, StoredValue> cache_;
    int objective_function_counts_;
    int cache_hits_;

    DISALLOW_COPY_AND_ASSIGN(ObjectiveFunctionCounter);
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* OBJECTIVEFUNCTIONCOUNTER_H_ */
