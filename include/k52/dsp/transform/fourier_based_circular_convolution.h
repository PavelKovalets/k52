#ifndef K52_FOURIER_BASED_CIRCULAR_CONVOLUTION_H
#define K52_FOURIER_BASED_CIRCULAR_CONVOLUTION_H

#include <k52/dsp/transform/i_fourier_transform.h>
#include <k52/dsp/transform/i_circular_convolution.h>
#include <k52/dsp/transform/inverse_fourier_transform.h>

namespace k52
{
namespace dsp
{

class FourierBasedCircularConvolution : public ICircularConvolution
{
public:
    FourierBasedCircularConvolution(
                IFourierTransform::shared_ptr fourier_transform);

    std::vector< std::complex< double > > EvaluateConvolution(
            const std::vector< std::complex< double > >& first_sequence,
            const std::vector< std::complex< double > >& second_sequence
    ) const;

private:
    IFourierTransform::shared_ptr _fourier_transform;
    InverseFourierTransform _inverse_fourier_transform;
};

} // namespace dsp
} // namespace k52

#endif //K52_FOURIER_BASED_CIRCULAR_CONVOLUTION_H
