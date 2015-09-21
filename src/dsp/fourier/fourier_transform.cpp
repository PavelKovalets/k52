#include <k52/dsp/fourier/fourier_transform.h>

#include <cmath>

namespace k52
{
namespace dsp
{


std::vector< std::complex< double > > FourierTransform::Transform(const std::vector< std::complex< double > >& sequence)
{
    std::complex< double > i;
    i = -1;
    i = sqrt(i);
    double pi = 2 * asin(1);

    size_t N = sequence.size();
    std::vector< std::complex< double > > result(N);

    for (size_t k = 0; k < N; ++k)
    {
        result[k] = 0;

        for (size_t n = 0; n < N; ++n)
        {
            result[k] += sequence[n] * exp( -2 * pi * i *(double) k * (double)n /(double) N);
        }
    }

    return result;
}

} // namespace dsp
} // namespace k52
