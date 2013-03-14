/*
 * StatisticsAggregator.h
 *
 *  Created on: Mar 14, 2013
 *      Author: feanor
 */

#ifndef STATISTICSAGGREGATOR_H_
#define STATISTICSAGGREGATOR_H_

#include <parallel/WorkerStatistics.h>
#include <vector>
#include <map>

namespace k52
{
namespace parallel
{

class StatisticsAggregator
{
public:
	void registerCount(const int& workerId);
	void registerError(const int& workerId);
	std::vector<WorkerStatistics> getStatistics();

protected:
	WorkerStatistics getAppropriateStatistics(const int& workerId);

private:
	typedef std::map<int,WorkerStatistics> StatisticsContainer;
	StatisticsContainer _statistics;
};

} /* namespace parallel */
} /* namespace k52 */

#endif /* STATISTICSAGGREGATOR_H_ */
