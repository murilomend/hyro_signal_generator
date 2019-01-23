#ifndef SIGNALGENERATOR_HPP
#define SIGNALGENERATOR_HPP

#include <math.h>
#include <iostream>
class SignalGenerator
{
public:
  SignalGenerator();
  SignalGenerator(const double &amp,const double &freq,const bool &cosine);
  ~SignalGenerator();

  double getSignalValue();
  bool  setSignalGenerator(const double &amp,const double &freq,const bool &cosine);
private:
  double  m_deg;
  double  m_step;
  double  m_amp;
  double  m_freq;
  bool    m_cosine;
};

#endif // SIGNALGENERATOR_HPP