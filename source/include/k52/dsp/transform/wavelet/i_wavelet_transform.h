#ifndef I_WAVELET_TRANSFORM_H
#define I_WAVELET_TRANSFORM_H

#include <vector>
#include <complex>
#include <boost/shared_ptr.hpp>

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/dsp/transform/wavelet/i_wavelet.h>

namespace k52
{
namespace dsp
{

class IWaveletTransform
{
public :
    typedef boost::shared_ptr<IWaveletTransform> shared_ptr;

    ///Default constructor should be explicitly defined if DISALLOW_COPY_AND_ASSIGN used
    IWaveletTransform() {}
    virtual ~IWaveletTransform() {}

    virtual std::vector< std::vector< std::complex< double > > > Transform(
            const std::vector< std::complex< double > >& sequence,
            IWavelet::shared_ptr wavelet
    ) const = 0;

private:
    DISALLOW_COPY_AND_ASSIGN(IWaveletTransform);
};

} // namespace dsp
} // namespace k52

#endif //I_WAVELET_TRANSFORM_H
