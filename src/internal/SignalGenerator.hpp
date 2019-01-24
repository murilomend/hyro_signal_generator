/**
* @file SignalGenerator.hpp
* @brief This header file contains the basic definitions for the SignalGenerator class.
* It simulates a sinusoidal wave for a given set of parameters.
*
* @author Murilo Mendonça Venâncio
* 
* @date 24/01/2019
*/

#ifndef SIGNALGENERATOR_HPP
#define SIGNALGENERATOR_HPP

#include <math.h>
#include <iostream>
class SignalGenerator
{
public:
  /**
   * @brief Construct a new SignalGenerator object
   * 
   */
  SignalGenerator();

  /**
   * @brief Construct a new SignalGenerator object
   * 
   * @param amp  it sets the amaximum peak value of the generated signal
   * @param freq it sets the frrequency in Hertz (considering an update rate of 1 ms)
   * @param cosine  if true, the signal will be generated by a cosine function, and sine otherwise
   */
  SignalGenerator(const double &amp,const double &freq,const bool &cosine);

  /**
   * @brief Destroy the Signal Generator object
   * 
   */
  ~SignalGenerator();

  /**
   * @brief Updates the Signal Value object everytime is called
   * 
   * @return double 
   */
  double getSignalValue();

  /**
   * @brief Set the SignalGenerator object
   *  
   * @param amp    it sets the amaximum peak value of the generated signal
   * @param freq   it sets the frrequency in Hertz (considering an update rate of 1 ms)
   * @param cosine if true, the signal will be generated by a cosine function, and sine otherwise
   * @return true  
   * @return false 
   */
  bool  setSignalGenerator(const double &amp,const double &freq,const bool &cosine);
private:
  double  m_deg;
  double  m_step;
  double  m_amp;
  double  m_freq;
  bool    m_cosine;
};

#endif // SIGNALGENERATOR_HPP