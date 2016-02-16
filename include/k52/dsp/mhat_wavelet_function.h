#ifndef K52_DSP_MHAT_WAVELET_FUNCTION_H
#define K52_DSP_MHAT_WAVELET_FUNCTION_H

#include <boost/shared_ptr.hpp>
#include <k52/dsp/transform/wavelet/i_wavelet.h>

/*
    The Mexican hat (MHAT) base function
    http://en.wikipedia.org/wiki/Mexican_hat_wavelet
*/

namespace k52
{
namespace dsp
{

class MhatWaveletFunction : public IWavelet
{
public:
    typedef boost::shared_ptr<MhatWaveletFunction> shared_ptr;

    MhatWaveletFunction();
    virtual ~MhatWaveletFunction() {}

    virtual std::complex<double> GetValue(double t);

    virtual double real(double value);

private:
    double k_;
};

} // namespace dsp
} // namespace k52

#endif // K52_DSP_MHAT_WAVELET_FUNCTION_H
