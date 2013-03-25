#ifndef SIGNAL_BASED_HEADER
#define SIGNAL_BASED_HEADER

#include <k52/processing/iwavelet_function.h>

/** Класс SignalBased представляет базовую вейвлет функцию, построенную из сэмплов
    некоторого опорного сигнала.
*/

namespace k52
{
namespace processing
{

#ifdef DONT_TRY_TO_COMPILE_IT_PLEASE
class SignalBased : public WaveletFunction
{
  public :
    /** There are two cause of using parameters string:
      1. it should be xml file name
      2. it should contain xml string

      <parameters length="">
        <real file="string" begin="int" end="int" z_shift="bool"/>
        <imaginary file="string" begin="int" end="int" z_shift="bool"/>
      </parametes>
      where begin and end are in counts.

      if this string is empty or some parameters aren't set the next default parameters will be used:
      <parameters length="4096">
        <real file="real.wav" begin="0" end="size of real.wav" z_shift="false"/>
        <imaginary file="imaj.wav" begin="0" end="size of imaj.wav" z_shift="false"/>
      </parameters> */

    SignalBased(string parameters);
    virtual double real(double x, int index);
    virtual double imag(double x, int index);

  private :
    int m_length;
    SoundFile m_file;
    std::vector<double> m_real;
    std::vector<double> m_imaj;
};
#endif

} // namespace processing
} // namespace k52

#endif // SIGNAL_BASED_HEADER
