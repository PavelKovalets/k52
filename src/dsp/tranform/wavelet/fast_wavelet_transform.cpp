#include <k52/dsp/transform/wavelet/fast_wavelet_transform.h>
#include <stdexcept>

using ::std::vector;
using ::std::conj;
using ::std::complex;
using ::std::invalid_argument;
using ::k52::dsp::FastWaveletTransform;

namespace k52
{
namespace dsp
{

FastWaveletTransform::FastWaveletTransform(double min_scale, double max_scale, size_t scale_count)
        : min_scale_(min_scale), max_scale_(max_scale), scale_count_(scale_count)
{
    if(min_scale <= 0)
    {
        throw invalid_argument("min_scale <= 0");
    }

    if(max_scale <= 0)
    {
        throw invalid_argument("max_scale <= 0");
    }

    if(scale_count <= 0)
    {
        throw invalid_argument("scale_count <= 0");
    }

    i_circular_convolution_ = FourierBasedCircularConvolution::shared_ptr(
            new FourierBasedCircularConvolution(
                    IFourierTransform::shared_ptr(
                            //TODO use FFT
                            new FourierTransform()
                    )
            )
    );
}

vector< vector< complex< double > > > FastWaveletTransform::Transform(
        const vector< std::complex< double > > &sequence,
        IWavelet::shared_ptr wavelet) const
{
    size_t N = sequence.size();

    vector< double > scales = GetScales();

    vector< vector< complex< double > > > result(scales.size());

    for (int i = 0; i < scales.size(); ++i)
    {
        result[i] = i_circular_convolution_->EvaluateConvolution(
                sequence, GetWaveletSamplesForConvolution(wavelet, scales[i], N)
        );
    }

    return result;
}

vector< double > FastWaveletTransform::GetScales() const
{
    //TODO precalculate?
    double scale_step = (max_scale_ - min_scale_) / scale_count_;

    vector< double > scales(scale_count_);
    for (int i = 0; i < scale_count_; ++i)
    {
        scales[i] = min_scale_ + scale_step * i;
    }
    return scales;
}

std::vector< std::complex< double > > FastWaveletTransform::GetWaveletSamplesForConvolution(
        IWavelet::shared_ptr wavelet, double scale, size_t N) const
{
    //TODO precalculate?
    vector< complex< double > > wavelet_samples(N);
    for (size_t n = 0; n < N; ++n)
    {
        //TODO !!! check if we need this cyclic shift here - to include all wavelet, not its right half?
        double t = (n < N/2) ? n : (n - N);
        wavelet_samples[n] = conj( GetScaledWaveletValue(wavelet, scale, -t) );
    }
    return wavelet_samples;
}

complex< double > FastWaveletTransform::GetScaledWaveletValue(
        IWavelet::shared_ptr wavelet, double scale, double t) const
{
    return wavelet->get_value(t/scale) / sqrt(scale);
}

} // namespace dsp
} // namespace k52
