#include <k52/dsp/transform/wavelet/logarithmic_scale.h>
#include <stdexcept>
#include <math.h>

using ::std::vector;
using ::std::invalid_argument;

namespace k52
{
namespace dsp
{

LogarithmicScale::LogarithmicScale(int min_exponent, int max_exponent)
{
    if(min_exponent >= max_exponent)
    {
        throw invalid_argument("min_exponent >= max_exponent");
    }

    scales_ = CalculateScales(min_exponent, max_exponent);
}

vector< double > LogarithmicScale::GetScales() const
{
    return scales_;
}

vector< double > LogarithmicScale::CalculateScales(int min_exponent, int max_exponent)
{
    int size = max_exponent - min_exponent + 1;
    vector< double > scales(size);

    double initial_scale = pow(2, min_exponent);

    for (int i = 0; i < size; ++i)
    {
        scales[i] = initial_scale;
        initial_scale *= 2;
    }

    return scales;
}

} // namespace dsp
} // namespace k52