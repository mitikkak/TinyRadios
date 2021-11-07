
project(power_remote_atmega)

INCLUDE_DIRECTORIES(${ARDUINO_PINS} ${ARDUINO_SPI_SRC})
include(${ARDUINO_CMAKE_DIR}/arduino_tools.cmake)

include(${ARDUINO_CMAKE_DIR}/atmega328_defs.cmake)

add_executable(${PROJECT_NAME} ${sources} ${shared} ${arduino_core_sources} ${rf24_sources} ${spi_sources})

add_custom_target(elf_to_hex_power_remote_atmega COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom power_remote_atmega power_remote_atmega.hex)
add_custom_target(upload_power_remote_atmega COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -Uflash:w:./power_remote_atmega.hex:i
                                    DEPENDS elf_to_hex_power_remote_atmega)
add_custom_target(upload_power_remote_atmega_1 COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM1 -b115200 -Uflash:w:./power_remote_atmega.hex:i
                                           DEPENDS elf_to_hex_power_remote_atmega)
