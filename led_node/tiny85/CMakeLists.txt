
project(led_node)

include(${PROJECT_ROOT}/tiny85_defs.cmake)

include(${PROJECT_ROOT}/arduino_tools.cmake)

add_executable(${PROJECT_NAME} ${sources} ${shared} ${arduino_core_sources} ${tiny_dbg_serial_sources} ${rf24_sources})

#Burn bootloader, 8Mhz internal clock
add_custom_target(bootloader_tiny85_8Mhz COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -v -v -v -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -e -Uefuse:w:0xff:m -Uhfuse:w:0xdf:m -Ulfuse:w:0xe2:m)
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
