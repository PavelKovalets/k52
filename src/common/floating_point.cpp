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

bool FloatingPoint::AreEqual(
    const std::vector<double>& vector1,
    const std::vector<double>& vector2)
{
    if (vector1.size() != vector2.size())
    {
        return false;
    }

    for (size_t i = 0; i < vector1.size(); ++i)
    {
        if (!AreEqual(vector1[i], vector2[i]))
        {
            return false;
        }
    }

    return true;
}

}/* namespace common */
}/* namespace k52 */