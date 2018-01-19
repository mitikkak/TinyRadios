
project(led_server_tiny85)

include(${ARDUINO_CMAKE_DIR}/tiny85_defs.cmake)

include(${ARDUINO_CMAKE_DIR}/arduino_tools.cmake)

add_executable(${PROJECT_NAME} ${sources} ${shared_sources} ${arduino_core_sources} ${tiny_dbg_serial_sources} ${rf24_sources})

add_custom_target(elf_to_hex_led_server_tiny85 COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom led_server_tiny85 led_server_tiny85.hex)
add_custom_target(upload_led_server_tiny85 COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -Uflash:w:./led_server_tiny85.hex:i
                         DEPENDS elf_to_hex_led_server_tiny85)
add_custom_target(upload_led_server_tiny85_1 COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -pattiny85 -cstk500v1 -P/dev/ttyACM1 -b19200 -Uflash:w:./led_server_tiny85.hex:i
                                             DEPENDS elf_to_hex_led_server_tiny85)
