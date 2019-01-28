/**
* @file Thresholding.cpp
* @brief This header file contains the implementation functions of the Thresholding class.
*
* @author Murilo Mendonça Venâncio
* 
* @date 24/01/2019
*/

#include "Thresholding.hpp"

Thresholding::~Thresholding()
{
}
bool Thresholding::setThreshold(const double thresh)
{
  m_thresh = thresh;
  return true;
}

double Thresholding::getThreshold()
{
  return m_thresh;
}
bool Thresholding::setAmplitude(const double amp)
{
  m_amp = amp;
  return true;
}
double Thresholding::getAmplitude()
{
  return m_amp;
}
double Thresholding::getSignalThreshold(const double signal)
{
  return signal > m_thresh ? m_amp : 0;
}