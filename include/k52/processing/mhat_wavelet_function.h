#ifndef MHAT_WAVELET_FUNCTION_H
#define MHAT_WAVELET_FUNCTION_H

#include <processing/iwavelet_function.h>

/*
    The Mexican hat (MHAT) base function
    http://en.wikipedia.org/wiki/Mexican_hat_wavelet
*/

namespace k52
{
namespace processing
{

class MhatWaveletFunction : public IWaveletFunction
{
public:
    typedef boost::shared_ptr<MhatWaveletFunction> shared_ptr;

    MhatWaveletFunction();
    virtual ~MhatWaveletFunction() {}

    virtual double real(double value, int index = 0);
    virtual double imag(double value, int index = 0);

private:
    double k_;
};

} // namespace processing
} // namespace k52

#endif // MHAT_WAVELET_FUNCTION_H
