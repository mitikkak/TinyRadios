
INCLUDE_DIRECTORIES(${ARDUINO_CORE_SRC} ${SHARED_SRC} ${PROJECT_ROOT} ${ARDUINO_WIRE_SRC}  ${RF24_SRC} ${MESSAGES_SRC})
set(sources ${CMAKE_CURRENT_SOURCE_DIR}/power_switch.cpp)
add_subdirectory(targets/atmega328)
add_subdirectory(targets/tiny85)