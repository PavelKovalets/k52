#include "objective_function_counter.h"

#include <stdexcept>

#include <parallel/worker_pool_factory.h>
#include <parallel/mpi/identifyable_objects_manager.h>

using ::std::vector;
using ::k52::parallel::WorkerPoolFactory;

namespace k52
{
namespace optimize
{

ObjectiveFunctionCounter::ObjectiveFunctionCounter(bool use_value_caching)
{
    cache_hits_ = 0;
    objective_function_counts_ = 0;
    use_value_caching_ = use_value_caching;

#ifdef BUILD_WITH_MPI
    CountObjectiveFunctionTask task;
    k52::parallel::mpi::IdentifyableObjectsManager::Instance().RegisterObject(task);
#endif
    if(WorkerPoolFactory::CanCreateWorkerPool(WorkerPoolFactory::kMpiWorkerPool))
    {
        fitness_worker_pool_ = WorkerPoolFactory::CreateWorkerPool(WorkerPoolFactory::kMpiWorkerPool);
    }
    else if(WorkerPoolFactory::CanCreateWorkerPool(WorkerPoolFactory::kThreadWorkerPool))
    {
        fitness_worker_pool_ = WorkerPoolFactory::CreateWorkerPool(WorkerPoolFactory::kThreadWorkerPool);
    }
    else if(WorkerPoolFactory::CanCreateWorkerPool(WorkerPoolFactory::kSequentialWorkerPool))
    {
        fitness_worker_pool_ = WorkerPoolFactory::CreateWorkerPool(WorkerPoolFactory::kSequentialWorkerPool);
    }
    else
    {
        throw std::runtime_error("Can not create fitness_worker_pool_.");
    }
}

void ObjectiveFunctionCounter::ObtainFitness(
    const IObjectiveFunction& objective_function,
    std::vector<Individual>* population)
{
    vector<const IParameters*> parameters_to_count;
    vector<int> indexes_to_count;

    ProcessPopulation(population, &parameters_to_count, &indexes_to_count);

    vector<double> counted_values = CountObjectiveFunctionValues(parameters_to_count, objective_function);

    for(size_t i=0; i<counted_values.size(); i++)
    {
        (*population)[ indexes_to_count[i] ] . set_fitness( counted_values[i] );
    }

    if(use_value_caching_)
    {
        AddNewCacheValues(population, indexes_to_count);
    }
}

vector<double> ObjectiveFunctionCounter::CountObjectiveFunctionValues(
    const vector<const IParameters*>& parameters_to_count,
    const IObjectiveFunction& objective_function)
{
    vector< CountObjectiveFunctionTask::shared_ptr > raw_tasks = CreateRawTasks(parameters_to_count, objective_function);
    vector< ObjectiveFunctionTaskResult::shared_ptr > results = Count(raw_tasks);

    vector<double> counted_values(parameters_to_count.size());

    for(size_t i=0; i<raw_tasks.size(); i++)
    {
        counted_values[i] =  results[i]->get_objective_function_value();
    }

    return counted_values;
}

void ObjectiveFunctionCounter::ResetCacheHits()
{
    cache_hits_ = 0;
}

int ObjectiveFunctionCounter::get_cache_hits() const
{
    return cache_hits_;
}

int ObjectiveFunctionCounter::get_objective_function_counts() const
{
    return objective_function_counts_;
}

void ObjectiveFunctionCounter::ProcessPopulation(
    vector<Individual>* population,
    vector<const IParameters*>* parameters_to_count,
    vector<int>* indexes_to_count)
{
    parameters_to_count->reserve(population->size());
    indexes_to_count->reserve(population->size());

    for(size_t i=0; i<population->size(); i++)
    {
        if(use_value_caching_)
        {
            StoredValue stored_fitness = cache_[(*population)[i].GetChromosome()];
            if(stored_fitness.has_value())
            {
                (*population)[i].set_fitness( stored_fitness.get_value() );
                cache_hits_ ++;
                continue;
            }
        }

        //These items should be evaluated further as they are not cached
        const IParameters* parameters = (*population)[i].GetParametersAccordingToChromosome();
        parameters_to_count->push_back(parameters);
        indexes_to_count->push_back(i);
    }
}

vector< ObjectiveFunctionTaskResult::shared_ptr > ObjectiveFunctionCounter::Count(
    const vector<CountObjectiveFunctionTask::shared_ptr>& raw_tasks)
{
    objective_function_counts_ += raw_tasks.size();
    vector< const k52::parallel::ITask* > raw_tasks_pointers = CreateRawTaskPointersVector(raw_tasks);

    vector< k52::parallel::ITaskResult::shared_ptr > raw_results = fitness_worker_pool_->DoTasks(raw_tasks_pointers);

    vector< ObjectiveFunctionTaskResult::shared_ptr > results(raw_results.size());
    for(size_t i = 0; i<raw_results.size(); i++)
    {
        results[i] = boost::dynamic_pointer_cast<ObjectiveFunctionTaskResult>(raw_results[i]);
    }
    return results;
}

std::vector< CountObjectiveFunctionTask::shared_ptr > ObjectiveFunctionCounter::CreateRawTasks(
    const vector<const IParameters*>& parameters_to_count,
    const IObjectiveFunction& objective_function)
{
    vector< CountObjectiveFunctionTask::shared_ptr > raw_tasks(parameters_to_count.size());

    for(size_t i=0; i<parameters_to_count.size(); i++)
    {
        raw_tasks[i] = CountObjectiveFunctionTask::shared_ptr( new CountObjectiveFunctionTask(parameters_to_count[i], &objective_function) );
    }

    return raw_tasks;
}

vector< const k52::parallel::ITask* > ObjectiveFunctionCounter::CreateRawTaskPointersVector(
    const vector<CountObjectiveFunctionTask::shared_ptr>& raw_tasks )
{
    vector<const k52::parallel::ITask*> raw_tasks_pointers(raw_tasks.size());

    for(size_t i=0; i<raw_tasks.size(); i++)
    {
        raw_tasks_pointers[i] = raw_tasks[i].get();
    }

    return raw_tasks_pointers;
}

void ObjectiveFunctionCounter::AddNewCacheValues(
    vector<Individual>* population, 
    const vector<int>&  new_cache_indexes)
{
    for(size_t i=0; i<new_cache_indexes.size(); i++)
    {
        Individual* current_individ = &(*population)[ new_cache_indexes[i] ];
        StoredValue stored_fitness( current_individ->get_fitness() );

        //TODO use hash instead of whole vector?
        cache_[current_individ->GetChromosome()] = stored_fitness;
    }
}

}/* namespace optimize */
}/* namespace k52 */
