#include <k52/dsp/akima_wavelet_function.h>
#include <stdexcept>

#include <k52/dsp/akima_spline.h>

namespace k52
{
namespace dsp
{

AkimaWavelet::shared_ptr AkimaWavelet::CreateAkimaWavelet(const std::vector<double>& real,
                                                          const std::vector<double>& imaj)
{
    AkimaWavelet::shared_ptr akima_wavelet(new AkimaWavelet);
    akima_wavelet->spline(k52::dsp::AkimaSpline::Create());
    akima_wavelet->Init(real, imaj);
    return akima_wavelet;
}

AkimaWavelet::AkimaWavelet()
{
}

} // namespace dsp
} // namespace k52
