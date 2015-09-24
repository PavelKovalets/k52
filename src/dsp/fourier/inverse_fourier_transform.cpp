#include <k52/dsp/fourier/inverse_fourier_transform.h>
#include <k52/dsp/fourier/fourier_transform.h>

namespace k52
{
namespace dsp
{

std::vector< std::complex< double > > InverseFourierTransform::Transform(const std::vector <std::complex< double>> &sequence)
{
    FourierTransform ft;

    size_t N = sequence.size();

    std::vector< std::complex< double > > directTransformResult = ft.Transform(sequence);

    std::vector< std::complex< double > > inverseTransformResult(N);

    for (int n = 0; n < N; ++n)
    {
        inverseTransformResult[n] = directTransformResult[(N - 1) - n] / (double) N;
    }

    return inverseTransformResult;
}

} // namespace dsp
} // namespace k52

