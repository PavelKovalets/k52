#ifndef I_WAVELET_H
#define I_WAVELET_H

#include <complex>
#include <boost/shared_ptr.hpp>

namespace k52
{
namespace dsp
{

class IWavelet
{
public :
    typedef boost::shared_ptr<IWavelet> shared_ptr;
    virtual ~IWavelet() {}

    virtual std::complex< double > GetValue(double t) = 0;
};

} // namespace dsp
} // namespace k52

#endif //I_WAVELET_H
