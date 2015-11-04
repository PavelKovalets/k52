#include <k52/dsp/transform/wavelet/fast_wavelet_transform.h>
#include <stdexcept>

using ::std::vector;
using ::std::conj;
using ::std::complex;
using ::std::invalid_argument;
using ::k52::dsp::FastWaveletTransform;
using ::k52::dsp::IScale;

namespace k52
{
namespace dsp
{

FastWaveletTransform::FastWaveletTransform(IScale::shared_ptr scale)
        : i_scale_(scale)
{
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
    vector< double > scales = i_scale_->GetScales();

    vector< vector< complex< double > > > result(scales.size());

    for (size_t i = 0; i < scales.size(); ++i)
    {
        result[i] = TransformOneScale(sequence, wavelet, scales[i]);
    }

    return result;
}

std::vector< std::complex< double > > FastWaveletTransform::TransformOneScale(
        const std::vector< std::complex< double > > &sequence, IWavelet::shared_ptr wavelet, double scale) const
{
    if(scale <= 0)
    {
        throw invalid_argument("scale <= 0");
    }

    return i_circular_convolution_->EvaluateConvolution(
            sequence, GetWaveletSamplesForConvolution(wavelet, scale, sequence.size())
    );
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
    return wavelet->GetValue(t / scale) / sqrt(scale);
}

} // namespace dsp
} // namespace k52
