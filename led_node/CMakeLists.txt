
set(LED_NODE_SRC ${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${ARDUINO_CORE_SRC} ${SHARED_SRC} ${PROJECT_ROOT} ${ARDUINO_WIRE_SRC}  ${RF24_SRC} ${MESSAGES_SRC})
set(node_number 1 CACHE STRING "node number of led node")
add_definitions(-Dnode_number=${node_number})
#add_definitions(-DNODE_ALWAYS_ON)
set(sources ${LED_NODE_SRC}/Loop.cpp
            ${LED_NODE_SRC}/Setup.cpp
            ${LED_NODE_SRC}/Components.cpp
   )
set(shared ${SHARED_SRC}/RadioMode.cpp
           ${SHARED_SRC}/Blink.cpp
           ${SHARED_SRC}/Messages.cpp
   )

add_subdirectory(tiny85)
add_subdirectory(atmega328)
