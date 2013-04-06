#ifndef K52_PROCESSING_SPLINE_H
#define K52_PROCESSING_SPLINE_H

namespace k52
{
namespace processing
{

class Spline
{
public:
    typedef boost::shared_ptr<Spline> shared_ptr;

    virtual void Initialize(const std::vector<double> &points, const std::vector<double> &values) = 0;
    virtual double Value(double x) = 0;
};

} // namespace processing
} // namespace k52

#endif // K52_PROCESSING_SPLINE_H
