#include <k52/dsp/transform/fourier_transform.h>

#include  <k52/common/constants.h>

using ::k52::common::Constants;
using ::std::vector;
using ::std::complex;

namespace k52
{
namespace dsp
{

vector< complex< double > > FourierTransform::Transform(const vector< complex< double > >& sequence) const
{
    size_t N = sequence.size();
    vector< complex< double > > result(N);

    for (size_t k = 0; k < N; ++k)
    {
        result[k] = 0;

        for (size_t n = 0; n < N; ++n)
        {
            result[k] += sequence[n] * exp( -2 * Constants::Pi * Constants::ImaginaryUnit *(double) k * (double)n /(double) N);
        }
    }

    return result;
}

} // namespace dsp
} // namespace k52
