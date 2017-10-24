
# Find Arduino SDK delivered programs
find_program(AR_AVR_GCC NAMES avr-gcc PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_CXX NAMES avr-g++ PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_OBJCOPY NAMES avr-objcopy PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_OBJDUMP NAMES avr-objdump PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_RANLIB NAMES avr-ranlib PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)
find_program(AR_AVR_LD NAMES avr-ld PATHS ${ARDUINO_PATH}/hardware/tools/avr/bin NO_DEFAULT_PATH)

# Compiler suite specification
set(CMAKE_C_COMPILER ${AR_AVR_GCC})
set(CMAKE_CXX_COMPILER ${AR_AVR_CXX})
set(CMAKE_OBJCOPY ${AR_AVR_OBJCOPY})
set(CMAKE_OBJDUMP ${AR_AVR_OBJDUMP})
set(CMAKE_RANLIB ${AR_AVR_RANLIB})
set(CMAKE_LINKER ${AR_AVR_LD})
