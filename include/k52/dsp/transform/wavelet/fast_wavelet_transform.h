#ifndef FAST_WAVELET_TRANSFORM_H
#define FAST_WAVELET_TRANSFORM_H

#include <k52/dsp/transform/wavelet/i_scale.h>
#include <k52/dsp/transform/wavelet/i_wavelet_transform.h>
#include <k52/dsp/transform/fourier_based_circular_convolution.h>
#include <k52/dsp/transform/i_fourier_transform.h>

namespace k52
{
namespace dsp
{

/**
@class FastWaveletTransform
Implementation of wavelet transform described in
"A Wavelet Tour of Signal Processing"
S. Mallat Chapter 4.3.3  Discrete Wavelets
*/
class FastWaveletTransform : public IWaveletTransform
{

public:
    FastWaveletTransform(
            k52::dsp::IScale::shared_ptr scale,
            size_t sequence_size
    );

    virtual std::vector< std::vector< std::complex< double > > > Transform(
            const std::vector< std::complex< double > > &sequence,
            IWavelet::shared_ptr wavelet) const;

    virtual std::vector< std::complex< double > > TransformOneScale(
            const std::vector< std::complex< double > > &sequence,
            IWavelet::shared_ptr wavelet,
            double scale
    ) const;

protected:
    std::vector< std::complex< double > > GetWaveletSamplesForConvolution(
            IWavelet::shared_ptr wavelet, double scale, size_t N) const;

    std::complex< double > GetScaledWaveletValue(
            IWavelet::shared_ptr wavelet, double scale, double t) const;

private:
    ICircularConvolution::shared_ptr i_circular_convolution_;
    k52::dsp::IScale::shared_ptr i_scale_;
};

} // namespace dsp
} // namespace k52


#endif //FAST_WAVELET_TRANSFORM_H
