hyro_init_package(signal_generator VERSION 0.0.1)
hyro_find_package(hyro_utils REQUIRED)
hyro_find_package(hyro_msgs REQUIRED)
hyro_find_package(hyro_widgets REQUIRED)
###########
## Build ##
###########
## Specify additional locations of header files
## Your package locations should be listed before other locations
set(SIGNAL_GENERATOR_HEADERS
  # add all *.h files here
  include/hyro/SignalGeneratorComponent.hpp
  include/hyro/DigitalConverterComponent.hpp
  #Messages includes
  include/hyro/msgs/Signal.hpp
  include/hyro/msgs/Signal.proto.h
)
set(SIGNAL_GENERATOR_SOURCES
  # add all *.cpp files here
  src/components/SignalGeneratorComponent.cpp
  src/components/DigitalConverterComponent.cpp
  src/internal/SignalGenerator.cpp
  src/internal/Thresholding.cpp
)
## Example components library
#########################################
hyro_add_library(
  ${PROJECT_NAME}_components
  HEADERS 
    ${SIGNAL_GENERATOR_HEADERS}
  SOURCES 
    ${SIGNAL_GENERATOR_SOURCES}
  DEPENDS_ON
    hyro_utils
    hyro_msgs
    hyro_widgets
)
hyro_compile_messages(
  ${PROJECT_NAME}_components
  SOURCES msgs/hyro/msgs/Signal.proto
)
## Example executable
#########################################
hyro_add_executable(${PROJECT_NAME}
  SOURCES src/examples/signal_generator.cpp
  DEPENDS_ON ${PROJECT_NAME}_components
)
## Install targets
#########################################
hyro_install_package(${PROJECT_NAME}
  LIBS
    ${PROJECT_NAME}_components
  EXES
    ${PROJECT_NAME}
)
## Add GTest 
#########################################
hyro_add_gtest(${PROJECT_NAME}
  SOURCES 
    tests/test_signal_generator.cpp
  DEPENDS_ON
    ${PROJECT_NAME}_components
)