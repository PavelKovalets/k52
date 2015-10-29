#ifndef FAST_WAVELET_TRANSFORM_H
#define FAST_WAVELET_TRANSFORM_H

#include <k52/dsp/transform/wavelet/i_wavelet_transform.h>
#include <k52/dsp/transform/fourier_based_circular_convolution.h>
#include <k52/dsp/transform/fourier_transform.h>

namespace k52
{
namespace dsp
{

class FastWaveletTransform : public IWaveletTransform
{

public:
    FastWaveletTransform(double min_scale, double max_scale, size_t scale_count);

    virtual std::vector< std::vector< std::complex< double > > > Transform(
            const std::vector< std::complex< double > > &sequence,
            IWavelet::shared_ptr wavelet) const;

protected:
    std::vector< double > GetScales() const;

    std::vector< std::complex< double > > GetWaveletSamplesForConvolution(
            IWavelet::shared_ptr wavelet, double scale, size_t N) const;

    std::complex< double > GetScaledWaveletValue(
            IWavelet::shared_ptr wavelet, double scale, double t) const;

private:
    ICircularConvolution::shared_ptr i_circular_convolution_;
    double min_scale_;
    double max_scale_;
    size_t scale_count_;
};

} // namespace dsp
} // namespace k52


#endif //FAST_WAVELET_TRANSFORM_H
