#ifndef K52_DSP_SPLINE_BASED_WAVELET_FUNCTION_HEADER
#define K52_DSP_SPLINE_BASED_WAVELET_FUNCTION_HEADER

#include <algorithm>
#include <stdint.h>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <k52/dsp/transform/wavelet/i_wavelet.h>
#include "spline.h"

namespace k52
{
namespace dsp
{

/**
  @todo: comment it
*/
class SplineBased : public IWavelet
{
public:
    typedef boost::shared_ptr<SplineBased> shared_ptr;

    virtual void Init(const std::vector<double> &real, const std::vector<double> &imaj);

    virtual std::complex<double> GetValue(double t);

    virtual double real(double x);

protected:
    SplineBased() {}
    // If any custom spline based wavelet function is being impementing custom spline should be set up
    // with this function
    void spline(Spline::shared_ptr spline);

private:
    Spline::shared_ptr spline_;
};

#if 0
class CubicWavelet : public SplineBased
{
protected:
    virtual void initSpline(const alglib::real_1d_array &spline_points_x, const alglib::real_1d_array &spline_points_y)
    try
    {
        alglib::spline1dbuildcubic(spline_points_x, spline_points_y, SplineBased::interpolant_);
    }
    catch(const alglib::ap_error& error)
    {
        std::cerr << "alglib error: " << error.msg << std::endl;
    }
    catch(...)
    {
        std::cerr << __FUNCTION__ << ", an error :" << std::endl;
        throw;
    }
};
#endif

} // namespace dsp
} // namespace k52

#endif // K52_DSP_SPLINE_BASED_WAVELET_FUNCTION_HEADER
