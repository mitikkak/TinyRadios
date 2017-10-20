
project(led_node)
cmake_minimum_required(VERSION 3.1)
message(ARDUINO_PATH: ${ARDUINO_PATH})
if(${ARDUINO_PATH} MATCHES .*arduino.*)
   message("arduino path found at:" ${ARDUINO_PATH})
else()
   message("setting arduino path from env variable ...")
   set(ARDUINO_PATH $ENV{ARDUINO_PATH} CACHE STRING "")
endif()

if(${ARDUINO_PATH} MATCHES .*arduino.*)
   message("arduino path found at:" ${ARDUINO_PATH})
else()
   message(FATAL_ERROR "ARDUINO_PATH environment variable missing! It should point to root of arduino installation, for example /home/your_name/arduino-1.6.12/")
endif()

set(AVR_COMPILER_DIR ${ARDUINO_PATH}/hardware/tools/avr/bin)
set(CMAKE_C_COMPILER ${AVR_COMPILER_DIR}/avr-gcc)
set(CMAKE_CXX_COMPILER ${AVR_COMPILER_DIR}/avr-g++)
set(ARDUINO_CORE_SRC ${ARDUINO_PATH}/hardware/arduino/avr/cores/arduino)
set(ARDUINO_WIRE_SRC ${ARDUINO_PATH}/hardware/arduino/avr/libraries/Wire/src/)
set(ARDUINO_PINS ${ARDUINO_PATH}/hardware/arduino/avr/variants/standard)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${ARDUINO_CORE_SRC} ${SRC_DIR} ${ARDUINO_WIRE_SRC} /home/mikko/.arduino15/packages/attiny/hardware/avr/1.0.2/variants/tiny8)

add_definitions(-c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=attiny85 -DF_CPU=8000000L -DARDUINO=10612 -DARDUINO_attiny -DARDUINO_ARCH_AVR)
#add_definitions(-c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10800 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR)

set(sources ${SRC_DIR}/Loop.cpp ${SRC_DIR}/Setup.cpp)
set(arduino_core_sources ${ARDUINO_CORE_SRC}/CDC.cpp
                         ${ARDUINO_CORE_SRC}/HardwareSerial.cpp
                         ${ARDUINO_CORE_SRC}/HardwareSerial0.cpp
                         ${ARDUINO_CORE_SRC}/HardwareSerial1.cpp
                         ${ARDUINO_CORE_SRC}/HardwareSerial2.cpp
                         ${ARDUINO_CORE_SRC}/HardwareSerial3.cpp
                         ${ARDUINO_CORE_SRC}/IPAddress.cpp
                         ${ARDUINO_CORE_SRC}/PluggableUSB.cpp
                         ${ARDUINO_CORE_SRC}/Print.cpp
                         ${ARDUINO_CORE_SRC}/Stream.cpp
                         ${ARDUINO_CORE_SRC}/Tone.cpp
                         ${ARDUINO_CORE_SRC}/USBCore.cpp
                         ${ARDUINO_CORE_SRC}/WInterrupts.c
                         ${ARDUINO_CORE_SRC}/WMath.cpp
                         ${ARDUINO_CORE_SRC}/WString.cpp
                         ${ARDUINO_CORE_SRC}/abi.cpp
                         ${ARDUINO_CORE_SRC}/hooks.c
                         ${ARDUINO_CORE_SRC}/main.cpp
                         ${ARDUINO_CORE_SRC}/new.cpp
                         ${ARDUINO_CORE_SRC}/wiring.c
                         ${ARDUINO_CORE_SRC}/wiring_analog.c
                         ${ARDUINO_CORE_SRC}/wiring_digital.c
                         ${ARDUINO_CORE_SRC}/wiring_pulse.c
                         ${ARDUINO_CORE_SRC}/wiring_shift.c
)

# Find Arduino SDK delivered programs
find_program(AR_AVR_GCC NAMES avr-gcc PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_CXX NAMES avr-g++ PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_OBJCOPY NAMES avr-objcopy PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_OBJDUMP NAMES avr-objdump PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_RANLIB NAMES avr-ranlib PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_LD NAMES avr-ld PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)

# Compiler suite specification
set(CMAKE_C_COMPILER ${AR_AVR_GCC})
set(CMAKE_CXX_COMPILER ${AR_AVR_CXX})
set(CMAKE_OBJCOPY ${AR_AVR_OBJCOPY})
set(CMAKE_OBJDUMP ${AR_AVR_OBJDUMP})
set(CMAKE_RANLIB ${AR_AVR_RANLIB})
set(CMAKE_LINKER ${AR_AVR_LD})

# Linker flags
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")   # remove -rdynamic for C
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") # remove -rdynamic for CXX
#set(CMAKE_EXE_LINKER_FLAGS "-Os -Wl,--gc-sections -mmcu=atmega328p")
set(CMAKE_EXE_LINKER_FLAGS "-w -Os -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=attiny85")

add_executable(${PROJECT_NAME} ${sources} ${arduino_core_sources})

#Burn bootloader, 8Mhz internal clock
add_custom_target(bootloader COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -v -v -v -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -e -Uefuse:w:0xff:m -Uhfuse:w:0xdf:m -Ulfuse:w:0xe2:m)
add_custom_target(elf_to_hex COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom led_node led_node.hex)
add_custom_target(upload COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -Uflash:w:./led_node.hex:i
                         DEPENDS elf_to_hex)

