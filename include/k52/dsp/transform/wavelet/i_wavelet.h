#ifndef I_WAVELET_H
#define I_WAVELET_H

#include <complex>
#include <boost/shared_ptr.hpp>

#include <k52/common/disallow_copy_and_assign.h>

namespace k52
{
namespace dsp
{

class IWavelet
{
public :
    typedef boost::shared_ptr<IWavelet> shared_ptr;

    ///Default constructor should be explicitly defined if DISALLOW_COPY_AND_ASSIGN used
    IWavelet() {}
    virtual ~IWavelet() {}

    virtual std::complex< double > GetValue(double t) = 0;

private:
    DISALLOW_COPY_AND_ASSIGN(IWavelet);
};

} // namespace dsp
} // namespace k52

#endif //I_WAVELET_H
