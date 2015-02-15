#ifndef K52_DSP_AKIMA_SPLINE_H
#define K52_DSP_AKIMA_SPLINE_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <k52/dsp/spline.h>

namespace k52
{
namespace dsp
{

/**
 * @brief Perform Akima spline interpolation.
 * @see "The Computer Graphics Manual" by David Salomon pp 600-601 for more details about implementation
 *      Publisher: Springer Science & Business Media, 2011
 *      ISBN: 0857298860, 9780857298867
 */
class AkimaSpline : public Spline
{
public:
    typedef boost::shared_ptr<AkimaSpline> shared_ptr;

    /**
     * @return new akima spline interpolator
     */
    static AkimaSpline::shared_ptr Create();

    /**
     * @brief Initialize Akima spline based on provided point set
     * @param x - x-coordinate for each point
     * @param y - y-coordinate (function value) for each point
     */
    void Initialize(const std::vector<double>& x, const std::vector<double>& y);

    /**
     * @brief Calculate intepolated value for given x-coordinate
     * @param x - x-coordinate
     * @return interpolated function value
     */
    double Value(double x);

protected:
    AkimaSpline();

    std::vector<double> CalculateM();
    std::vector<double> CalculateSlopes(const std::vector<double>& m);

    void ReestimatePolynomials();
    std::size_t ResolveInterval(double x) const;

private:
    typedef std::vector<double> Polynomial;
    std::vector<Polynomial> coeffs_;

    std::vector<double> train_x_;
    std::vector<double> train_y_;
};

} // namespace dsp
} // namespace k52

#endif // K52_DSP_AKIMA_SPLINE_H
