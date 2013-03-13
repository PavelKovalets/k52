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

using ::k52::parallel::WorkerPoolFactory;

ObjectiveFunctionCounter::ObjectiveFunctionCounter(int nuberOfWorkers, bool useValueCaching)
{
	_cacheHits = 0;
	_objectiveFunctionCounts = 0;
	_nuberOfWorkers = nuberOfWorkers;
	_useValueCaching = useValueCaching;

	//TODO remove nuberOfWorkers
	if(nuberOfWorkers > 0)
	{
#ifdef BUILD_WITH_MPI
		CountObjectiveFunctionTask task;
		k52::parallel::mpi::IdentifyableObjectsManager::Instance().registerObject(&task);
#endif
		if(WorkerPoolFactory::canCreateWorkerPool(k52::parallel::kMpiWorkerPool))
		{
			WorkerPoolFactory::createWorkerPool(k52::parallel::kMpiWorkerPool);
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
}

//TODO unite with countObjectiveFunctionValues
void ObjectiveFunctionCounter::obtainFitness(vector<Individual>* population,
		const IObjectiveFunction& objectiveFunction)
{
	vector< std::pair<int, CountObjectiveFunctionTask> > rawTasks = getRawTasks(population, objectiveFunction);
	vector< ObjectiveFunctionTaskResult::shared_ptr > results;

	if(_fitnessWorkerPool == NULL)
	{
		results = countSecuentially(rawTasks);
	}
	else
	{
		results = countParallel(rawTasks);
	}
	
	for(size_t i=0; i<results.size(); i++)
	{
		(*population)[ rawTasks[i].first ] . setFitness( results[i]->getObjectiveFunctionValue() );
	}

	if(_useValueCaching)
	{
		addNewCacheValues(population, rawTasks);
	}
}

void ObjectiveFunctionCounter::countObjectiveFunctionValues(vector<double>* valuesToSave,
			const vector<const IParameters*>& parametersToCount,
			const IObjectiveFunction& objectiveFunction)
{
	//TODO unite with ObtainFitness
	throw std::logic_error("Not implemented yet.");
//	queue<CountObjectiveFunctionTask> rawTasksQueue;
//
//	fillTasksQueue(valuesToSave, parametersToCount, objectiveFunction, &rawTasksQueue);
//
//	if(_fitnessWorkerPool == NULL)
//	{
//		this->countSecuentially(&rawTasksQueue);
//	}
//	else
//	{
//		this->countParallel(&rawTasksQueue);
//	}
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
		const vector< std::pair<int, CountObjectiveFunctionTask> >& rawTasks )
{
	vector<const k52::parallel::ITask*> rawTasksPtrs(rawTasks.size());

	for(size_t i=0; i<rawTasks.size(); i++)
	{
		rawTasksPtrs[i] = &(rawTasks[i].second);
	}

	return rawTasksPtrs;
}

vector< std::pair<int, CountObjectiveFunctionTask> > ObjectiveFunctionCounter::getRawTasks(
		vector<Individual>* population,
		const IObjectiveFunction& objectiveFunction)
{
	vector< std::pair<int, CountObjectiveFunctionTask> > rawTasks;
	rawTasks.reserve(population->size());

	//This function MUST be used only if caching is enabled
	for(size_t i=0; i<population->size(); i++)
	{
		StoredValue storedFitness = _cache[(*population)[i].getChromosome()];
		if(storedFitness.hasValue())
		{
			(*population)[i].setFitness( storedFitness.getValue() );
			_cacheHits ++;
			continue;
		}
		else
		{
			//These items should be evaluated further as they are not cached
			const IParameters* parameters = (*population)[i].getParametersAccordingToChromosome();
			CountObjectiveFunctionTask task(parameters, &objectiveFunction);
			rawTasks.push_back(std::pair<int, CountObjectiveFunctionTask>(i, task));
		}
	}
	return rawTasks;
}

void ObjectiveFunctionCounter::addNewCacheValues(vector<Individual>* population, const vector< std::pair<int, CountObjectiveFunctionTask> >&  newCacheIndexes)
{
	for(size_t i=0; i<newCacheIndexes.size(); i++)
	{
		Individual* currentIndivid = &(*population)[ newCacheIndexes[i].first ];
		StoredValue storedFitness( currentIndivid->getFitness() );

		//TODO use hash instead of whole vector?
		_cache[currentIndivid->getChromosome()] = storedFitness;
	}
}

//TODO use this for setting fitness
void ObjectiveFunctionCounter::setCountedValues(vector<Individual>* population, const vector<double>& populationFitness)
{
	for(size_t i=0; i<population->size(); i++)
	{
		if(populationFitness[i] < 0)
		{
			throw std::logic_error("Fitness counted by TargetFunction must be >= 0!");
		}

		(*population)[i].setFitness( populationFitness[i] );
	}
}


vector< ObjectiveFunctionTaskResult::shared_ptr > ObjectiveFunctionCounter::countParallel(
		const vector< std::pair<int, CountObjectiveFunctionTask> >& rawTasks)
{
	_objectiveFunctionCounts += rawTasks.size();
	vector< ObjectiveFunctionTaskResult::shared_ptr > results (rawTasks.size());
	vector< const k52::parallel::ITask* > rawTasksPtrs = createRawTaskPointersVector(rawTasks);

	std::vector< k52::parallel::ITaskResult::shared_ptr > rawResults = _fitnessWorkerPool->doTasks(rawTasksPtrs);
	//TODO unite this part with countSecuentially
	for(size_t i=0; i<rawTasks.size(); i++)
	{
		results[i] = boost::dynamic_pointer_cast<ObjectiveFunctionTaskResult>( rawResults[i] );
	}

	return results;
}

vector< ObjectiveFunctionTaskResult::shared_ptr > ObjectiveFunctionCounter::countSecuentially(
		const vector< std::pair<int, CountObjectiveFunctionTask> >& rawTasks)
{
	_objectiveFunctionCounts += rawTasks.size();
	vector< ObjectiveFunctionTaskResult::shared_ptr > results (rawTasks.size());

	for(size_t i=0; i<rawTasks.size(); i++)
	{
		results[i] = boost::dynamic_pointer_cast<ObjectiveFunctionTaskResult>( rawTasks[i].second.perform() );
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

