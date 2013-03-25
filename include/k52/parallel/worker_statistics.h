#ifndef WORKERSTATISTICS_H_
#define WORKERSTATISTICS_H_

namespace k52
{
namespace parallel
{

class WorkerStatistics
{
public:
    WorkerStatistics();

    WorkerStatistics(int counted, int errors, int id);

    void IncreaseCounted();

    void IncreaseErrors();

    int get_counted() const;

    int get_errors() const;

    int get_id() const;

protected:
    int counted_;
    int errors_;
    int id_;
};

} /* namespace parallel */
} /* namespace k52 */
#endif /* WORKERSTATISTICS_H_ */
