#ifndef K52_IFOURIER_TRANSFORM_H
#define K52_IFOURIER_TRANSFORM_H

#include <complex>
#include <vector>

namespace k52
{
namespace dsp
{


class IFourierTransform
{
public:

    virtual std::vector< std::complex< double > > Transform(const std::vector< std::complex< double > >&) = 0;

};

} // namespace dsp
} // namespace k52

#endif //K52_IFOURIER_TRANSFORM_H
