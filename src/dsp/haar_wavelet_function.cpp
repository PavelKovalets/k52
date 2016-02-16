#include <k52/dsp/haar_wavelet_function.h>

namespace k52
{
namespace dsp
{

std::complex<double> HaarWaveletFunction::GetValue(double t)
{
    return std::complex<double>(real(t), imag(t));
}

// Haar wavelet function implementation
double HaarWaveletFunction::real(double x)
{
    if (x < -0.5 || x > 0.5 || x == 0 )
    {
        return 0;
    }

    if (x >= -0.5 && x < 0)
    {
        return -1;
    }

    return 1;
}

double HaarWaveletFunction::imag(double x)
{
    if (x < -0.25 || x > 0.75 || x == 0.25)
    {
        return 0;
    }

    if (x >= -0.25 && x < 0.25)
    {
        return -1;
    }

    return 1;
}

} // namespace dsp
} // namespace k52
