#include <k52/common/floating_point.h>

namespace k52
{
namespace common
{

bool FloatingPoint::AreEqual(double x, double y)
{
    return std::abs(x - y) < Constants::Eps;
}

bool FloatingPoint::IsZero(double x)
{
    return AreEqual(x, 0);
}

}/* namespace common */
}/* namespace k52 */