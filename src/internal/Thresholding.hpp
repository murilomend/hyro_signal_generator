/**
* @file Thresholding.hpp
* @brief This header file contains the basic definitions for the Thresholding class.
* It basically takes a signal as input and simulates a digital converter, in which outputs
* a square wave depending on the set of parameters.
*
* @author Murilo Mendonça Venâncio
* 
* @date 24/01/2019
*/
#ifndef THRESHOLDING_HPP
#define THRESHOLDING_HPP

#include <math.h>

class Thresholding
{
public:

  /**
   * @brief Construct a new Thresholding object
   * 
   */
  Thresholding()
    : m_amp(1)
    , m_thresh(0) {}

  /**
   * @brief Construct a new Thresholding object
   * 
   * @param amp 
   * @param thresh 
   */
  Thresholding(const double amp,const double thresh)
    : m_amp(amp)
    , m_thresh(thresh) {}
    
  /**
   * @brief Destroy the Thresholding object
   * 
   */
  ~Thresholding();

  /**
   * @brief Get a signal as input and calculates its threshold
   * 
   * @param signal  signal to be thresholded
   * @return double  signal thresholded
   */
  double getSignalThreshold(const double signal);

  /**
  * Methods related to Set and Get the private parameters
  */ 
  ///@{
  bool   setThreshold(const double thresh);
  double getThreshold();
  bool   setAmplitude(const double amp);
  double getAmplitude();
  ///@}

private:
  double m_amp;
  double m_thresh;   
};

#endif // THRESHOLDING_HPP