/**
* @file SignalGeneratorComponent.cpp
* @brief This file contains implementation for the definitions for the SignalGeneratorComponent functionalities.
*
* @author Murilo Mendonça Venâncio
* 
* @date 24/01/2019
*/

#include <hyro/SignalGeneratorComponent.hpp>

namespace hyro
{

std::shared_ptr<hyro::HyroLogger> SignalGeneratorComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("SignalGeneratorComponent");

hyro::Result SignalGeneratorComponent::init (const hyro::ComponentConfiguration & config)
{
  /* Dummy output for fixing the DynamicProperty bug for unit tests */
  std::shared_ptr<ChannelOutput<std::vector<int>>>
  m_dummy = this->registerOutput<std::vector<int>>("fix_dynamic"_uri, config);

  /* Setting an output channel for sending the generated signal */
  m_output = this->registerOutput<Signal>("signals"_uri, config);

  /* Setting the parameters from configuration */
  double amp,freq;
  bool   cosine;
  amp     = config.parameters.getParameter<double>("amplitude", 1.0);
  freq    = config.parameters.getParameter<double>("frequency", 1.0);
  cosine  = config.parameters.getParameter<bool>("cosine", false);
  m_signal_generator = SignalGenerator(amp,freq,cosine);

  /* Registering the Dynamic properties */
  registerDynamicProperty<double>(
    "amplitude",
    &SignalGeneratorComponent::setAmplitude,
    &SignalGeneratorComponent::getAmplitude,
    this);
  registerDynamicProperty<double>(
    "frequency",
    &SignalGeneratorComponent::setFrequency,
    &SignalGeneratorComponent::getFrequency,
    this);
  registerDynamicProperty<bool>(
    "cosine",
    &SignalGeneratorComponent::setCosine,
    &SignalGeneratorComponent::getCosine,
    this);

  return hyro::Result::RESULT_OK;
}


bool SignalGeneratorComponent::setAmplitude(double amp)
{ 
  return m_signal_generator.setAmplitude(amp);
}

double SignalGeneratorComponent::getAmplitude()
{
  return m_signal_generator.getAmplitude();
}

bool SignalGeneratorComponent::setFrequency(double freq)
{
  return m_signal_generator.setFrequency(freq);
}

double SignalGeneratorComponent::getFrequency()
{
  return m_signal_generator.getFrequency();
}


bool SignalGeneratorComponent::setCosine(bool cosine)
{
  return m_signal_generator.setCosine(cosine);
}

bool SignalGeneratorComponent::getCosine()
{
  return m_signal_generator.getCosine();
}


hyro::Result SignalGeneratorComponent::reset ()
{
  /* Reset all variables and objects like the object was just created */
  m_output.reset();
  return hyro::Result::RESULT_OK;
}

hyro::Result SignalGeneratorComponent::check ()
{
  /* Check everything is OK here */
  return hyro::Result::RESULT_OK;
}

hyro::Result SignalGeneratorComponent::start ()
{
  /* Start spinners and drivers (if any) here */
  return hyro::Result::RESULT_OK;
}

hyro::Result SignalGeneratorComponent::update()
{
  std::chrono::seconds secs = std::chrono::duration_cast<std::chrono::seconds>(hyro::TimeUtils::Now_TimeSinceEpoch());
  long int seconds          = secs.count(); //now expressed in seconds since epoch

  Signal value;
  value.timestamp = seconds;
  value.frame_id  = "Signal";
  value.value     = m_signal_generator.getSignalValue();
  /* Send out the updated signal message to the output channel ('signals') */
  m_output->sendAsync(value);
  return hyro::Result::RESULT_OK;
}

} // namespace hydrone
