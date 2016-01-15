#ifndef K52_DSP_MORLET_WAVELET_FUNCTION_HEADER
#define K52_DSP_MORLET_WAVELET_FUNCTION_HEADER

#include <boost/shared_ptr.hpp>
#include <k52/dsp/transform/wavelet/i_wavelet.h>

namespace k52
{
namespace dsp
{

class MorletWaveletFunction : public IWavelet
{
public :
    typedef boost::shared_ptr<IWavelet> shared_ptr;
    virtual ~MorletWaveletFunction() {}

    virtual std::complex<double> GetValue(double t);
};

} // namespace dsp
} // namespace k52

#endif // K52_DSP_MORLET_WAVELET_FUNCTION_HEADER
