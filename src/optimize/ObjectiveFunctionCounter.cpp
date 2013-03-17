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

void ObjectiveFunctionCounter::processPopulation(
		vector<Individual>* population,
		vector<const IParameters*>* parametersToCount,
		vector<int>* indexesToCount)
{
	parametersToCount->reserve(population->size());
	indexesToCount->reserve(population->size());

	for(size_t i=0; i<population->size(); i++)
	{
		if(_useValueCaching)
		{
			StoredValue storedFitness = _cache[(*population)[i].getChromosome()];
			if(storedFitness.hasValue())
			{
				(*population)[i].setFitness( storedFitness.getValue() );
				_cacheHits ++;
				continue;
			}
		}

		//These items should be evaluated further as they are not cached
		const IParameters* parameters = (*population)[i].getParametersAccordingToChromosome();
		parametersToCount->push_back(parameters);
		indexesToCount->push_back(i);
	}
}

void ObjectiveFunctionCounter::obtainFitness(vector<Individual>* population,
		const IObjectiveFunction& objectiveFunction)
{
	vector<const IParameters*> parametersToCount;
	vector<int> indexesToCount;

	processPopulation(population, &parametersToCount, &indexesToCount);

	vector<double> countedValues = countObjectiveFunctionValues(parametersToCount, objectiveFunction);
	
	for(size_t i=0; i<countedValues.size(); i++)
	{
		(*population)[ indexesToCount[i] ] . setFitness( countedValues[i] );
	}

	if(_useValueCaching)
	{
		addNewCacheValues(population, indexesToCount);
	}
}

vector<double> ObjectiveFunctionCounter::countObjectiveFunctionValues(
			const vector<const IParameters*>& parametersToCount,
			const IObjectiveFunction& objectiveFunction)
{
	vector< CountObjectiveFunctionTask::shared_ptr > rawTasks = createRawTasks(parametersToCount, objectiveFunction);
	vector< ObjectiveFunctionTaskResult::shared_ptr > results = count(rawTasks);

	vector<double> countedValues(parametersToCount.size());

	for(size_t i=0; i<rawTasks.size(); i++)
	{
		countedValues[i] = boost::dynamic_pointer_cast<ObjectiveFunctionTaskResult>( results[i] )->getObjectiveFunctionValue();
	}

	return countedValues;
}

vector< ObjectiveFunctionTaskResult::shared_ptr > ObjectiveFunctionCounter::count(
		const vector<CountObjectiveFunctionTask::shared_ptr>& rawTasks)
{
	_objectiveFunctionCounts += rawTasks.size();
	vector< ObjectiveFunctionTaskResult::shared_ptr > results (rawTasks.size());
	vector< const k52::parallel::ITask* > rawTasksPtrs = createRawTaskPointersVector(rawTasks);

	std::vector< k52::parallel::ITaskResult::shared_ptr > rawResults = _fitnessWorkerPool->doTasks(rawTasksPtrs);

	return results;
}

vector< const k52::parallel::ITask* > ObjectiveFunctionCounter::createRawTaskPointersVector(
		const vector<CountObjectiveFunctionTask::shared_ptr>& rawTasks )
{
	vector<const k52::parallel::ITask*> rawTasksPtrs(rawTasks.size());

	for(size_t i=0; i<rawTasks.size(); i++)
	{
		rawTasksPtrs[i] = rawTasks[i].get();
	}

	return rawTasksPtrs;
}

std::vector< CountObjectiveFunctionTask::shared_ptr > ObjectiveFunctionCounter::createRawTasks(
		const vector<const IParameters*>& parametersToCount,
		const IObjectiveFunction& objectiveFunction)
{
	vector< CountObjectiveFunctionTask::shared_ptr > rawTasks(parametersToCount.size());

	for(size_t i=0; i<parametersToCount.size(); i++)
	{
		rawTasks[i] = CountObjectiveFunctionTask::shared_ptr( new CountObjectiveFunctionTask(parametersToCount[i], &objectiveFunction) );
	}

	return rawTasks;
}

void ObjectiveFunctionCounter::addNewCacheValues(vector<Individual>* population, const vector<int>&  newCacheIndexes)
{
	for(size_t i=0; i<newCacheIndexes.size(); i++)
	{
		Individual* currentIndivid = &(*population)[ newCacheIndexes[i] ];
		StoredValue storedFitness( currentIndivid->getFitness() );

		//TODO use hash instead of whole vector?
		_cache[currentIndivid->getChromosome()] = storedFitness;
	}
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
