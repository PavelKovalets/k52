#ifndef K52_DSP_SPLINE_H
#define K52_DSP_SPLINE_H

namespace k52
{
namespace dsp
{

class Spline
{
public:
    typedef boost::shared_ptr<Spline> shared_ptr;

    virtual void Initialize(const std::vector<double> &points, const std::vector<double> &values) = 0;
    virtual double Value(double x) = 0;
};

} // namespace dsp
} // namespace k52

#endif // K52_DSP_SPLINE_H
