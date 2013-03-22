/*
 * ObjectiveFunctionCounter.h
 *
 *  Created on: Mar 18, 2012
 *      Author: feanor
 */

#ifndef OBJECTIVEFUNCTIONCOUNTER_H_
#define OBJECTIVEFUNCTIONCOUNTER_H_

#include <optimize/i_objective_function.h>
#include <optimize/individual.h>
#include "CountObjectiveFunctionTask.h"
#include "objective_function_task_result.h"
#include <parallel/i_worker_pool.h>
#include <map>
#include <vector>
#include <queue>
#include <common/disallow_copy_and_assign.h>

namespace k52
{
namespace optimize
{

class StoredValue
{
public:

	StoredValue() : _hasValue(false) {}

	StoredValue(double fitness) : _hasValue(true), _value(fitness) {}

	bool hasValue()	{ return _hasValue; }

	double getValue() { return _value; }

private:
	bool _hasValue;
	double _value;
};

class ObjectiveFunctionCounter
{
public:
	typedef boost::shared_ptr<ObjectiveFunctionCounter> shared_ptr;

	ObjectiveFunctionCounter(bool useValueCaching);

	void obtainFitness(std::vector<Individual>* population, const IObjectiveFunction& objectiveFunction);

	std::vector<double> countObjectiveFunctionValues(
			const std::vector<const IParameters*>& parametersToCount,
			const IObjectiveFunction& objectiveFunction);

    int getObjectiveFunctionCounts() const;

	int getCacheHits() const;

    void resetCacheHits();

protected:
    void processPopulation(
    		std::vector<Individual>* population,
    		std::vector<const IParameters*>* parametersToCount,
    		std::vector<int>* indexesToCount);

    std::vector< ObjectiveFunctionTaskResult::shared_ptr > count(const std::vector<CountObjectiveFunctionTask::shared_ptr>& rawTasks);

    std::vector< CountObjectiveFunctionTask::shared_ptr > createRawTasks(
    		const std::vector<const IParameters*>& parametersToCount,
    		const IObjectiveFunction& objectiveFunction);

    std::vector< const k52::parallel::ITask* > createRawTaskPointersVector(
    		const std::vector<CountObjectiveFunctionTask::shared_ptr>& rawTasks );

	void addNewCacheValues(std::vector<Individual>* population, const std::vector<int>& newCacheIndexes);

private:
	ObjectiveFunctionCounter();

	bool _useValueCaching;
	k52::parallel::IWorkerPool::shared_ptr _fitnessWorkerPool;
	std::map<std::vector<bool>, StoredValue> _cache;
	int _cacheHits;
	int _objectiveFunctionCounts;

	DISALLOW_COPY_AND_ASSIGN(ObjectiveFunctionCounter);
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* OBJECTIVEFUNCTIONCOUNTER_H_ */
