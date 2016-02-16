#ifndef LINEAR_SCALE_H
#define LINEAR_SCALE_H

#include <k52/dsp/transform/wavelet/i_scale.h>

namespace k52
{
namespace dsp
{

class LinearScale : public IScale
{
public:
    LinearScale(double min_scale, double max_scale, size_t scale_count);
    virtual std::vector< double > GetScales() const;

protected:
    std::vector< double > CalculateScales();

private:
    double min_scale_;
    double max_scale_;
    size_t scale_count_;

    std::vector< double > scales_;
};

} // namespace dsp
} // namespace k52


#endif //LINEAR_SCALE_H
