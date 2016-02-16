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
    //TODO
    return std::exp(-t * t/2.) * std::exp(  5* t * Constants::ImaginaryUnit);
}

} // namespace dsp
} // namespace k52

