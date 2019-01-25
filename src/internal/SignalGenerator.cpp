/**
* @file SignalGenerator.cpp
* @brief This header file contains the implementation functions of the SignalGenerators class.
*
* @author Murilo Mendonça Venâncio
* 
* @date 24/01/2019
*/

#include "SignalGenerator.hpp"


SignalGenerator::~SignalGenerator()
{

}

bool SignalGenerator::setAmplitude(const double amp)
{
  this->m_amp    = amp;
  return true;
}
double SignalGenerator::getAmplitude()
{
  return this->m_amp;
}

bool SignalGenerator::setFrequency(const double freq)
{
  this->m_freq    = freq;
  return true;
}
double SignalGenerator::getFrequency()
{
  return this->m_freq;
}

bool SignalGenerator::setCosine(const bool cosine)
{
  this->m_cosine    = cosine;
  return true;
}
bool SignalGenerator::getCosine()
{
  return this->m_cosine;
}

double SignalGenerator::getSignalValue()
{
  /* Basically this function updates the sinusoidal wave by a m_freq*0.360 each time.
     The 0.360 converts m_freq to hertz, considering an update rate of 1 ms. */
  double rad = m_deg / 180.0 * M_PI;
  m_deg += m_freq*0.360;
  return m_cosine?(m_amp * cos(rad)):(m_amp * sin(rad));
}

