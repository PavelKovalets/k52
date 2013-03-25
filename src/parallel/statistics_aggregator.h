#ifndef STATISTICSAGGREGATOR_H_
#define STATISTICSAGGREGATOR_H_

#include <vector>
#include <map>

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/parallel/worker_statistics.h>

namespace k52
{
namespace parallel
{

class StatisticsAggregator
{
public:
    StatisticsAggregator();

    void RegisterCount(const int& worker_id);
    void RegisterError(const int& worker_id);
    std::vector<WorkerStatistics> GetStatistics();

protected:
    WorkerStatistics GetAppropriateStatistics(const int& worker_id);

private:
    typedef std::map<int,WorkerStatistics> StatisticsContainer;

    StatisticsContainer statistics_;

    DISALLOW_COPY_AND_ASSIGN(StatisticsAggregator);
};

} /* namespace parallel */
} /* namespace k52 */

#endif /* STATISTICSAGGREGATOR_H_ */
