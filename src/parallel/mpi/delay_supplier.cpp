#include "delay_supplier.h"

#include <unistd.h>

namespace k52
{
namespace parallel
{
namespace mpi
{

DelaySupplier::DelaySupplier()
{
    initial_delay_ = 1000;
    maximum_delay_ = 1000000;
    current_delay_ = initial_delay_;
}

void DelaySupplier::SleepWithCurrentDelay()
{
    usleep(current_delay_);
}

void DelaySupplier::IncreaseDelay()
{
    current_delay_ *= 10;

    if(current_delay_ > maximum_delay_)
    {
        current_delay_ = maximum_delay_;
    }
}

void DelaySupplier::ResetDelay()
{
    current_delay_ = initial_delay_;
}

} /* namespace mpi */
} /* parallel */
} /* k52 */
