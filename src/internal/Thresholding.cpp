/**
* @file Thresholding.cpp
* @brief This header file contains the implementation functions of the Thresholding class.
*
* @author Murilo Mendonça Venâncio
* 
* @date 24/01/2019
*/

#include "Thresholding.hpp"

Thresholding::Thresholding()
{

}


Thresholding::Thresholding(const double &amplitude,const double &threshold)
{
  setThreshold(amplitude,threshold);
}


Thresholding::~Thresholding()
{
}

bool Thresholding::setThreshold(const double &amplitude,const double &threshold)
{
  this->m_amplitude = amplitude;
  this->m_threshold = threshold;
  return true;
}

double Thresholding::getSignalThreshold(const double &signal)
{
  return signal > m_threshold ? m_amplitude : 0;
}