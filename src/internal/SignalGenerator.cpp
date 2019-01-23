#include "SignalGenerator.hpp"


SignalGenerator::SignalGenerator()
{
  setSignalGenerator(1,1,true);
  m_deg  = 0.;
}

SignalGenerator::~SignalGenerator()
{

}

SignalGenerator::SignalGenerator(const double &amp,const double &freq,const bool &cosine)
{
  setSignalGenerator(amp,freq,cosine);
  m_deg  = 0.;
}

bool SignalGenerator::setSignalGenerator(const double &m_amp,const double &freq,const bool &cosine)
{
  this->m_amp    = m_amp;
  this->m_freq   = freq;
  this->m_step   = freq*0.360;
  this->m_cosine = cosine;

  return true;
}



double SignalGenerator::getSignalValue()
{
  double rad = m_deg / 180.0 * M_PI;
  m_deg += m_step;
  return m_cosine?(m_amp * cos(rad)):(m_amp * sin(rad));
}

