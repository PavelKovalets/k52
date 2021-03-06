#include <k52/parallel/worker_statistics.h>

namespace k52
{
namespace parallel
{

WorkerStatistics::WorkerStatistics()
    : counted_(0)
    , errors_(0)
    , id_()
{
}

WorkerStatistics::WorkerStatistics(int counted, int errors, int id)
    : counted_(counted)
    , errors_(errors)
    , id_(id)
{
}

void WorkerStatistics::IncreaseCounted()
{
    ++counted_;
}

void WorkerStatistics::IncreaseErrors()
{
    errors_++; // encoding issue with prefix increment
}

int WorkerStatistics::get_counted() const
{
    return counted_;
}

int WorkerStatistics::get_errors() const
{
    return errors_;
}

int WorkerStatistics::get_id() const
{
    return id_;
}

} // namespace parallel
} // namespace k52
