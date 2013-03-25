#include <k52/processing/morlet_wavelet_function.h>
#include <math.h>

namespace k52
{
namespace processing
{

/// Morlet implementation
double MorletWaveletFunction::real(double x, int index)
{
    return (exp(-x * x/2.) * cos(5. * x));
}

double MorletWaveletFunction::imag(double x, int index)
{
    return (exp(-x * x/2.) * sin(5. * x));
}

} // namespace processing
} // namespace k52

