#ifndef HAAR_WAVELET_FUNCTION_HEADER
#define HAAR_WAVELET_FUNCTION_HEADER

#include <boost/shared_ptr.hpp>
#include <processing/iwavelet_function.h>

namespace k52
{
namespace processing
{

/*
    The Haar base wavelet function
    http://en.wikipedia.org/wiki/Haar_wavelet
*/

class HaarWaveletFunction : public IWaveletFunction
{
public:
    typedef boost::shared_ptr<HaarWaveletFunction> shared_ptr;

    virtual double real(double x, int index = 0);
    virtual double imag(double x, int index = 0);
};

} // namespace processing
} // namespace k52

#endif // HAAR_WAVELET_FUNCTION_HEADER
