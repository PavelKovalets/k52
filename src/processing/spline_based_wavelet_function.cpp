#include <k52/processing/spline_based_wavelet_function.h>

// standart headers
#include <algorithm>
#include <stdint.h>
#include <vector>

namespace k52
{
namespace processing
{

void SplineBased::Init(const std::vector<double> &real, const std::vector<double> &imaj)
{
    std::vector<double> points(real.size() + 2);
    double delta = 8. / real.size();
    for (size_t i = 0; i < real.size(); ++i)
    {
        points[i+1] = -4 + delta * i;
    }

    std::vector<double> values(points.size());
    std::copy(real.begin(), real.end(), values.begin()+1);

    points[0] = points[1] - (points[2] - points[1]);
    values[0] = 0;
    int size(points.size());
    points[size - 1] = points[size - 2] - (points[size - 3] - points[size - 2]);
    values[size - 1] = 0;

    spline_->Initialize(points, values);
}

double SplineBased::real(double x, int)
{
    // from -4 to +4 is effective part of wavelet, all other should be zero
    if((x >= -4) && (x <= 4))
    {
        return spline_->Value(x);
    }
    return 0;
}

double SplineBased::imag(double x, int)
{
    // from -4 to +4 is effective part of wavelet, all other should be zero
    return 0;
}

void SplineBased::spline(Spline::shared_ptr spline)
{
    spline_ = spline;
}

} // namespace processing
} // namespace k52
