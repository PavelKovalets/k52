#include <processing/haar_wavelet_function.h>
#include <math.h>

namespace k52
{
namespace processing
{

// Haar wavelet function implementation
double HaarWaveletFunction::real(double x, int index)
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

double HaarWaveletFunction::imag(double x, int index)
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

} // namespace processing
} // namespace k52
