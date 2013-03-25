#ifndef PSEUDO_WAVELET_FUNCTION_HEADER
#define PSEUDO_WAVELET_FUNCTION_HEADER

#include <processing/iwavelet_function.h>

namespace k52
{
namespace processing
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

} // namespace processing
} // namespace k52

#endif // PSEUDO_WAVELET_FUNCTION_HEADER
