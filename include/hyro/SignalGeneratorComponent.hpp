/**
* @file SignalGeneratorComponent.hpp
* @brief This header file contains the basic definitions for the SignalGeneratorComponent class.
* It creates a Hyro component to be used as an virtual sinusoidal wave generator
*
* @author Murilo Mendonça Venâncio
* 
* @date 24/01/2019
*/


#pragma once

#ifndef SIGNAL_GENERATOR_SIGNALGENERATORCOMPONENT_HPP
#define SIGNAL_GENERATOR_SIGNALGENERATORCOMPONENT_HPP

/* Includes */
#include "../../src/internal/SignalGenerator.hpp"
#include <signal_generator_components_export.h>
#include <hyro/core/Component.h>
/* Messages includes */ 
#include <hyro/msgs/common/Basic.h>
#include <hyro/msgs/Signal.hpp>



namespace hyro
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT SignalGeneratorComponent : public hyro::Component
{
public:
  using Component::Component;
  /**
   * @brief Destroy the SignalGeneratorComponent object
   * 
   */
  virtual  ~SignalGeneratorComponent () override = default;

  /**
   * @brief Methods related to the overall functionalities if the component
   */
  ///@{
  virtual hyro::Result init (const hyro::ComponentConfiguration & config) override;
  virtual hyro::Result reset () override;
  virtual hyro::Result check () override;
  virtual hyro::Result start () override;
  virtual hyro::Result update () override;
  ///@}
  
private:
  /**
  * Methods related to Set and Get ot each registered dynamic property
  */ 
  ///@{
  bool   setAmplitude(double amp);
  double getAmplitude();
  bool   setFrequency(double freq);
  double getFrequency();
  bool   setCosine(bool cosine);
  bool   getCosine();
  ///@}
  
  SignalGenerator m_signal_generator;
  std::shared_ptr<hyro::ChannelOutput<Signal>>  m_output;
  
  /* Static Variables */ 
  static std::shared_ptr<hyro::HyroLogger>      s_logger;
};

} // namespace hyro

#endif // SIGNAL_GENERATOR_SIGNALGENERATORCOMPONENT_HPP