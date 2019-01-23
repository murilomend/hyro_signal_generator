#include <hyro/SignalGeneratorComponent.hpp>
#include <hyro/DigitalConverterComponent.hpp>
#include <hyro/utils/DynamicPropertyAccess.h>

#include <hyro/test/ComponentTester.h>
#include <gtest/gtest.h>

static void
__assert_and_run_state_machine(hyro::StateMachine& sm,
                               const hyro::ComponentConfiguration& conf,
                               const hyro::ConnectionConfiguration& endpoint)
{
  ASSERT_EQ(hyro::Result::RESULT_OK, sm.init(conf));

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.start());

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.connect(endpoint));

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.check());
}

#define ASSERT_AND_RUN_STATE_MACHINE(sm, conf, endpoint) \
  __assert_and_run_state_machine(sm, conf, endpoint)



namespace hyro
{
namespace test
{

TEST (TestSignalGenerator, SignalGeneratorComponentCheck)
{
  //Configuration
  auto signal_config     = "{"
                            "outputs: {"
                            "signals: { protocol: 'api' },"
                            "fix_dynamic: { protocol: 'api' }"
                            "}"
                            "}";

  //IntGeneratorComponent state machine
  StateMachine sig_sm(std::make_shared<SignalGeneratorComponent>("/signal_generator"_uri));

  auto result = sig_sm.init(ComponentConfiguration(signal_config));
  ASSERT_EQ(Result::RESULT_OK, result);

  result = sig_sm.start();
  ASSERT_EQ(Result::RESULT_OK, result);

  result = sig_sm.connect(ConnectionConfiguration());
  ASSERT_EQ(Result::RESULT_OK, result);

  result = sig_sm.check();
  ASSERT_EQ(Result::RESULT_OK, result);

  
  //Fake input channels
  auto inputSignal = std::make_shared<FakeInput<Signal>>("inputSignal"_uri, "api", "/signal_generator/signals");
  ASSERT_TRUE(inputSignal->connect());

  sig_sm.update();
  auto valueSignal = std::shared_ptr<const Signal>();
  ReceiveStatus ret = inputSignal->receive(valueSignal, 500ms);
  ASSERT_EQ(ReceiveStatus::RECEIVE_OK, ret);
  EXPECT_EQ(valueSignal->value, 0);

  //Dynamic properties
  DynamicPropertyAccess dynamic_property_access("/signal_generator"_uri);
  float not_exits;
  ASSERT_ANY_THROW(dynamic_property_access.get("not_exists", not_exits));
  ASSERT_TRUE(dynamic_property_access.set("amplitude", 10.0));
  ASSERT_TRUE(dynamic_property_access.set("frequency", 20.0));
  ASSERT_TRUE(dynamic_property_access.set("cosine", true));
  
  double amplitude, frequency;
  bool cosine;
  ASSERT_TRUE(dynamic_property_access.get("amplitude", amplitude));
  ASSERT_TRUE(dynamic_property_access.get("frequency", frequency));
  ASSERT_TRUE(dynamic_property_access.get("cosine", cosine));

  ASSERT_NEAR(amplitude, 10.0, 0.001);
  ASSERT_NEAR(frequency, 20.0, 0.001);
  ASSERT_EQ(cosine,true);
}

TEST (TestSignalGenerator, DigitalConverterComponentCheck)
{
  //Configuration
  auto digital_config  = "{"
                          "inputs: {"
                          "signals: {protocol: 'api'}},"
                          "outputs: {"
                          "digital_signals: {protocol: 'api'},"
                          "fix_dynamic: { protocol: 'api' }"
                          "}"
                          "}";
  //IntGeneratorComponent state machine
  StateMachine dig_sm(std::make_shared<DigitalConverterComponent>("/digital_converter"_uri));

  // Fake outputs channels
  auto outputSignal = std::make_shared<FakeOutput<Signal>>("outputSignal"_uri, "api");
  ASSERT_TRUE(outputSignal->start());

  auto configuration = ComponentConfiguration(digital_config);
  auto endpoint = ConnectionConfiguration("{ signals: { endpoint: 'outputSignal' } }");
  ASSERT_AND_RUN_STATE_MACHINE(dig_sm, configuration, endpoint);

  //Fake input channels
  auto inputSignal = std::make_shared<FakeInput<Signal>>("inputSignal"_uri, "api", "/digital_converter/digital_signals");
  ASSERT_TRUE(inputSignal->connect());

  //Dynamic properties
  DynamicPropertyAccess dynamic_property_access("/digital_converter"_uri);
  float not_exits;
  ASSERT_ANY_THROW(dynamic_property_access.get("not_exists", not_exits));

  ASSERT_TRUE(dynamic_property_access.set("amplitude", 10.0));
  ASSERT_TRUE(dynamic_property_access.set("threshold", 20.0));

  
  double amplitude = 0, threshold = 0;

  ASSERT_TRUE(dynamic_property_access.get("amplitude", amplitude));
  ASSERT_TRUE(dynamic_property_access.get("threshold", threshold));

  ASSERT_NEAR(amplitude, 10.0, 0.001);
  ASSERT_NEAR(threshold, 20.0, 0.001);

}

int main (int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}
}