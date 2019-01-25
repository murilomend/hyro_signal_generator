/**
* @file DigitalConverterComponent.hpp
* @brief This header file contains the basic definitions for the DigitalConverterComponent class.
* It creates a Hyro component to be used as an virtual threshold function for a given signal
*
* @author Murilo Mendonça Venâncio
* 
* @date 24/01/2019
*/
#pragma once
#ifndef SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_H
#define SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_H
/* Main includes */
#include <signal_generator_components_export.h>
#include "../../src/internal/Thresholding.hpp"
#include <hyro/core/Component.h>
/* Messages includes */
#include <hyro/msgs/common/Basic.h>
#include <hyro/msgs/Signal.hpp>


namespace hyro
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT DigitalConverterComponent : public hyro::Component
{
public:
  using Component::Component;

  /**
   * @brief Destroy the DigitalConverterComponent object
   * 
   */
  virtual  ~DigitalConverterComponent () override = default;


  /**
   * @brief Methods related to the overall functionalities if the component
   * 
   * @param uri 
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
  bool   setThreshold(double thresh);
  double getThreshold();
  ///@}

  Thresholding  m_thresh;
  std::shared_ptr<hyro::ChannelInput<Signal>>  m_input;
  std::shared_ptr<hyro::ChannelOutput<float>>  m_output;


  /* Static Variables */ 
  static std::shared_ptr<hyro::HyroLogger>     s_logger;

};

} // namespace hyro

#endif // SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_H