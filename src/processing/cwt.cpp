#include <processing/cwt.h>

namespace k52
{
namespace processing
{

std::vector<std::vector<double> > ContiniousWaveletTransformation(const std::vector<double>& source_data,
                                                                  Wavelet::shared_ptr wavelet, int step)
{
    std::vector<std::vector<double> > wavelet_result;
    wavelet_result.reserve(source_data.size());

    std::vector<double> data(source_data.size() + wavelet->max_lenght());
    std::fill(data.begin(), data.end(), 0);
    std::copy(source_data.begin(), source_data.end(), data.begin() + wavelet->max_lenght() / 2);

    for(size_t i = 0, i_end = source_data.size(); i < i_end; i += step)
    {
        wavelet_result.push_back(wavelet->transform<double>(data.begin() + i));
    }

    return wavelet_result;
}

} // namespace processing
} // namespace k52
