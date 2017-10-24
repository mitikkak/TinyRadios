
set(arduino_core_sources ${ARDUINO_CORE_SRC}/CDC.cpp
                         ${ARDUINO_CORE_SRC}/HardwareSerial.cpp
                         ${ARDUINO_CORE_SRC}/HardwareSerial0.cpp
                         ${ARDUINO_CORE_SRC}/HardwareSerial1.cpp
                         ${ARDUINO_CORE_SRC}/HardwareSerial2.cpp
                         ${ARDUINO_CORE_SRC}/HardwareSerial3.cpp
                         ${ARDUINO_CORE_SRC}/IPAddress.cpp
                         ${ARDUINO_CORE_SRC}/PluggableUSB.cpp
                         ${ARDUINO_CORE_SRC}/Print.cpp
                         ${ARDUINO_CORE_SRC}/Stream.cpp
                         ${ARDUINO_CORE_SRC}/Tone.cpp
                         ${ARDUINO_CORE_SRC}/USBCore.cpp
                         ${ARDUINO_CORE_SRC}/WInterrupts.c
                         ${ARDUINO_CORE_SRC}/WMath.cpp
                         ${ARDUINO_CORE_SRC}/WString.cpp
                         ${ARDUINO_CORE_SRC}/abi.cpp
                         ${ARDUINO_CORE_SRC}/hooks.c
                         ${ARDUINO_CORE_SRC}/main.cpp
                         ${ARDUINO_CORE_SRC}/new.cpp
                         ${ARDUINO_CORE_SRC}/wiring.c
                         ${ARDUINO_CORE_SRC}/wiring_analog.c
                         ${ARDUINO_CORE_SRC}/wiring_digital.c
                         ${ARDUINO_CORE_SRC}/wiring_pulse.c
                         ${ARDUINO_CORE_SRC}/wiring_shift.c
)
