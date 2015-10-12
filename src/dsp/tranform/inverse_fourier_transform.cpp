#include <k52/dsp/transform/inverse_fourier_transform.h>
#include <k52/dsp/transform/fourier_transform.h>
#include <k52/common/helpers.h>

using k52::common::Helpers;
using k52::dsp::IFourierTransform;

namespace k52
{
namespace dsp
{

InverseFourierTransform::InverseFourierTransform(IFourierTransform::shared_ptr fourier_transform)
        : _fourier_transform (fourier_transform)
{
}

std::vector< std::complex< double > > InverseFourierTransform::Transform(const std::vector <std::complex< double> > &sequence) const
{
    size_t N = sequence.size();

    std::vector< std::complex< double > > directTransformResult = _fourier_transform->Transform(
            Helpers::Conjugate(sequence)
    );
    std::vector< std::complex< double > > inverseTransformResult = Helpers::Conjugate(directTransformResult);

    for (int n = 0; n < N; ++n)
    {
        inverseTransformResult[n] = inverseTransformResult[n] / (double) N;
    }

    return inverseTransformResult;
}

} // namespace dsp
} // namespace k52

