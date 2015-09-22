#include  <k52/common/constants.h>

#include <cmath>

using k52::common::Constants;

namespace k52
{
namespace common
{
const double Constants::Eps = 1e-10;
const double Constants::Pi = 2 * asin(1);
const std::complex< double > Constants::ImaginaryUnit = sqrt((std::complex< double >)-1);

}/* namespace common */
}/* namespace k52 */

