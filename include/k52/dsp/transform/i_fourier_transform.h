#ifndef K52_IFOURIER_TRANSFORM_H
#define K52_IFOURIER_TRANSFORM_H

#include <boost/smart_ptr/shared_ptr.hpp>

#include <complex>
#include <vector>


namespace k52
{
namespace dsp
{

class IFourierTransform
{
public:
    typedef boost::shared_ptr<IFourierTransform> shared_ptr;

    virtual ~IFourierTransform() {};
    virtual std::vector< std::complex< double > > Transform(
            const std::vector< std::complex< double > >& sequence) const = 0;

};

} // namespace dsp
} // namespace k52

#endif //K52_IFOURIER_TRANSFORM_H
