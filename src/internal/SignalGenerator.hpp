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

#define NUM_TO_HERTZ  0.360

class SignalGenerator
{
public:
  /**
   * @brief Construct a new SignalGenerator object
   * 
   */
  SignalGenerator()  
    : m_amp(1)
    , m_freq(1)
    , m_cosine(false)
    , m_deg(0) {}

  /**
   * @brief Construct a new SignalGenerator object
   * 
   * @param amp  it sets the amaximum peak value of the generated signal
   * @param freq it sets the frrequency in Hertz (considering an update rate of 1 ms)
   * @param cosine  if true, the signal will be generated by a cosine function, and sine otherwise
   */
  SignalGenerator(const double amp,const double freq,const bool cosine)
    : m_amp(amp)
    , m_freq(freq)
    , m_cosine(cosine)
    , m_deg(0) {}

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
  * Methods related to Set and Get the private parameters
  */ 
  ///@{
  bool    setAmplitude(const double amp);
  double  getAmplitude();
  bool    setFrequency(const double freq);
  double  getFrequency();
  bool    setCosine(const bool cosine);
  bool    getCosine();
  ///@}

private:
  double  m_amp;
  double  m_freq;
  bool    m_cosine;
  double  m_deg;
};

#endif // SIGNALGENERATOR_HPP