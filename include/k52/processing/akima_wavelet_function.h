#ifndef AKIMA_WAVELET_FUNCTION_H
#define AKIMA_WAVELET_FUNCTION_H

#include <boost/shared_ptr.hpp>
#include <k52/processing/spline_based_wavelet_function.h>

namespace k52
{
namespace processing
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

} // namespace processing
} // namespace k52

#endif // AKIMA_WAVELET_FUNCTION_H
