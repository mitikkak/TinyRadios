
project(led_node)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${ARDUINO_CORE_SRC} ${SRC_DIR} ${ARDUINO_WIRE_SRC} ${TINY_DBG_SERIAL_SRC} ${RF24_SRC} ${MESSAGES_SRC} ${TINY85_SRC})

add_definitions(-c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=attiny85 -DF_CPU=8000000L -DARDUINO=10612 -DARDUINO_attiny -DARDUINO_ARCH_AVR)
set(node_number 1 CACHE STRING "node number of led node")
add_definitions(-Dnode_number=${node_number})

set(sources ${SRC_DIR}/Loop.cpp
            ${SRC_DIR}/Setup.cpp
            ${SRC_DIR}/Components.cpp
            ${SRC_DIR}/Blink.cpp
   )

set(tiny_dbg_serial_sources ${TINY_DBG_SERIAL_SRC}/TinyDebugSerial.cpp
                            ${TINY_DBG_SERIAL_SRC}/TinyDebugSerial9600.cpp)
set(rf24_sources ${RF24_SRC}/RF24.cpp)

include(${PROJECT_ROOT}/arduino_tools.cmake)

# Linker flags
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")   # remove -rdynamic for C
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") # remove -rdynamic for CXX
#set(CMAKE_EXE_LINKER_FLAGS "-Os -Wl,--gc-sections -mmcu=atmega328p")
set(CMAKE_EXE_LINKER_FLAGS "-w -Os -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=attiny85")

add_executable(${PROJECT_NAME} ${sources} ${arduino_core_sources} ${tiny_dbg_serial_sources} ${rf24_sources})

#Burn bootloader, 8Mhz internal clock
add_custom_target(bootloader_led_node COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -v -v -v -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -e -Uefuse:w:0xff:m -Uhfuse:w:0xdf:m -Ulfuse:w:0xe2:m)
add_custom_target(elf_to_hex_led_node COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom led_node led_node.hex)
add_custom_target(upload_led_node COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -Uflash:w:./led_node.hex:i
                         DEPENDS elf_to_hex_led_node)

add_custom_target(usage_led_node COMMAND echo "USAGE:"
                                 COMMAND echo "cmake -Dnode_number:STRING=[integer] ../"
                                 COMMAND echo "make led_node"
                                 COMMAND echo "make bootloader_led_node"
                                 COMMAND echo "make upload_led_node")

