#include <k52/dsp/transform/wavelet/linear_scale.h>
#include <stdexcept>

using ::std::vector;
using ::std::invalid_argument;

namespace k52
{
namespace dsp
{

LinearScale::LinearScale(double min_scale, double max_scale, size_t scale_count)
        : min_scale_(min_scale), max_scale_(max_scale), scale_count_(scale_count)
{
    if(min_scale <= 0)
    {
        throw invalid_argument("min_scale <= 0");
    }

    if(max_scale <= 0)
    {
        throw invalid_argument("max_scale <= 0");
    }

    if(max_scale <= 0)
    {
        throw invalid_argument("max_scale <= 0");
    }

    if(min_scale >= max_scale)
    {
        throw invalid_argument("min_scale >= max_scale");
    }

    if(scale_count < 2)
    {
        //At least 2 scales - min and max - must be used
        throw invalid_argument("scale_count < 2");
    }

    scales_ = CalculateScales();
}

vector< double > LinearScale::GetScales() const
{
    return scales_;
}

vector< double > LinearScale::CalculateScales()
{
    double scale_step = (max_scale_ - min_scale_) / (scale_count_ - 1);

    vector< double > scales(scale_count_);
    for (size_t i = 0; i < scale_count_; ++i)
    {
        scales[i] = min_scale_ + scale_step * i;
    }
    return scales;
}

} // namespace dsp
} // namespace k52
