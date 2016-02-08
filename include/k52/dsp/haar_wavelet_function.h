#ifndef K52_DSP_HAAR_WAVELET_FUNCTION_HEADER
#define K52_DSP_HAAR_WAVELET_FUNCTION_HEADER

#include <boost/shared_ptr.hpp>
#include <k52/dsp/transform/wavelet/i_wavelet.h>

namespace k52
{
namespace dsp
{

/*
    The Haar base wavelet function
    http://en.wikipedia.org/wiki/Haar_wavelet
*/

class HaarWaveletFunction : public IWavelet
{
public:
    typedef boost::shared_ptr<HaarWaveletFunction> shared_ptr;

    virtual std::complex<double> GetValue(double t);

    virtual double real(double x);
    virtual double imag(double x);
};

} // namespace dsp
} // namespace k52

#endif // K52_DSP_HAAR_WAVELET_FUNCTION_HEADER
