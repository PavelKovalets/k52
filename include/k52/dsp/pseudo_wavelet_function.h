#ifndef K52_DSP_PSEUDO_WAVELET_FUNCTION_HEADER
#define K52_DSP_PSEUDO_WAVELET_FUNCTION_HEADER

#include <k52/dsp/iwavelet_function.h>

namespace k52
{
namespace dsp
{

class PseudoWaveletFunction : public IWaveletFunction
{
public:
    typedef boost::shared_ptr<PseudoWaveletFunction> shared_ptr;

    PseudoWaveletFunction(int length);
    virtual ~PseudoWaveletFunction() {}

    virtual double real(double x, int index);
    virtual double imag(double x, int index);

private:
    int length_;
};

} // namespace dsp
} // namespace k52

#endif // K52_DSP_PSEUDO_WAVELET_FUNCTION_HEADER
