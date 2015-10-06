#ifndef K52_CIRCULAR_CONVOLUTION_H
#define K52_CIRCULAR_CONVOLUTION_H

#include <complex>
#include <vector>

namespace k52
{
namespace dsp
{

class CircularConvolution
{
public:
    std::vector< std::complex< double > > EvaluateConvolution(
            const std::vector< std::complex< double > >& first_sequence,
            const std::vector< std::complex< double > >& second_sequence
    );

};

} // namespace dsp
} // namespace k52


#endif //K52_CIRCULAR_CONVOLUTION_H
