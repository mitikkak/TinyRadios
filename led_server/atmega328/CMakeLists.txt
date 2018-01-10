
project(led_server)

INCLUDE_DIRECTORIES(${ARDUINO_PINS} ${ARDUINO_SPI_SRC})

include(${PROJECT_ROOT}/arduino_tools.cmake)

include(${PROJECT_ROOT}/atmega328_defs.cmake)
add_executable(${PROJECT_NAME} ${sources} ${shared_sources} ${arduino_core_sources} ${rf24_sources} ${spi_sources})

add_custom_target(elf_to_hex_led_server COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom led_server led_server.hex)
add_custom_target(upload_led_server COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -Uflash:w:./led_server.hex:i
                                    DEPENDS elf_to_hex_led_server)
