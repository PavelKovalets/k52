#ifndef SPLINE_BASED_HEADER
#define SPLINE_BASED_HEADER

#include <algorithm>
#include <stdint.h>
#include <vector>

#include <k52/processing/iwavelet_function.h>
#include "spline.h"

/**
  SplineBased - реализация вейвлета, базовая функция которого описывается при помощи сплайна
*/

#include <iostream>

namespace k52
{
namespace processing
{

class SplineBased : public IWaveletFunction
{
public:
    typedef boost::shared_ptr<SplineBased> shared_ptr;

    virtual void Init(const std::vector<double> &real, const std::vector<double> &imaj);
    virtual double real(double x, int index);
    virtual double imag(double x, int index);

protected:
    SplineBased() {}
    // If any custom spline based wavelet function is being impementing custom spline should be set up
    // with this function
    void spline(Spline::shared_ptr spline);

private:
    Spline::shared_ptr spline_;
};

/*
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
};*/

} // namespace processing
} // namespace k52

#endif // SPLINE_BASED_HEADER
