#include <k52/dsp/morlet_wavelet_function.h>
#include <cmath>

#include <k52/common/constants.h>

using ::k52::common::Constants;

namespace k52
{
namespace dsp
{

std::complex<double> MorletWaveletFunction::GetValue(double t)
{
    return std::exp(5 * t * Constants::ImaginaryUnit - t * t/2.);
}

} // namespace dsp
} // namespace k52

