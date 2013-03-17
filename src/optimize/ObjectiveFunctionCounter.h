/*
 * ObjectiveFunctionCounter.h
 *
 *  Created on: Mar 18, 2012
 *      Author: feanor
 */

#ifndef OBJECTIVEFUNCTIONCOUNTER_H_
#define OBJECTIVEFUNCTIONCOUNTER_H_

#include <optimize/IObjectiveFunction.h>
#include <optimize/Individual.h>
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

    std::vector< ObjectiveFunctionTaskResult::shared_ptr > count(const std::vector< std::pair<int, CountObjectiveFunctionTask::shared_ptr> >& rawTasks);

    std::vector< std::pair<int, CountObjectiveFunctionTask::shared_ptr> > getRawTasks(std::vector<Individual>* population,
		const IObjectiveFunction& objectiveFunction);

    std::vector< const k52::parallel::ITask* > createRawTaskPointersVector(const std::vector< std::pair<int, CountObjectiveFunctionTask::shared_ptr> >& rawTasks );

	void fillRawTasks(const std::vector<const IParameters*>& parametersToCount,
			const IObjectiveFunction& objectiveFunction,
			std::vector<CountObjectiveFunctionTask>* rawTasks);

	void addNewCacheValues(std::vector<Individual>* population, const std::vector< std::pair<int, CountObjectiveFunctionTask::shared_ptr> >& newCacheIndexes);

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
