/**
* @file SignalGenerator.cpp
* @brief This header file contains the implementation functions of the SignalGenerators class.
*
* @author Murilo Mendonça Venâncio
* 
* @date 24/01/2019
*/

#include "SignalGenerator.hpp"


SignalGenerator::SignalGenerator()
{
  /** These are the default values for starting the class */
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
  /** The frequency value (freq) is used to set the variable m_step, which is multiplied by 0.360 to convert */
  /** freq to hertz, considering an update rate of 1 ms. */
  this->m_amp    = m_amp;
  this->m_freq   = freq;
  this->m_step   = freq*0.360;
  this->m_cosine = cosine;

  return true;
}



double SignalGenerator::getSignalValue()
{
  /** Basically this function updates the siusoidal wave by a m_step eachp time. */
  double rad = m_deg / 180.0 * M_PI;
  m_deg += m_step;
  return m_cosine?(m_amp * cos(rad)):(m_amp * sin(rad));
}

