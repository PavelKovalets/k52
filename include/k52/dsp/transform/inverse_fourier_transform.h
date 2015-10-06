#ifndef K52_INVERSE_FOURIER_TRANSFORM_H
#define K52_INVERSE_FOURIER_TRANSFORM_H

#include <k52/dsp/transform/i_fourier_transform.h>

namespace k52
{
namespace dsp
{

class InverseFourierTransform : public IFourierTransform
{
public:
    virtual std::vector< std::complex< double > > Transform(const std::vector< std::complex< double>> &sequence);
};


} // namespace dsp
} // namespace k52

#endif //K52_INVERSE_FOURIER_TRANSFORM_H
