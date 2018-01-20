
set(LED_SERVER_SRC ${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${ARDUINO_CORE_SRC} ${RF24_SRC} ${ARDUINO_SWSERIAL_SRC} ${PROJECT_ROOT})

set(sources ${LED_SERVER_SRC}/Loop.cpp
            ${LED_SERVER_SRC}/LedServerLoop.cpp
            ${LED_SERVER_SRC}/Setup.cpp
            ${LED_SERVER_SRC}/Components.cpp
   )
set(shared_sources ${SHARED_SRC}/RadioMode.cpp
   )
set(sw_serial_sources ${ARDUINO_SWSERIAL_SRC}/SoftwareSerial.cpp
)
set(led_server_common_sources ${sources} ${shared_sources} ${arduino_core_sources} ${rf24_sources})
add_subdirectory(tiny85)
add_subdirectory(atmega328)
