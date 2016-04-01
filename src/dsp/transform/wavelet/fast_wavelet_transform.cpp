#include <k52/dsp/transform/wavelet/fast_wavelet_transform.h>
#include <k52/dsp/transform/fast_fourier_transform.h>
#include <boost/tuple/tuple_comparison.hpp>
#include <stdexcept>

using ::std::vector;
using ::std::conj;
using ::std::complex;
using ::std::invalid_argument;
using ::k52::dsp::FastWaveletTransform;
using ::k52::dsp::IScale;

//TODO in c++11 there is a default hash implementation for tuples,
// so this should be removed and k52::dsp::FastWaveletTransform::ScaledWaveletKey
// made private when k52 migrate to c++11
namespace boost
{
size_t hash_value(k52::dsp::FastWaveletTransform::ScaledWaveletKey const & t)
{
    std::size_t seed = 0;
    boost::hash_combine( seed, t.get<0>().get() );
    boost::hash_combine( seed, t.get<1>() );
    boost::hash_combine( seed, t.get<2>() );
    return seed;
}
}

namespace k52
{
namespace dsp
{

FastWaveletTransform::FastWaveletTransform(
        IScale::shared_ptr scale,
        size_t sequence_size,
        double cache_data_limit_in_megabytes
)
        : i_scale_(scale)
{
    i_circular_convolution_ = FourierBasedCircularConvolution::shared_ptr(
            new FourierBasedCircularConvolution(
                    IFourierTransform::shared_ptr(
                            new FastFourierTransform(sequence_size)
                    )
            )
    );

    cache_ = ScaledWaveletCache::Create(cache_data_limit_in_megabytes);
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
        //TODO this is a hack to allow filling of wavelet samples with N/2 shift - think of a better solution
        std::rotate(result[i].begin(), result[i].begin() + result[i].size() / 2, result[i].end());
    }

    return result;
}

std::vector< std::complex< double > > FastWaveletTransform::TransformOneScale(
        const std::vector< std::complex< double > > &sequence, IWavelet::shared_ptr wavelet, double scale) const
{
    if (scale <= 0)
    {
        throw invalid_argument("scale <= 0");
    }

    return i_circular_convolution_->EvaluateConvolution(sequence,
        GetWaveletSamplesForConvolution(wavelet, scale, sequence.size()));
}

std::vector< std::complex< double > > FastWaveletTransform::GetWaveletSamplesForConvolution(
        IWavelet::shared_ptr wavelet, double scale, size_t N) const
{
    ScaledWaveletKey cache_key = boost::make_tuple(wavelet, scale, N);

    if (cache_ && cache_->IsCached(cache_key))
    {
        return cache_->GetCachedValue(cache_key);
    }
    else
    {
        vector< complex< double > > wavelet_samples = CalculateWaveletSamplesForConvolution(wavelet, scale, N);
        if (cache_)
        {
            cache_->AddValue(cache_key, wavelet_samples);
        }
        return wavelet_samples;
    }
}

std::vector< std::complex< double > > FastWaveletTransform::CalculateWaveletSamplesForConvolution(
    IWavelet::shared_ptr wavelet, double scale, size_t N) const
{
    vector< complex< double > > wavelet_samples(N);
    for (size_t n = 0; n < N; ++n)
    {
        double t = n - double(N) / 2.;
        wavelet_samples[n] = conj(GetScaledWaveletValue(wavelet, scale, -t));
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
