#include "statistics_aggregator.h"

namespace k52
{
namespace parallel
{

StatisticsAggregator::StatisticsAggregator(){}

void StatisticsAggregator::RegisterCount(const int& worker_id)
{
    WorkerStatistics statistics = GetAppropriateStatistics(worker_id);
    statistics.IncreaseCounted();
    statistics_[worker_id] = statistics;
}

void StatisticsAggregator::RegisterError(const int& worker_id)
{
    WorkerStatistics statistics = GetAppropriateStatistics(worker_id);
    statistics.IncreaseErrors();
    statistics_[worker_id] = statistics;
}

std::vector<WorkerStatistics> StatisticsAggregator::GetStatistics()
{
    std::vector<WorkerStatistics> statistics;
    statistics.reserve(statistics_.size());

    for(StatisticsContainer::iterator it = statistics_.begin(); it != statistics_.end(); it++)
    {
        statistics.push_back( (*it).second );
    }

    return statistics;
}

WorkerStatistics StatisticsAggregator::GetAppropriateStatistics(const int& worker_id)
{
    StatisticsContainer::iterator it = statistics_.find(worker_id);
    WorkerStatistics statistics(0, 0, worker_id);

    if(it != statistics_.end())
    {
        statistics = (*it).second;
    }

    return statistics;
}

} /* namespace parallel */
} /* namespace k52 */
