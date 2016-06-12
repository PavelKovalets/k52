#ifndef K52_FLOATING_POINT_H
#define K52_FLOATING_POINT_H

#include <cmath>
#include <vector>
#include "constants.h"

namespace k52
{
namespace common
{

class FloatingPoint
{
public:
    static bool AreEqual(double x, double y);
    static bool AreEqual(
        const std::vector<double>&,
        const std::vector<double>&);
    static bool IsZero(double x);
};

}/* namespace common */
}/* namespace k52 */

#endif //K52_FLOATING_POINT_H
