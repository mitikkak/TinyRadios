
cmake_minimum_required(VERSION 3.1)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

include(arduino_paths.cmake)

set(AVR_COMPILER_DIR ${ARDUINO_PATH}/hardware/tools/avr/bin)
set(ARDUINO_CORE_SRC ${ARDUINO_PATH}/hardware/arduino/avr/cores/arduino)
set(ARDUINO_WIRE_SRC ${ARDUINO_PATH}/hardware/arduino/avr/libraries/Wire/src/)
set(ARDUINO_PINS ${ARDUINO_PATH}/hardware/arduino/avr/variants/standard)
set(ARDUINO_SPI_SRC ${ARDUINO_PATH}/hardware/arduino/avr/libraries/SPI/src)
set(TINY85_SRC ${TINY_PKG_PATH}/hardware/avr/1.0.2/variants/tiny8)
set(ALTERNATE_TINY85_SRC ${TINY_PKG_PATH}/variants/tiny8)
set(TINY_DBG_SERIAL_SRC ${ARDUINO_LIB_PATH}/TinyDebugSerial)
set(RF24_SRC ${ARDUINO_LIB_PATH}/RF24)
set(MESSAGES_SRC ${ARDUINO_LIB_PATH}/Messages)

include (arduino_core.cmake)
set(tiny_dbg_serial_sources ${TINY_DBG_SERIAL_SRC}/TinyDebugSerial.cpp
                            ${TINY_DBG_SERIAL_SRC}/TinyDebugSerial9600.cpp)
set(rf24_sources ${RF24_SRC}/RF24.cpp)
set(spi_sources ${ARDUINO_SPI_SRC}/SPI.cpp)

# Linker flags
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")   # remove -rdynamic for C
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") # remove -rdynamic for CXX

add_subdirectory(led_node)
add_subdirectory(led_server)
