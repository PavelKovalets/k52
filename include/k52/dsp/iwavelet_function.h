#ifndef K52_DSP_IWAVELET_FUNCTION_H
#define K52_DSP_IWAVELET_FUNCTION_H

#include <boost/shared_ptr.hpp>

namespace k52
{
namespace dsp
{

class IWaveletFunction
{
  public :
    typedef boost::shared_ptr<IWaveletFunction> shared_ptr;
    virtual ~IWaveletFunction() {}

    virtual double real(double value, int index = 0) = 0; // index for bspline and pseudo
    virtual double imag(double value, int index = 0) = 0;
};

} // namespace dsp
} // namespace k52

#endif // K52_DSP_IWAVELET_FUNCTION_H
