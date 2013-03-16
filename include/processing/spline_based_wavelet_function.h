#ifndef SPLINE_BASED_HEADER
#define SPLINE_BASED_HEADER

#include <algorithm>
#include <stdint.h>
#include <vector>
#include <interpolation.h>

#include <processing/iwavelet_function.h>

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

    virtual void init(const std::vector<double> &real, const std::vector<double> &imaj)
    {
        // regular spline from -4 upto 4
        uint32_t points_count = real.size() + 2;
        alglib::real_1d_array spline_points_x;
        alglib::real_1d_array spline_points_y;
        spline_points_x.setlength(points_count);
        spline_points_y.setlength(points_count);

        // create spline
        double delta = 8. / real.size();
        for (int i = 0; i < real.size(); ++i)
        {
            spline_points_x[i+1] = -4 + delta * i;
            spline_points_y[i+1] = real[i];
        }

        spline_points_x[0] = spline_points_x[1] - (spline_points_x[2] - spline_points_x[1]);
        spline_points_y[0] = 0;
        spline_points_x[points_count - 1] = spline_points_x[points_count - 2] -
            (spline_points_x[points_count - 3] - spline_points_x[points_count - 2]);
        spline_points_y[points_count - 1] = 0;

        initSpline(spline_points_x, spline_points_y);
    }

    virtual double real(double x, int index)
    {
        // from -4 to +4 is effective part of wavelete, all other should be zero

        if((x >= -4) && (x <= 4))
        {
            return alglib::spline1dcalc(interpolant_, x);
        }
        return 0;
    }

    virtual double imag(double x, int index)
    {
        // from -4 to +4 is effective part of wavelete, all other should be zero
        return 0;
    }

protected:
    virtual void initSpline(const alglib::real_1d_array &spline_points_x,
                            const alglib::real_1d_array &spline_points_y) = 0;

    alglib::spline1dinterpolant interpolant_; // take it easy

private:
    int length_;
};

class AkimaWavelet : public SplineBased
{
protected:
    virtual void initSpline(const alglib::real_1d_array &spline_points_x, const alglib::real_1d_array &spline_points_y)
    try
    {
        alglib::spline1dbuildakima(spline_points_x, spline_points_y, SplineBased::interpolant_);
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

} // namespace processing
} // namespace k52

#endif // SPLINE_BASED_HEADER
