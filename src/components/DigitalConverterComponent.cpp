#include <hyro/DigitalConverterComponent.hpp>

namespace hyro
{

std::shared_ptr<hyro::HyroLogger> DigitalConverterComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("DigitalConverterComponent");

DigitalConverterComponent::DigitalConverterComponent (URI uri): hyro::Component(uri)
{
  // Initialize object here
};

hyro::Result DigitalConverterComponent::init (const hyro::ComponentConfiguration & config)
{
  //Dummy output for fixing the DynamicProperty bug for unit tests
  std::shared_ptr<ChannelOutput<std::vector<int>>>
  m_dummy = this->registerOutput<std::vector<int>>("fix_dynamic"_uri, config);
  
  m_input  = this->registerInput<Signal>("signals"_uri, config);
  m_output = this->registerOutput<float>("digital_signals"_uri, config);

  m_amplitude = config.parameters.getParameter<double>("amplitude", 2.0);
  m_threshold = config.parameters.getParameter<double>("threshold", 0.0);

  registerDynamicProperty<double>(
    "amplitude",
    &DigitalConverterComponent::setAmplitude,
    &DigitalConverterComponent::getAmplitude,
    this);
  registerDynamicProperty<double>(
    "threshold",
    &DigitalConverterComponent::setThreshold,
    &DigitalConverterComponent::getThreshold,
    this);

    m_thresh = Thresholding(m_amplitude,m_threshold);
    return hyro::Result::RESULT_OK;
}


bool DigitalConverterComponent::setAmplitude(double amplitude)
{
  m_amplitude = amplitude;
  return m_thresh.setThreshold(m_amplitude,m_threshold);
}

double DigitalConverterComponent::getAmplitude()
{
  return this->m_amplitude;
}

bool DigitalConverterComponent::setThreshold(double threshold)
{
  this->m_threshold = threshold;
  return m_thresh.setThreshold(m_amplitude,m_threshold);
}

double DigitalConverterComponent::getThreshold()
{
  return this->m_threshold;
}

hyro::Result DigitalConverterComponent::reset ()
{
    // Reset all variables and objects like the object was just created
    m_input.reset();
    m_output.reset();
    return hyro::Result::RESULT_OK;
}

hyro::Result DigitalConverterComponent::check ()
{
  // Check everything is OK here
  return hyro::Result::RESULT_OK;
}

hyro::Result DigitalConverterComponent::start ()
{
  // Start spinners and drivers (if any) here
  return hyro::Result::RESULT_OK;
}

hyro::Result DigitalConverterComponent::update()
{
  // Wait for an input value or exit after 1 second.
  auto value = std::shared_ptr<const Signal>();
  auto ret   = m_input->receive(value, 0s);

  // If the timeout has not been triggered but we actually have got some number,
  // convert it to string and send it out.
  if (ret == ReceiveStatus::RECEIVE_OK)
  {
      float thresh_signal = m_thresh.getSignalThreshold(value->value);
      m_output->sendAsync(thresh_signal);
  }
  // Signal the everything went fine.

  // Perform the operations here
  return hyro::Result::RESULT_OK;
}

} // namespace hydrone
