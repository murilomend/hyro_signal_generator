#include <hyro/SignalGeneratorComponent.hpp>

namespace hyro
{

std::shared_ptr<hyro::HyroLogger> SignalGeneratorComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("SignalGeneratorComponent");

SignalGeneratorComponent::SignalGeneratorComponent (URI uri): hyro::Component(uri)
{
  // Initialize object here
};

hyro::Result SignalGeneratorComponent::init (const hyro::ComponentConfiguration & config)
{
  //Dummy output for fixing the DynamicProperty bug for unit tests
  std::shared_ptr<ChannelOutput<std::vector<int>>>
  m_dummy = this->registerOutput<std::vector<int>>("fix_dynamic"_uri, config);

  m_output = this->registerOutput<Signal>("signals"_uri, config);
  m_signal_generator = SignalGenerator();

  m_amplitude = config.parameters.getParameter<double>("amplitude", 1.0);
  m_frequency = config.parameters.getParameter<double>("frequency", 1.0);
  m_cosine    = config.parameters.getParameter<bool>("cosine", false);

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

  /*m_amplitude = 10;
  m_frequency = 5;
  m_cosine    = false;*/
  m_signal_generator.setSignalGenerator(m_amplitude,m_frequency,m_cosine);
  return hyro::Result::RESULT_OK;
}


bool SignalGeneratorComponent::setAmplitude(double amplitude)
{
  m_amplitude = amplitude;
  return m_signal_generator.setSignalGenerator(m_amplitude,m_frequency,m_cosine);
}

double SignalGeneratorComponent::getAmplitude()
{
  return this->m_amplitude;
}

bool SignalGeneratorComponent::setFrequency(double frequency)
{
  m_frequency = frequency;
  return m_signal_generator.setSignalGenerator(m_amplitude,m_frequency,m_cosine);
}

double SignalGeneratorComponent::getFrequency()
{
  return this->m_frequency;
}


bool SignalGeneratorComponent::setCosine(bool cosine)
{
  m_cosine = cosine;
  return m_signal_generator.setSignalGenerator(m_amplitude,m_frequency,m_cosine);
}

bool SignalGeneratorComponent::getCosine()
{
  return this->m_cosine;
}


hyro::Result SignalGeneratorComponent::reset ()
{
    // Reset all variables and objects like the object was just created
    m_output.reset();
    return hyro::Result::RESULT_OK;
}

hyro::Result SignalGeneratorComponent::check ()
{
  // Check everything is OK here
  return hyro::Result::RESULT_OK;
}

hyro::Result SignalGeneratorComponent::start ()
{
  // Start spinners and drivers (if any) here
  return hyro::Result::RESULT_OK;
}

hyro::Result SignalGeneratorComponent::update()
{
  Signal value;
  value.timestamp = 1000;
  value.frame_id  = "Signal";
  value.value     = m_signal_generator.getSignalValue();
  m_output->sendAsync(value);
  // Perform the operations here
  return hyro::Result::RESULT_OK;
}

} // namespace hydrone
