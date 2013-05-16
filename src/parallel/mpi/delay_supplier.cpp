#include "delay_supplier.h"

#include <boost/static_assert.hpp>

#ifdef __unix__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
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
    DelaySupplier::SleepMillisec(current_delay_);
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

void DelaySupplier::SleepMillisec(int milliseconds)
{
#ifdef __unix__
    usleep(milliseconds * 1000);   // usleep takes sleep time in us
#elif _WIN32
    Sleep(milliseconds);
#else
    BOOST_STATIC_ASSERT_MSG(false, "Current system is not supported in k52::parallel::mpi::DelaySupplier::SleepMillisec");
#endif
}

} /* namespace mpi */
} /* namespace parallel */
} /* namespace k52 */
