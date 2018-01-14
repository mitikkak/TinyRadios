
project(led_node_atmega)

INCLUDE_DIRECTORIES(${ARDUINO_PINS} ${ARDUINO_SPI_SRC})
include(${PROJECT_ROOT}/arduino_tools.cmake)

include(${PROJECT_ROOT}/atmega328_defs.cmake)

add_executable(${PROJECT_NAME} ${sources} ${shared} ${arduino_core_sources} ${rf24_sources} ${spi_sources})

add_custom_target(elf_to_hex_led_node_atmega COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom led_node_atmega led_node_atmega.hex)
add_custom_target(upload_led_node_atmega COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -Uflash:w:./led_node_atmega.hex:i
                                    DEPENDS elf_to_hex_led_node_atmega)
add_custom_target(upload_led_node_atmega_1 COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM1 -b115200 -Uflash:w:./led_node_atmega.hex:i
                                           DEPENDS elf_to_hex_led_node_atmega)
