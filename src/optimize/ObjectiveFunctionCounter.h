/*
 * ObjectiveFunctionCounter.h
 *
 *  Created on: Mar 18, 2012
 *      Author: feanor
 */

#ifndef OBJECTIVEFUNCTIONCOUNTER_H_
#define OBJECTIVEFUNCTIONCOUNTER_H_

#include <optimize/Individual.h>
#include <optimize/IObjectiveFunction.h>
#include "CountObjectiveFunctionTask.h"
#include "ObjectiveFunctionTaskResult.h"
#include <parallel/IWorkerPool.h>
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
	ObjectiveFunctionCounter(int nuberOfWorkers, bool useValueCaching);

	void obtainFitness(std::vector<Individual>* population, const IObjectiveFunction& objectiveFunction);

	void countObjectiveFunctionValues(std::vector<double>* valuesToSave,
			const std::vector<const IParameters*>& parametersToCount,
			const IObjectiveFunction& objectiveFunction);

    int getObjectiveFunctionCounts() const;

	int getCacheHits() const;

    void resetCacheHits();

protected:

    std::vector< ObjectiveFunctionTaskResult::shared_ptr > countParallel(const std::vector< std::pair<int, CountObjectiveFunctionTask> >& rawTasks);

    std::vector< ObjectiveFunctionTaskResult::shared_ptr > countSecuentially(const std::vector< std::pair<int, CountObjectiveFunctionTask> >& rawTasks);

    std::vector< std::pair<int, CountObjectiveFunctionTask> > getRawTasks(std::vector<Individual>* population,
		const IObjectiveFunction& objectiveFunction);

    std::vector< const k52::parallel::ITask* > createRawTaskPointersVector(const std::vector< std::pair<int, CountObjectiveFunctionTask> >& rawTasks );

	void fillRawTasks(const std::vector<const IParameters*>& parametersToCount,
			const IObjectiveFunction& objectiveFunction,
			std::vector<CountObjectiveFunctionTask>* rawTasks);

	void setCountedValues(std::vector<Individual>* population, const std::vector<double>& populationFitness);

	void addNewCacheValues(std::vector<Individual>* population, const std::vector< std::pair<int, CountObjectiveFunctionTask> >& newCacheIndexes);

private:
	ObjectiveFunctionCounter();

	bool _useValueCaching;
	int _nuberOfWorkers;
	k52::parallel::IWorkerPool::shared_ptr _fitnessWorkerPool;
	std::map<std::vector<bool>, StoredValue> _cache;
	int _cacheHits;
	int _objectiveFunctionCounts;

	DISALLOW_COPY_AND_ASSIGN(ObjectiveFunctionCounter);
};

}/* namespace optimize */
}/* namespace k52 */

#endif /* OBJECTIVEFUNCTIONCOUNTER_H_ */
