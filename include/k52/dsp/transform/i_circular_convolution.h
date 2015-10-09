#ifndef K52_I_CIRCULAR_CONVOLUTION_H
#define K52_I_CIRCULAR_CONVOLUTION_H

#include <boost/smart_ptr/shared_ptr.hpp>

#include <complex>
#include <vector>

namespace k52
{
namespace dsp
{

class ICircularConvolution
{
public:
    typedef boost::shared_ptr<ICircularConvolution> shared_ptr;

    virtual ~ICircularConvolution() {};
    virtual std::vector< std::complex< double > > EvaluateConvolution(
            const std::vector< std::complex< double > >& first_sequence,
            const std::vector< std::complex< double > >& second_sequence
    ) const = 0;
};

} // namespace dsp
} // namespace k52

#endif //K52_I_CIRCULAR_CONVOLUTION_H
