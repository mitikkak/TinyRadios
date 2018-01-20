
project(led_server)

INCLUDE_DIRECTORIES(${ARDUINO_PINS} ${ARDUINO_SPI_SRC})

include(${ARDUINO_CMAKE_DIR}/arduino_tools.cmake)

include(${ARDUINO_CMAKE_DIR}/atmega328_defs.cmake)
add_definitions(-DBLUETOOTH_ON)
add_executable(${PROJECT_NAME} ${led_server_common_sources} ${spi_sources} ${sw_serial_sources})

add_custom_target(elf_to_hex_led_server COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom led_server led_server.hex)
add_custom_target(upload_led_server COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -Uflash:w:./led_server.hex:i
                                    DEPENDS elf_to_hex_led_server)
add_custom_target(upload_led_server_1 COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM1 -b115200 -Uflash:w:./led_server.hex:i
                                      DEPENDS elf_to_hex_led_server)
