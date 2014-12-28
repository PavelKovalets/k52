#include <k52/dsp/signal_based_wavelet_function.h>

#ifdef DONT_TRY_TO_COMPILE_IT_PLEASE

#include "../xmlParser/xmlParser.h"
#include <fstream>
#include <iostream>
#include <cstring>

SignalBased::SignalBased(string parameters) : m_length(4096)
{
    // default parameters
    string real_filename = "real.wav";
    int real_begin = 0;
    int real_end = -1;
    bool real_zshift = false;
    bool real_windowed = false;

    string imaj_filename = "imaj.wav";
    int imaj_begin = 0;
    int imaj_end = -1;
    bool imaj_zshift = false;
    bool imaj_windowed = false;

    // check if "parameters" is filename
    bool is_file = false;
    std::ifstream test_file(parameters.c_str());
    if(test_file.good())
    {
        is_file = true;
        test_file.close();
    };

    // try to parse xml
    XMLResults xError;
    XMLNode xP = is_file ? XMLNode::parseFile(parameters.c_str(), "parameters", &xError)
                         : XMLNode::parseString(parameters.c_str(), "parameters", &xError);

    if(xError.error == 0)
    {
        // there are no errors, parse general parameters
        if(xP.getAttribute("length"))
        {
            string length = string(xP.getAttribute("length"));
            if(!length.empty())
            {
                m_length = atof(length.c_str());
            }
        }

      // parse real part parameters
      XMLNode xReal = xP.getChildNode("real");
      if(!xReal.isEmpty())
      {
        if(xReal.getAttribute("file"))  real_filename = string(xReal.getAttribute("file"));
        if(xReal.getAttribute("begin")) real_begin = atoi(xReal.getAttribute("begin"));
        if(xReal.getAttribute("end"))   real_end = atoi(xReal.getAttribute("end"));
        if(xReal.getAttribute("z_shift"))
          real_zshift = string(xReal.getAttribute("z_shift")) == string("true");
        if(xReal.getAttribute("windowed"))
          real_windowed = string(xReal.getAttribute("windowed")) == string("true");
      };

      // parse imaj part parameters
      XMLNode xImaj = xP.getChildNode("imaginary");
      if(!xImaj.isEmpty())
      {
        if(xImaj.getAttribute("file"))  imaj_filename = string(xImaj.getAttribute("file"));
        if(xImaj.getAttribute("begin")) imaj_begin = atoi(xImaj.getAttribute("begin"));
        if(xImaj.getAttribute("end"))   imaj_end = atoi(xImaj.getAttribute("end"));
        if(xImaj.getAttribute("z_shift"))
          imaj_zshift = string(xImaj.getAttribute("z_shift")) == string("true");
        if(xImaj.getAttribute("windowed"))
          imaj_windowed = string(xImaj.getAttribute("windowed")) == string("true");
      };
    }
    else
    {
      std::cerr << "SignalBased : There is some error while parse input parameters. The default value will be used\n";
      std::cerr << "error : " << xError.error << " at " << xError.nLine << ":" << xError.nColumn << std::endl;
    }

    // create real wavelet part
    SoundFile real_file;
    real_file.open(real_filename);
    if(real_begin < 0) real_begin = 0;
    if(real_end <= real_begin) real_end = real_file.data().size();
    m_real.resize(real_end - real_begin);
    std::copy(real_file.data().begin() + real_begin, real_file.data().begin() + real_end, m_real.begin());

    //apply Hamming window for real part
    if (real_windowed)
    {
      for (unsigned int i = 0; i < m_real.size(); i++)
      {
        m_real.at(i) = HammingModWindow(i - m_real.size() / 2., m_real.size()) * m_real.at(i);
      }
    }

    if (real_zshift)
    {
      double real = 0;
      for(unsigned int i = 0; i < m_real.size(); i++) real += m_real[i];
      for(unsigned int i = 0; i < m_real.size(); i++) m_real[i] -= real / (double)m_real.size();
    }

    // create imaginary wavelet part
    SoundFile imaj_file;
    imaj_file.open(imaj_filename);
    if(imaj_begin < 0) imaj_begin = 0;
    if(imaj_end <= imaj_begin) imaj_end = imaj_file.data().size();
    m_imaj.resize(imaj_end - imaj_begin);
    std::copy(imaj_file.data().begin() + imaj_begin, imaj_file.data().begin() + imaj_end, m_imaj.begin());

    //apply Hamming window for imaj part
    if (imaj_windowed)
    {
      for(unsigned int i = 0; i < m_imaj.size(); i++)
      {
        m_imaj.at(i) = HammingModWindow(i - m_imaj.size() / 2., m_imaj.size()) * m_imaj.at(i);
      }
    }

    if (imaj_zshift)
    {
      double imaj = 0;
      for(unsigned int i = 0; i < m_imaj.size(); i++) imaj += m_imaj[i];
      for(unsigned int i = 0; i < m_imaj.size(); i++) m_imaj[i] -= imaj / (double)m_imaj.size();
    }
}

double SignalBased::real(double x, int)
{
  // from -4 to +4 is effective part of wavelete, all other shoud be zero
  double k = (double)m_real.size() / 8.;
  int i_min = ((x+4.) * k) / 1;
  double i_delta = ((x+4.) * k) - i_min;

  if((i_min >= 0) && (i_min < (int(m_real.size())-1)))
  {
    double v_delta = m_real.at(i_min + 1) - m_real.at(i_min);
    return m_real.at(i_min) + i_delta * v_delta;
  }
  return 0;
}

double SignalBased::imag(double x, int)
{
// from -4 to +4 is effective part of wavelete, all other shoud be zero
  double k = (double)m_imaj.size() / 8.;
  int i_min = ((x+4.) * k) / 1;
  double i_delta = ((x+4.) * k) - i_min;

  if(i_min >= 0 && i_min < int(m_imaj.size())-1)
  {
    double v_delta = m_imaj.at(i_min + 1) - m_imaj.at(i_min);
    return m_imaj.at(i_min) + i_delta * v_delta;
  }
  return 0;
}

#endif
