#ifndef MORLET_WAVELET_FUNCTION_HEADER
#define MORLET_WAVELET_FUNCTION_HEADER

#include <k52/processing/iwavelet_function.h>

namespace k52
{
namespace processing
{

class MorletWaveletFunction : public IWaveletFunction
{
public :
    typedef boost::shared_ptr<IWaveletFunction> shared_ptr;
    virtual ~MorletWaveletFunction() {}

    virtual double real(double x, int index = 0);
    virtual double imag(double x, int index = 0);
};

} // namespace processing
} // namespace k52

#endif // MORLET_WAVELET_FUNCTION_HEADER
