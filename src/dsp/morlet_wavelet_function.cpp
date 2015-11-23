#include <k52/dsp/morlet_wavelet_function.h>
#include <cmath>

namespace k52
{
namespace dsp
{

/// Morlet implementation
double MorletWaveletFunction::real(double x, int)
{
    return (std::exp(-x * x/2.) * std::cos(5. * x));
}

double MorletWaveletFunction::imag(double x, int)
{
    return (std::exp(-x * x/2.) * std::sin(5. * x));
}

} // namespace dsp
} // namespace k52

