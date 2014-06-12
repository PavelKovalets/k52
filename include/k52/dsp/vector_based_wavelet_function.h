#ifndef VECTORBASED_H_INCLUDED
#define VECTORBASED_H_INCLUDED

#include <vector>
#include <k52/processing/wavelet_function.h>

/**
  VectorBased - the wavelet that stores base function in std::vector
*/

namespace k52
{
namespace processing
{

class VectorBased : public WaveletFunction
{
  public :
    VectorBased(const std::vector<double> &real, const std::vector<double> &imaj)
               : m_real(real), m_imaj(imaj)
    {
    }

    virtual double real(double x, int index)
    {
      // from -4 to +4 is effective part of wavelet, all other shoud be zero
      double k = (double)m_real.size() / 8.;
      int i_min = ((x+4.) * k) / 1;
      double i_delta = ((x+4.) * k) - i_min;

      if((i_min >= 0) && (i_min < (int(m_real.size())-1)))
      {
        double v_delta = m_real.at(i_min + 1) - m_real.at(i_min);
        return m_real.at(i_min) + i_delta * v_delta;
      };

      return 0;
    };

    virtual double imag(double x, int index)
    {
      // from -4 to +4 is effective part of wavelete, all other shoud be zero
      double k = (double)m_imaj.size() / 8.;
      int i_min = ((x+4.) * k) / 1;
      double i_delta = ((x+4.) * k) - i_min;

      if(i_min >= 0 && i_min < int(m_imaj.size())-1)
      {
        double v_delta = m_imaj.at(i_min + 1) - m_imaj.at(i_min);
        return m_imaj.at(i_min) + i_delta * v_delta;
      };

      return 0;
    };

  private :
    int m_length;
    std::vector<double> m_real;
    std::vector<double> m_imaj;
};

} // namespace processing
} // namespace k52

#endif // VECTORBASED_H_INCLUDED
