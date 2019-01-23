#include <hyro/common/Time.h>
#include <hyro/core/StateMachine.h>
#include <hyro/utils/StateMachineSpinner.h>
#include <hyro/widgets/WidgetCollection.h>
#include <hyro/factory/CommandFactory.h>
#include <hyro/utils/DynamicPropertyAccess.h>
#include <hyro/msgs/Signal.hpp>

#include <hyro/SignalGeneratorComponent.hpp>
#include <hyro/DigitalConverterComponent.hpp>

using namespace hyro;
using namespace std::string_literals;

int main ()
{
  hyro::LogConfig config;
  config.level = hyro::LogLevel::CRITICAL;
  hyro::HyroLoggerManager::Configure(config);
  /*
   * STEP 1: Component instantiation
   */
  // Define the state machine for both Signal amd Digital Components
  StateMachine sig_sm(std::make_shared<SignalGeneratorComponent>("/signal_generator"_uri));
  StateMachine dig_sm(std::make_shared<DigitalConverterComponent>("/digital_converter"_uri));

  /*
   * STEP 2: Components configuration
   */
  // Configuration map for the component inputs & outputs
  /*ComponentConfiguration gen1_conf = ComponentConfiguration("{parameters: {min: 0, max: 50},"
                                                                         "outputs: {number: {protocol: 'lcm'}}}");*/

  ComponentConfiguration signal_config  =    ComponentConfiguration("{"
                                                                      "parameters: {amplitude: 0.5, frequency: 0.5, cosine: true},"
                                                                      "outputs: {"
                                                                        "signals: { protocol: 'api' },"
                                                                        "fix_dynamic: { protocol: 'api' }"
                                                                      "}"
                                                                      "}");
  ComponentConfiguration digital_config =    ComponentConfiguration("{"
                                                                      "parameters: {amplitude: 2, threshold: 0.0},"
                                                                      "inputs: {"
                                                                        "signals: {protocol: 'api'}},"
                                                                      "outputs: {"
                                                                        "digital_signals: {protocol: 'api'},"
                                                                        "fix_dynamic: { protocol: 'api' }"
                                                                      "}"
                                                                      "}");
        
  // Ports Connection Configuration
  // Connection map
  auto dig_connections = ConnectionConfiguration(
    "{ signals: {endpoint: '/signal_generator/signals' }}");

  /*
   * STEP 3: Init the SMs
   */
  // Init Components State Machines
  sig_sm.init(signal_config);
  dig_sm.init(digital_config);
  /*
   * STEP 4: Start the SMs
   */
  // Start Components State Machines
  sig_sm.start();
  dig_sm.start();
  /*
   * STEP 5: Connections
   */
  // Connect ports between different componets
  sig_sm.connect();
  dig_sm.connect(dig_connections);
  /*
   * STEP 6: Check Everything
   */
  sig_sm.check();
  dig_sm.check();

  sig_sm.update();
  dig_sm.update();

  /*
   * STEP 7: Run Everything
   */
  CancellationTokenSource cancellation_token;

  StateMachineSpinner sig_spinner(sig_sm, cancellation_token, 1ms);
  StateMachineSpinner dig_spinner(dig_sm, cancellation_token, 1ms);
  
  std::thread plot_thread([]()
  {
    widgets::registerChannelListener<hyro::Signal>("/signal_generator/signals", "api", [](Signal signal_msg)
    {
      widgets::plot2d<float>("Signal", "/signal_generator/signals/value", signal_msg.value);
    });
    widgets::plot2d<float>("Signal", "/digital_converter/digital_signals", widgets::Plot2dSettings::initWithProtocol("api"));
    widgets::exec();
  });

  std::this_thread::sleep_for(1s);
  //Dynamic properties Access
  DynamicPropertyAccess dynamic_property_access_sig("/signal_generator"_uri);
  DynamicPropertyAccess dynamic_property_access_dig("/digital_converter"_uri);
  char ch;
  do
  {
    double  amplitude_sig = 0,frequency = 0;
    double  amplitude_dig = 0,threshold = 0;
    bool    cosine = false;

    std::cout << "Set Signal Properties" << std::endl;

    // Read parameters values
    dynamic_property_access_sig.get<double>("amplitude", amplitude_sig);
    dynamic_property_access_sig.get<double>("frequency", frequency);
    dynamic_property_access_sig.get<bool>("cosine", cosine);
    dynamic_property_access_dig.get<double>("amplitude",amplitude_dig);
    dynamic_property_access_dig.get<double>("threshold",threshold);
    std::cout << "Current parameters" <<  std::endl;
    std::cout << "SIGNAL GENERATOR  : Amplitude: " << amplitude_sig << ", Frequency: " << frequency << ", Cosine: " << cosine << std::endl;
    std::cout << "DIGITAl_CONVERTER : Amplitude: " << amplitude_dig << ", Threshold: " << threshold << std::endl;

    // Get user inputs
    std::cout << "Please inform the Signal Amplitude(Double): ";
    std::cin >> amplitude_sig;
    std::cout << "Please inform the Signal Frequency(Double): ";
    std::cin >> frequency;
    std::cout << "Please inform cosine (Int): 1 for Cosine, 0 to Sine: ";
    std::cin >> cosine;
    std::cout << "Please inform the Converter Amplitude(Double): ";
    std::cin >> amplitude_dig;
    std::cout << "Please inform the Converter Threshlod(Double): ";
    std::cin >> threshold;

    // Assign parameters values
    dynamic_property_access_sig.set<double>("amplitude", amplitude_sig);
    dynamic_property_access_sig.set<double>("frequency", frequency);
    dynamic_property_access_sig.set<bool>("cosine", cosine);
    dynamic_property_access_dig.set<double>("amplitude", amplitude_dig);
    dynamic_property_access_dig.set<double>("threshold", threshold);

    //widgets::exec();
    std::cout << "Continue (Y/n): ";
    std::cin >> ch;

  }while (ch != 'n' && ch != 'N');
  /*
   * STEP 7: Stop everything
   */
  // Let the system run for a while, then tell everyone to stop.
  std::this_thread::sleep_for(2s);
  // This call will signal every spinner's thread
  cancellation_token.cancel();
  // Wait for the components to stop any update() execution
  plot_thread.join();
  sig_spinner.wait();
  dig_spinner.wait();


  /*
   * STEP 8: Cleaning up : 
   * It has caused Segmentation Fault at the end of the program when included
   */
  // Reset Components State Machines
  /*widgets::reset();
  sig_sm.reset();
  dig_sm.reset();*/
  
  return 0;

}
