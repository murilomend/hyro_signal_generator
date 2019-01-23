#pragma once

#ifndef SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_H
#define SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_H

#include <signal_generator_components_export.h>
#include "../../src/internal/Thresholding.hpp"
#include <hyro/core/Component.h>
#include <hyro/msgs/common/Basic.h>
#include <hyro/msgs/Signal.hpp>


namespace hyro
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT DigitalConverterComponent : public hyro::Component
{
public:

  DigitalConverterComponent(URI uri);

  // Other public constructors here

  virtual  ~DigitalConverterComponent () override = default;

  virtual hyro::Result init (const hyro::ComponentConfiguration & config) override;

  virtual hyro::Result reset () override;

  virtual hyro::Result check () override;

  virtual hyro::Result start () override;

  virtual hyro::Result update () override;

  // Other public methods here

private:

  // Other private methods here
  bool   setAmplitude(double amplitude);
  double getAmplitude();
  bool   setThreshold(double threshold);
  double getThreshold();
  // Other variables here
  Thresholding  m_thresh;
  double        m_amplitude;
  double        m_threshold;
  
  static std::shared_ptr<hyro::HyroLogger>    s_logger;
  std::shared_ptr<hyro::ChannelInput<Signal>>  m_input;
  std::shared_ptr<hyro::ChannelOutput<float>>  m_output;
  
};

} // namespace hyro

#endif // SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_H