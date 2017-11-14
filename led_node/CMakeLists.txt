
project(led_node)

set(MY_SRC ${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${ARDUINO_CORE_SRC} ${SHARED_SRC} ${MY_SRC} ${ARDUINO_WIRE_SRC} ${TINY_DBG_SERIAL_SRC} ${RF24_SRC} ${MESSAGES_SRC} ${TINY85_SRC} ${ALTERNATE_TINY85_SRC})

include(${PROJECT_ROOT}/tiny85_defs.cmake)

set(node_number 1 CACHE STRING "node number of led node")
add_definitions(-Dnode_number=${node_number})
#add_definitions(-DNODE_ALWAYS_ON)

set(sources ${MY_SRC}/Loop.cpp
            ${MY_SRC}/Setup.cpp
            ${MY_SRC}/Components.cpp
            ${MY_SRC}/LedNodeLoop.cpp
   )
set(shared ${SHARED_SRC}/RadioMode.cpp
           ${SHARED_SRC}/Blink.cpp
           ${SHARED_SRC}/Messages.cpp
   )

include(${PROJECT_ROOT}/arduino_tools.cmake)

#set(CMAKE_EXE_LINKER_FLAGS "-Os -Wl,--gc-sections -mmcu=atmega328p")
set(CMAKE_EXE_LINKER_FLAGS "-w -Os -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=attiny85")

add_executable(${PROJECT_NAME} ${sources} ${shared} ${arduino_core_sources} ${tiny_dbg_serial_sources} ${rf24_sources})

#Burn bootloader, 8Mhz internal clock
add_custom_target(bootloader_led_node COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -v -v -v -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -e -Uefuse:w:0xff:m -Uhfuse:w:0xdf:m -Ulfuse:w:0xe2:m)
add_custom_target(elf_to_hex_led_node COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom led_node led_node.hex)
add_custom_target(upload_led_node COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -Uflash:w:./led_node.hex:i
                         DEPENDS elf_to_hex_led_node)
add_custom_target(upload_led_node_1 COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -pattiny85 -cstk500v1 -P/dev/ttyACM1 -b19200 -Uflash:w:./led_node.hex:i
                         DEPENDS elf_to_hex_led_node)

add_custom_target(usage_led_node COMMAND echo "USAGE:"
                                 COMMAND echo "cmake -Dnode_number:STRING=[integer] ../"
                                 COMMAND echo "make led_node"
                                 COMMAND echo "make bootloader_led_node"
                                 COMMAND echo "make upload_led_node")

