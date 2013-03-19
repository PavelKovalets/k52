/*
 * StatisticsAggregator.h
 *
 *  Created on: Mar 14, 2013
 *      Author: feanor
 */

#ifndef STATISTICSAGGREGATOR_H_
#define STATISTICSAGGREGATOR_H_

#include <vector>
#include <map>
#include <common/disallow_copy_and_assign.h>
#include <parallel/worker_statistics.h>

namespace k52
{
namespace parallel
{

class StatisticsAggregator
{
public:
	StatisticsAggregator();
	void registerCount(const int& workerId);
	void registerError(const int& workerId);
	std::vector<WorkerStatistics> getStatistics();

protected:
	WorkerStatistics getAppropriateStatistics(const int& workerId);

private:
	typedef std::map<int,WorkerStatistics> StatisticsContainer;
	StatisticsContainer _statistics;

	DISALLOW_COPY_AND_ASSIGN(StatisticsAggregator);
};

} /* namespace parallel */
} /* namespace k52 */

#endif /* STATISTICSAGGREGATOR_H_ */
