#ifndef K52_DSP_BSPLINE_WAVELET_FUNCTION_H
#define K52_DSP_BSPLINE_WAVELET_FUNCTION_H

#include <k52/dsp/iwavelet_function.h>

/*
    The BSpline base function
    http://en.wikipedia.org/wiki/B-spline
*/

namespace k52
{
namespace dsp
{

class BSplineWaveletFunction : public IWaveletFunction
{
public:
    typedef boost::shared_ptr<BSplineWaveletFunction> shared_ptr;

    virtual ~BSplineWaveletFunction() {}

    // @todo: check implementation (what is index?)
    virtual double real(double value, int index);
    virtual double imag(double value, int index);
};

} // namespace dsp
} // namespace k52

#endif // K52_DSP_BSPLINE_WAVELET_FUNCTION_H
