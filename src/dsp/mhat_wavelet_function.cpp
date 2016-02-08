#include <k52/dsp/mhat_wavelet_function.h>
#include <cmath>

namespace
{
const double kDefaultSigma = 3.0;
}

namespace k52
{
namespace dsp
{

MhatWaveletFunction::MhatWaveletFunction() : k_(2./std::sqrt(3. * kDefaultSigma) * std::pow(M_PI, 0.25))
{
}

std::complex<double> MhatWaveletFunction::GetValue(double t)
{
    return std::complex<double>(real(t));
}

double MhatWaveletFunction::real(double value)
{
    double k = value / kDefaultSigma;
    return k_ * (1. - std::pow(k, 2.)) * std::exp(-0.5 * std::pow(k, 2.));
}


} // namespace dsp
} // namespace k52
