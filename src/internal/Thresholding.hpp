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
  Thresholding();


  /**
   * @brief Construct a new Thresholding object
   * 
   * @param amplitude 
   * @param threshold 
   */
  Thresholding(const double &amplitude,const double &threshold);


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
  double getSignalThreshold(const double &signal);


  /**
   * @brief Set the Threshold object
   * 
   * @param amplitude   maximum wave peak
   * @param threshold   the value where the original signal starts to be thresholded
   * @return true       if they are acceptable parameters
   * @return false      otherwise
   */
  bool   setThreshold(const double &amplitude,const double &threshold);
private:
  double m_amplitude;
  double m_threshold;   

};

#endif // THRESHOLDING_HPP