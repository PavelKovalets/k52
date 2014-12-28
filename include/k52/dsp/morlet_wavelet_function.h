#ifndef K52_DSP_MORLET_WAVELET_FUNCTION_HEADER
#define K52_DSP_MORLET_WAVELET_FUNCTION_HEADER

#include <k52/dsp/iwavelet_function.h>

namespace k52
{
namespace dsp
{

class MorletWaveletFunction : public IWaveletFunction
{
public :
    typedef boost::shared_ptr<IWaveletFunction> shared_ptr;
    virtual ~MorletWaveletFunction() {}

    virtual double real(double x, int index = 0);
    virtual double imag(double x, int index = 0);
};

} // namespace dsp
} // namespace k52

#endif // K52_DSP_MORLET_WAVELET_FUNCTION_HEADER
