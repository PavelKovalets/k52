#ifndef K52_CIRCULAR_CONVOLUTION_H
#define K52_CIRCULAR_CONVOLUTION_H

#include <complex>
#include <vector>
#include <k52/dsp/transform/i_circular_convolution.h>

namespace k52
{
namespace dsp
{

class CircularConvolution : public ICircularConvolution
{
public:
    std::vector< std::complex< double > > EvaluateConvolution(
            const std::vector< std::complex< double > >& first_sequence,
            const std::vector< std::complex< double > >& second_sequence
    ) const;

};

} // namespace dsp
} // namespace k52


#endif //K52_CIRCULAR_CONVOLUTION_H
