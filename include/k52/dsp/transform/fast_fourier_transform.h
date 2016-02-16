#ifndef FAST_FOURIER_TRANSFORM_H
#define FAST_FOURIER_TRANSFORM_H

#include <k52/dsp/transform/i_fourier_transform.h>

namespace k52
{
namespace dsp
{

class FastFourierTransform : public IFourierTransform
{

public:
    FastFourierTransform(size_t sequence_size);
    ~FastFourierTransform();

    virtual std::vector< std::complex< double > > Transform(
            const std::vector< std::complex< double > > &sequence) const;

private:
    class FastFourierTransformImpl;
    FastFourierTransformImpl* fast_fourier_transform_impl_;
};

} // namespace dsp
} // namespace k52

#endif //FAST_FOURIER_TRANSFORM_H
