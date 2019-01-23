#pragma once

#ifndef SIGNAL_GENERATOR_SIGNALGENERATORCOMPONENT_HPP
#define SIGNAL_GENERATOR_SIGNALGENERATORCOMPONENT_HPP


#include "../../src/internal/SignalGenerator.hpp"


#include <signal_generator_components_export.h>

#include <hyro/msgs/common/Basic.h>
#include <hyro/msgs/Signal.hpp>
#include <hyro/core/Component.h>


namespace hyro
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT SignalGeneratorComponent : public hyro::Component
{
public:

  SignalGeneratorComponent(URI uri);

  // Other public constructors here

  virtual  ~SignalGeneratorComponent () override = default;

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
bool   setFrequency(double frequency);
double getFrequency();
bool   setCosine(bool cosine);
bool   getCosine();


// Other variables here
SignalGenerator m_signal_generator;
double          m_amplitude;
double          m_frequency;
bool            m_cosine;

static std::shared_ptr<hyro::HyroLogger>      s_logger;
std::shared_ptr<hyro::ChannelOutput<Signal>>  m_output;

};

} // namespace hyro

#endif // SIGNAL_GENERATOR_SIGNALGENERATORCOMPONENT_HPP