#include <k52/dsp/transform/fourier_based_circular_convolution.h>

#include <stdexcept>

k52::dsp::FourierBasedCircularConvolution::FourierBasedCircularConvolution(
            k52::dsp::IFourierTransform::shared_ptr fourier_transform) :
        fourier_transform_(fourier_transform),
        inverse_fourier_transform_(fourier_transform)
{
}

std::vector< std::complex< double > > k52::dsp::FourierBasedCircularConvolution::EvaluateConvolution(
        const std::vector< std::complex< double > > &first_sequence,
        const std::vector< std::complex< double > > &second_sequence) const
{
    if(first_sequence.size() != second_sequence.size())
    {
        throw std::runtime_error("Can evaluate convolution only for sequences of the same size.");
    }

    size_t N = first_sequence.size();

    std::vector< std::complex< double > > first_sequence_transform = fourier_transform_->Transform(first_sequence);
    std::vector< std::complex< double > > second_sequence_transform = fourier_transform_->Transform(second_sequence);

    std::vector< std::complex< double > > multiplication_transform(N);

    for (std::size_t k = 0; k < N; ++k)
    {
        multiplication_transform[k] = first_sequence_transform[k] * second_sequence_transform[k];
    }

    return inverse_fourier_transform_.Transform(multiplication_transform);
}
