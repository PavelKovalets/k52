#ifndef LOGARITHMIC_SCALE_H
#define LOGARITHMIC_SCALE_H

#include <k52/dsp/transform/wavelet/i_scale.h>

namespace k52
{
namespace dsp
{

class LogarithmicScale : public IScale
{
public:
    LogarithmicScale(int min_exponent, int max_exponent);
    virtual std::vector< double > GetScales() const;

protected:
    std::vector< double > CalculateScales(int min_exponent, int max_exponent);

private:
    std::vector< double > scales_;
};

} // namespace dsp
} // namespace k52

#endif //LOGARITHMIC_SCALE_H
