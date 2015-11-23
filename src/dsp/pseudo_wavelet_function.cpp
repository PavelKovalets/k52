#include <k52/dsp/pseudo_wavelet_function.h>
#include <cmath>

namespace 
{
double HammingModWindow(double i, double len);  // окно Хэмминга
}

namespace k52
{
namespace dsp
{

/// Pseudo implementation
PseudoWaveletFunction::PseudoWaveletFunction(int length) : length_(length)
{
}

double PseudoWaveletFunction::real(double x, int index)
{
    return HammingModWindow(index - length_ / 2, length_) * std::cos(5 * x) * 0.5 * 0.2;
}

double PseudoWaveletFunction::imag(double x, int index)
{
    return HammingModWindow(index - length_ / 2, length_) * std::sin(5 * x) * 0.5 * 0.2;
}

} // namespace dsp
} // namespace k52

namespace
{

// some usefull mathematical functions
double HammingModWindow(double i, double len)   // from -len/2 to len/2
{
    return 0.5 + 0.5 * std::cos(2.0 * M_PI * i / len);
}

}
