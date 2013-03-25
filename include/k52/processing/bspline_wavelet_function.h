#ifndef BSPLINE_WAVELET_FUNCTION_H
#define BSPLINE_WAVELET_FUNCTION_H

#include <processing/iwavelet_function.h>

/*
    The BSpline base function
    http://en.wikipedia.org/wiki/B-spline
*/

namespace k52
{
namespace processing
{

class BSplineWaveletFunction : public IWaveletFunction
{
public:
    typedef boost::shared_ptr<BSplineWaveletFunction> shared_ptr;

    virtual ~BSplineWaveletFunction() {}

    virtual double real(double value, int index = 0);
    virtual double imag(double value, int index = 0);
};

} // namespace processing
} // namespace k52

#endif // BSPLINE_WAVELET_FUNCTION_H
