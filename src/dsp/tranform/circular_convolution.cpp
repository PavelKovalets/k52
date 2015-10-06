#include <k52/dsp/transform/circular_convolution.h>
#include <stdexcept>

namespace k52
{
namespace dsp
{

std::vector< std::complex< double > > CircularConvolution::EvaluateConvolution(
        const std::vector< std::complex< double > > &first_sequence,
        const std::vector< std::complex< double > > &second_sequence)
{
    if(first_sequence.size() != second_sequence.size())
    {
        throw std::runtime_error("Can evaluate convolution only for sequences of the same size.");
    }

    size_t N = first_sequence.size();
    std::vector< std::complex< double > > result(N);

    for (int n = 0; n < N; ++n)
    {
        result[n] = 0;

        for (int m = 0; m < N; ++m)
        {
            result[n] += first_sequence[m] * ( m <= n ? second_sequence[n - m] : second_sequence[N + n - m] );
        }
    }

    return result;
}

} // namespace dsp
} // namespace k52