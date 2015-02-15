#include <k52/dsp/akima_wavelet_function.h>
#include <stdexcept>

#include <cmath>
#include <k52/dsp/akima_spline.h>

namespace
{
const size_t kMinimalPointsRequired = 5;
}

namespace k52
{
namespace dsp
{

AkimaSpline::shared_ptr AkimaSpline::Create()
{
    return AkimaSpline::shared_ptr(new AkimaSpline());
}

AkimaSpline::AkimaSpline()
{
}

void AkimaSpline::Initialize(const std::vector<double>& train_x, const std::vector<double>& train_y)
{
    // @todo - input data validation

    if ((train_x.size() < kMinimalPointsRequired) || (train_y.size() < kMinimalPointsRequired))
    {
        throw std::invalid_argument("Akima spline requeries at least 5 points for training");
    }

    if (train_x.size() != train_y.size())
    {
        throw std::invalid_argument("The training points are inconsistent");
    }

    train_x_ = train_x;
    train_y_ = train_y;

    ReestimatePolynomials();
}

double AkimaSpline::Value(double x)
{
    int i = ResolveInterval(x);
    double arg = x - train_x_[i];
    return coeffs_[i][0]
            + coeffs_[i][1] * arg
            + coeffs_[i][2] * powf(arg, 2)
            + coeffs_[i][3] * powf(arg, 3);
}

void AkimaSpline::ReestimatePolynomials()
{
    coeffs_ = std::vector<Polynomial>(train_x_.size() - 1);
    for (std::size_t i = 0; i < train_x_.size() - 1; ++i)
    {
        coeffs_[i] = Polynomial(4);
    }

    std::vector<double> s = CalculateSlopes(CalculateM());

    for (std::size_t i = 0; i < train_x_.size() - 1; ++i)
    {
        coeffs_[i][0] = train_y_[i];
        coeffs_[i][1] = s[i];
        coeffs_[i][2] = (3 * (train_y_[i+1] - train_y_[i]) / (train_x_[i+1] - train_x_[i])
                - 2 * s[i] - s[i+1]) / (train_x_[i+1] - train_x_[i]);
        coeffs_[i][3] = ( s[i+1] + s[i] - 2 * (train_y_[i+1] - train_y_[i]) / (train_x_[i+1] - train_x_[i]) )
                / powf(train_x_[i+1] - train_x_[i], 2);
    }
}

std::vector<double> AkimaSpline::CalculateM()
{
    std::vector<double> result(train_x_.size() + 3);

    for (std::size_t i = 0; i < train_x_.size() - 1; ++i)
    {
        result[i + 2] = (train_y_[i + 1] - train_y_[i]) / (train_x_[i+1] - train_x_[i]);
    }

    // special cases
    // @see p. 601
    result[0] = 3 * result[2] - 2 * result[3];
    result[1] = 2 * result[2] - result[3];

    std::size_t n = result.size() - 1;
    result[n - 1] = 2 * result[n - 2] - result[n - 3];
    result[n] = 3 * result[n - 2] - 2 * result[n - 3];

    return result;
}

std::vector<double> AkimaSpline::CalculateSlopes(const std::vector<double>& m)
{
    std::vector<double> slopes(train_x_.size());

    for (std::size_t i = 0; i < train_x_.size(); ++i)
    {
        double d = std::abs(m[2+i + 1] - m[2+i]) + std::abs(m[2+i - 1] - m[2+i - 2]);
        if (d == 0)
        {
            slopes[i] = 0.5 * (m[2+i - 1] + m[2+i]);
        }
        else
        {
            slopes[i] = (m[2+i - 1] * std::abs(m[2+i + 1] - m[2+i]) +
                         m[2+i] * std::abs(m[2+i - 1] - m[2+i - 2])) / d;
        }
    }

    return slopes;
}

std::size_t AkimaSpline::ResolveInterval(double x) const
{
    std::vector<double>::const_iterator upper_bound = std::upper_bound(train_x_.begin(), train_x_.end(), x);

    if (upper_bound == train_x_.begin())
    {
        throw std::out_of_range("X value is out of range in Akima spline");
    }

    if (upper_bound == train_x_.end())
    {
        std::vector<double>::const_iterator lower_bound = std::lower_bound(train_x_.begin(), train_x_.end(), x);
        if (lower_bound == train_x_.end())
        {
            throw std::out_of_range("X value is out of range in Akima spline");
        }
        else
        {
            return lower_bound - train_x_.begin() - 1;
        }
    }
    return upper_bound - train_x_.begin() - 1;
}

} // namespace dsp
} // namespace k52
