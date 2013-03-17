/*
 * FitnessCounter.cpp
 *
 *  Created on: Mar 18, 2012
 *      Author: feanor
 */

#include "ObjectiveFunctionCounter.h"
#include <parallel/WorkerPoolFactory.h>
#include <parallel/mpi/IdentifyableObjectsManager.h>
#include <stdexcept>

using ::std::vector;
using ::k52::parallel::WorkerPoolFactory;

namespace k52
{
namespace optimize
{

ObjectiveFunctionCounter::ObjectiveFunctionCounter(bool useValueCaching)
{
	_cacheHits = 0;
	_objectiveFunctionCounts = 0;
	_useValueCaching = useValueCaching;

#ifdef BUILD_WITH_MPI
	CountObjectiveFunctionTask task;
	k52::parallel::mpi::IdentifyableObjectsManager::Instance().registerObject(&task);
#endif
	if(WorkerPoolFactory::canCreateWorkerPool(k52::parallel::kMpiWorkerPool))
	{
		_fitnessWorkerPool = WorkerPoolFactory::createWorkerPool(k52::parallel::kMpiWorkerPool);
	}
	else if(WorkerPoolFactory::canCreateWorkerPool(k52::parallel::kThreadWorkerPool))
	{
		_fitnessWorkerPool = WorkerPoolFactory::createWorkerPool(k52::parallel::kThreadWorkerPool);
	}
	else if(WorkerPoolFactory::canCreateWorkerPool(k52::parallel::kSequentialWorkerPool))
	{
		_fitnessWorkerPool = WorkerPoolFactory::createWorkerPool(k52::parallel::kSequentialWorkerPool);
	}
	else
	{
		throw std::runtime_error("Can not create _fitnessWorkerPool.");
	}
}

//TODO unite with countObjectiveFunctionValues
void ObjectiveFunctionCounter::obtainFitness(vector<Individual>* population,
		const IObjectiveFunction& objectiveFunction)
{
	vector< std::pair<int, CountObjectiveFunctionTask::shared_ptr> > rawTasks = getRawTasks(population, objectiveFunction);
	vector< ObjectiveFunctionTaskResult::shared_ptr > results = count(rawTasks);
	
	for(size_t i=0; i<results.size(); i++)
	{
		(*population)[ rawTasks[i].first ] . setFitness( results[i]->getObjectiveFunctionValue() );
	}

	if(_useValueCaching)
	{
		addNewCacheValues(population, rawTasks);
	}
}

vector<double> ObjectiveFunctionCounter::countObjectiveFunctionValues(
			const vector<const IParameters*>& parametersToCount,
			const IObjectiveFunction& objectiveFunction)
{
	vector<double> countedValues(parametersToCount.size());

	//TODO unite with ObtainFitness
		throw std::logic_error("Not implemented yet.");

	return countedValues;
}

void ObjectiveFunctionCounter::fillRawTasks(
			const vector<const IParameters*>& parametersToCount,
			const IObjectiveFunction& objectiveFunction,
			vector<CountObjectiveFunctionTask>* rawTasks)
{
	//TODO unite with fillRawTasks#2
	throw std::logic_error("Not implemented yet.");
//	for(size_t i=0; i<parametersToCount.size(); i++)
//	{
//		CountObjectiveFunctionTask t(parametersToCount[i], &objectiveFunction);
//		(*rawTasks)[i] = t;
//	}
}

vector< const k52::parallel::ITask* > ObjectiveFunctionCounter::createRawTaskPointersVector(
		const vector< std::pair<int, CountObjectiveFunctionTask::shared_ptr> >& rawTasks )
{
	vector<const k52::parallel::ITask*> rawTasksPtrs(rawTasks.size());

	for(size_t i=0; i<rawTasks.size(); i++)
	{
		rawTasksPtrs[i] = rawTasks[i].second.get();
	}

	return rawTasksPtrs;
}

vector< std::pair<int, CountObjectiveFunctionTask::shared_ptr> > ObjectiveFunctionCounter::getRawTasks(
		vector<Individual>* population,
		const IObjectiveFunction& objectiveFunction)
{
	vector< std::pair<int, CountObjectiveFunctionTask::shared_ptr> > rawTasks;
	rawTasks.reserve(population->size());

	//This function MUST be used only if caching is enabled
	for(size_t i=0; i<population->size(); i++)
	{
		StoredValue storedFitness = _cache[(*population)[i].getChromosome()];
		if(storedFitness.hasValue())
		{
			//TODO single place for setting fitness?
			(*population)[i].setFitness( storedFitness.getValue() );
			_cacheHits ++;
			continue;
		}
		else
		{
			//These items should be evaluated further as they are not cached
			const IParameters* parameters = (*population)[i].getParametersAccordingToChromosome();
			CountObjectiveFunctionTask::shared_ptr task(new CountObjectiveFunctionTask(parameters, &objectiveFunction));
			rawTasks.push_back(std::pair<int, CountObjectiveFunctionTask::shared_ptr>(i, task));
		}
	}
	return rawTasks;
}

void ObjectiveFunctionCounter::addNewCacheValues(vector<Individual>* population, const vector< std::pair<int, CountObjectiveFunctionTask::shared_ptr> >&  newCacheIndexes)
{
	for(size_t i=0; i<newCacheIndexes.size(); i++)
	{
		Individual* currentIndivid = &(*population)[ newCacheIndexes[i].first ];
		StoredValue storedFitness( currentIndivid->getFitness() );

		//TODO use hash instead of whole vector?
		_cache[currentIndivid->getChromosome()] = storedFitness;
	}
}

vector< ObjectiveFunctionTaskResult::shared_ptr > ObjectiveFunctionCounter::count(
		const vector< std::pair<int, CountObjectiveFunctionTask::shared_ptr> >& rawTasks)
{
	_objectiveFunctionCounts += rawTasks.size();
	vector< ObjectiveFunctionTaskResult::shared_ptr > results (rawTasks.size());
	vector< const k52::parallel::ITask* > rawTasksPtrs = createRawTaskPointersVector(rawTasks);

	std::vector< k52::parallel::ITaskResult::shared_ptr > rawResults = _fitnessWorkerPool->doTasks(rawTasksPtrs);

	for(size_t i=0; i<rawTasks.size(); i++)
	{
		results[i] = boost::dynamic_pointer_cast<ObjectiveFunctionTaskResult>( rawResults[i] );
	}

	return results;
}

int ObjectiveFunctionCounter::getObjectiveFunctionCounts() const
{
    return _objectiveFunctionCounts;
}

int ObjectiveFunctionCounter::getCacheHits() const
{
    return _cacheHits;
}

void ObjectiveFunctionCounter::resetCacheHits()
{
	_cacheHits = 0;
}

}/* namespace optimize */
}/* namespace k52 */
