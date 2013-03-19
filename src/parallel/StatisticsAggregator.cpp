/*
 * StatisticsAggregator.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: feanor
 */

#include "StatisticsAggregator.h"

namespace k52
{
namespace parallel
{

StatisticsAggregator::StatisticsAggregator(){}

void StatisticsAggregator::registerCount(const int& workerId)
{
	WorkerStatistics statistics = getAppropriateStatistics(workerId);
	statistics.IncreaseCounted();
	_statistics[workerId] = statistics;
}

void StatisticsAggregator::registerError(const int& workerId)
{
	WorkerStatistics statistics = getAppropriateStatistics(workerId);
	statistics.IncreaseErrors();
	_statistics[workerId] = statistics;
}

std::vector<WorkerStatistics> StatisticsAggregator::getStatistics()
{
	std::vector<WorkerStatistics> statistics;
	statistics.reserve(_statistics.size());

	for(StatisticsContainer::iterator it = _statistics.begin(); it != _statistics.end(); it++)
	{
		statistics.push_back( (*it).second );
	}

	return statistics;
}

WorkerStatistics StatisticsAggregator::getAppropriateStatistics(const int& workerId)
{
	StatisticsContainer::iterator it = _statistics.find(workerId);
	WorkerStatistics statistics(0, 0, workerId);

	if(it != _statistics.end())
	{
		statistics = (*it).second;
	}

	return statistics;
}

} /* namespace parallel */
} /* namespace k52 */
