#include <k52/dsp/morlet_wavelet_function.h>
#include <math.h>

namespace k52
{
namespace dsp
{

/// Morlet implementation
double MorletWaveletFunction::real(double x, int)
{
    return (exp(-x * x/2.) * cos(5. * x));
}

double MorletWaveletFunction::imag(double x, int)
{
    return (exp(-x * x/2.) * sin(5. * x));
}

} // namespace dsp
} // namespace k52

