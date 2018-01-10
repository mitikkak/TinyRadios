
set(LED_SERVER_SRC ${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${ARDUINO_CORE_SRC} ${RF24_SRC} ${PROJECT_ROOT})

set(sources ${LED_SERVER_SRC}/Loop.cpp
            ${LED_SERVER_SRC}/LedServerLoop.cpp
            ${LED_SERVER_SRC}/Setup.cpp
            ${LED_SERVER_SRC}/Components.cpp
   )
set(shared_sources ${SHARED_SRC}/RadioMode.cpp
   )

add_subdirectory(tiny85)
add_subdirectory(atmega328)
