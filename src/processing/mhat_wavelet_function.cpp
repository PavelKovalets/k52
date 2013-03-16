#include <processing/mhat_wavelet_function.h>
#include <math.h>

namespace
{
const double kDefaultSigma = 3.0;
}

namespace k52
{
namespace processing
{

MhatWaveletFunction::MhatWaveletFunction() : k_(2./sqrt(3. * kDefaultSigma) * pow(M_PI, 0.25))
{
}

double MhatWaveletFunction::real(double value, int index)
{
    double k = value / kDefaultSigma;
    return k_ * (1. - pow(k, 2.)) * exp(-0.5 * pow(k, 2.));
}

double MhatWaveletFunction::imag(double value, int index)
{
    return 0;
}

} // namespace processing
} // namespace k52
