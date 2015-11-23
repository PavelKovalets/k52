#ifndef K52_DSP_WAVELET_HEADER
#define K52_DSP_WAVELET_HEADER

// Main header file for wavelet dsp

#include <boost/shared_ptr.hpp>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

#include <k52/common/disallow_copy_and_assign.h>
#include <k52/dsp/iwavelet_function.h>
#include <k52/dsp/bspline_wavelet_function.h>
#include <k52/dsp/haar_wavelet_function.h>
#include <k52/dsp/mhat_wavelet_function.h>
#include <k52/dsp/morlet_wavelet_function.h>
#include <k52/dsp/pseudo_wavelet_function.h>
#include <k52/dsp/spline_based_wavelet_function.h>

namespace k52
{
namespace dsp
{

class Wavelet
{
public:
    typedef boost::shared_ptr<Wavelet> shared_ptr;
    typedef enum {Log = 0, Linear} ScaleType;

    static Wavelet::shared_ptr BuildWavelet(IWaveletFunction::shared_ptr wavelet_function, int min_lenght,
                                            int max_lenght, int count, ScaleType type = Log);

    virtual ~Wavelet() {}

    inline void base_function(IWaveletFunction::shared_ptr function) { base_function_ = function; }
    inline IWaveletFunction::shared_ptr base_function() { return base_function_; }

    inline int  count()                    { return count_; }
    inline void count(int count)           { count_ = count; }
    inline void max_lenght(int max_lenght) { max_lenght_ = max_lenght; }
    inline int  max_lenght()               { return max_lenght_;}
    inline void min_lenght(int min_lenght) { min_lenght_ = min_lenght; }
    inline int  min_lenght()               { return min_lenght_; }

    virtual void createWavelet(ScaleType type = Log);

    template <typename T>
    std::vector<T> transform(typename std::vector<T>::const_iterator data_begin);

protected:
    // Protect this class from direct copying but allow inheritance for mocking
    Wavelet();
    DISALLOW_COPY_AND_ASSIGN(Wavelet);

    void createScale(ScaleType type);

private:
    IWaveletFunction::shared_ptr base_function_;
    int count_;
    int max_lenght_;
    int min_lenght_;

    std::vector<std::vector<double> > real_part_;
    std::vector<std::vector<double> > imaj_part_;
    std::vector<double> scale_;
};

template <typename T>
std::vector<T> Wavelet::transform(typename std::vector<T>::const_iterator data_begin)
{
    // check if wavelet ready
    if(real_part_.empty() || imaj_part_.empty() || scale_.empty())
    {
        std::cerr << "Try to call CreateWavelet before transformation" << std::endl;
        throw "Wavelet isn't ready";
    }

    std::vector<T> result(count_);

    T real_res = 0;
    T imaj_res = 0;
    for (int i = 0; i < count_; ++i)
    {
        real_res = inner_product(real_part_[i].begin(), real_part_[i].end(), data_begin, real_res);
        imaj_res = inner_product(imaj_part_[i].begin(), imaj_part_[i].end(), data_begin, imaj_res);

        result[i] = std::sqrt(real_res * real_res + imaj_res * imaj_res);
        real_res = 0;
        imaj_res = 0;
    }

    return result;
}

} // namespace dsp
} // namespace k52

#endif // K52_DSP_WAVELET_HEADER
