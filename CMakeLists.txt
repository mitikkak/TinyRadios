
cmake_minimum_required(VERSION 3.1)

include(arduino_paths.cmake)

set(AVR_COMPILER_DIR ${ARDUINO_PATH}/hardware/tools/avr/bin)
set(ARDUINO_CORE_SRC ${ARDUINO_PATH}/hardware/arduino/avr/cores/arduino)
set(ARDUINO_WIRE_SRC ${ARDUINO_PATH}/hardware/arduino/avr/libraries/Wire/src/)
set(ARDUINO_PINS ${ARDUINO_PATH}/hardware/arduino/avr/variants/standard)
set(TINY85_SRC ${TINY_PKG_PATH}/hardware/avr/1.0.2/variants/tiny8)
set(TINY_DBG_SERIAL_SRC ${ARDUINO_LIB_PATH}/TinyDebugSerial)
set(RF24_SRC ${ARDUINO_LIB_PATH}/RF24)
set(MESSAGES_SRC ${ARDUINO_LIB_PATH}/Messages)

include (arduino_core.cmake)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(led_node)

