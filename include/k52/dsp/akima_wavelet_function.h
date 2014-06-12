#ifndef K52_DSP_AKIMA_WAVELET_FUNCTION_H
#define K52_DSP_AKIMA_WAVELET_FUNCTION_H

#include <boost/shared_ptr.hpp>
#include <k52/dsp/spline_based_wavelet_function.h>

namespace k52
{
namespace dsp
{

class AkimaWavelet : public SplineBased
{
public:
    typedef boost::shared_ptr<AkimaWavelet> shared_ptr;

    static AkimaWavelet::shared_ptr CreateAkimaWavelet(const std::vector<double>& real,
                                                       const std::vector<double>& imaj);
protected:
    AkimaWavelet();
};

} // namespace dsp
} // namespace k52

#endif // K52_DSP_AKIMA_WAVELET_FUNCTION_H
