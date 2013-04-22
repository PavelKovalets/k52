#ifndef DELAYSUPPLIER_H_
#define DELAYSUPPLIER_H_

namespace k52
{
namespace parallel
{
namespace mpi
{

class DelaySupplier
{
public:
    DelaySupplier();

    void SleepWithCurrentDelay();
    void IncreaseDelay();
    void ResetDelay();

private:
    static void Sleep(int milliseconds);

    int initial_delay_;
    int maximum_delay_;
    int current_delay_;
};

} /* namespace mpi */
} /* parallel */
} /* k52 */

#endif /* DELAYSUPPLIER_H_ */
