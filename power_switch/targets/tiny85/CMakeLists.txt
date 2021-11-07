
project(power_switch_tiny)

include(${ARDUINO_CMAKE_DIR}/tiny85_defs.cmake)

include(${ARDUINO_CMAKE_DIR}/arduino_tools.cmake)

add_executable(${PROJECT_NAME} ${sources} ${shared} ${arduino_core_sources} ${tiny_dbg_serial_sources} ${rf24_sources})

#Burn bootloader, 8Mhz internal clock
#add_custom_target(bootloader_tiny85_8Mhz COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -v -v -v -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -e -Uefuse:w:0xff:m -Uhfuse:w:0xdf:m -Ulfuse:w:0xe2:m)
add_custom_target(elf_to_hex_power_switch_tiny COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom power_switch_tiny power_switch_tiny.hex)
add_custom_target(upload_power_switch_tiny COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -Uflash:w:./power_switch_tiny.hex:i
                         DEPENDS elf_to_hex_power_switch_tiny)
add_custom_target(upload_power_switch_tiny_1 COMMAND ${ARDUINO_PATH}/hardware/tools/avr/bin/avrdude -C${ARDUINO_PATH}/hardware/tools/avr/etc/avrdude.conf -v -pattiny85 -cstk500v1 -P/dev/ttyACM1 -b19200 -Uflash:w:./power_switch_tiny.hex:i
                         DEPENDS elf_to_hex_power_switch_tiny)

add_custom_target(usage_power_switch_tiny COMMAND echo "USAGE:"
                                 COMMAND echo "cmake -Dnode_number:STRING=[integer] ../"
                                 COMMAND echo "make power_switch_tiny"
                                 COMMAND echo "make bootloader_power_switch_tiny"
                                 COMMAND echo "make upload_power_switch_tiny")
