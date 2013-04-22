#include "delay_supplier.h"

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#inlcude <windows.h>
#endif

namespace k52
{
namespace parallel
{
namespace mpi
{

DelaySupplier::DelaySupplier()
{
    initial_delay_ = 1;
    maximum_delay_ = 1000;
    current_delay_ = initial_delay_;
}

void DelaySupplier::SleepWithCurrentDelay()
{
    DelaySupplier::Sleep(current_delay_);
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

void DelaySupplier::Sleep(int milliseconds)
{
#ifdef LINUX
    usleep(milliseconds * 1000);   // usleep takes sleep time in us
#endif
#ifdef WINDOWS
    Sleep(milliseconds);
#endif
}

} /* namespace mpi */
} /* parallel */
} /* k52 */
