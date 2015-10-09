#ifndef K52_INVERSE_FOURIER_TRANSFORM_H
#define K52_INVERSE_FOURIER_TRANSFORM_H

#include <complex>
#include <vector>
#include <k52/dsp/transform/i_fourier_transform.h>

namespace k52
{
namespace dsp
{

class InverseFourierTransform
{
public:
    InverseFourierTransform(k52::dsp::IFourierTransform::shared_ptr fourier_transform);

    virtual std::vector< std::complex< double > > Transform(const std::vector< std::complex< double>> &sequence) const;

private:
    k52::dsp::IFourierTransform::shared_ptr _fourier_transform;
};


} // namespace dsp
} // namespace k52

#endif //K52_INVERSE_FOURIER_TRANSFORM_H
