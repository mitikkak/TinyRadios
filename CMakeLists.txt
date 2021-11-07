
cmake_minimum_required(VERSION 3.1)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(ARDUINO_CMAKE_DIR ${PROJECT_ROOT}/arduino_cmake)
include(${ARDUINO_CMAKE_DIR}/arduino_paths.cmake)

set(AVR_COMPILER_DIR ${ARDUINO_PATH}/hardware/tools/avr/bin)
set(ARDUINO_CORE_SRC ${ARDUINO_PATH}/hardware/arduino/avr/cores/arduino)
set(ARDUINO_WIRE_SRC ${ARDUINO_PATH}/hardware/arduino/avr/libraries/Wire/src/)
set(ARDUINO_PINS ${ARDUINO_PATH}/hardware/arduino/avr/variants/standard)
set(ARDUINO_SPI_SRC ${ARDUINO_PATH}/hardware/arduino/avr/libraries/SPI/src)
set(ARDUINO_SWSERIAL_SRC ${ARDUINO_PATH}/hardware/arduino/avr/libraries/SoftwareSerial/src)
set(TINY85_SRC ${TINY_PKG_PATH}/hardware/avr/1.5.2/variants/tinyX5)
set(ALTERNATE_TINY85_SRC ${TINY_PKG_PATH}/variants/tiny8)
set(TINY_DBG_SERIAL_SRC ${ARDUINO_LIB_PATH}/TinyDebugSerial)
set(RF24_SRC ${PROJECT_ROOT}/RF24)
set(SHARED_SRC ${PROJECT_ROOT}/shared)
set(LEDNODE_SRC ${PROJECT_ROOT}/led_node)
set(LEDSERVER_SRC ${PROJECT_ROOT}/led_server)
include (${ARDUINO_CMAKE_DIR}/arduino_core.cmake)
set(tiny_dbg_serial_sources ${TINY_DBG_SERIAL_SRC}/TinyDebugSerial.cpp
                            ${TINY_DBG_SERIAL_SRC}/TinyDebugSerial9600.cpp)
set(rf24_sources ${RF24_SRC}/RF24.cpp)
set(spi_sources ${ARDUINO_SPI_SRC}/SPI.cpp)

# Linker flags
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")   # remove -rdynamic for C
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") # remove -rdynamic for CXX

add_subdirectory(led_node)
add_subdirectory(led_server)
add_subdirectory(power_remote)
add_subdirectory(power_switch)
#add_subdirectory(unit_tests)
