
project(led_server)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

INCLUDE_DIRECTORIES(${ARDUINO_CORE_SRC} ${ARDUINO_PINS} ${RF24_SRC} ${ARDUINO_SPI_SRC} ${MESSAGES_SRC})

set(sources ${SRC_DIR}/Loop.cpp
            ${SRC_DIR}/Setup.cpp
            ${SRC_DIR}/Components.cpp
   )

include(${PROJECT_ROOT}/arduino_tools.cmake)

add_definitions(-c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10800 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR)
set(CMAKE_EXE_LINKER_FLAGS "-Os -Wl,--gc-sections -mmcu=atmega328p")
add_executable(${PROJECT_NAME} ${sources} ${arduino_core_sources} ${rf24_sources} ${spi_sources})

add_custom_target(elf_to_hex_led_server COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom led_server led_server.hex)
add_custom_target(upload_led_server COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -Uflash:w:./led_server.hex:i
                                    DEPENDS elf_to_hex_led_server)
