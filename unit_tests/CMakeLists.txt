
project(ut)

set(TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR})
set(LED_NODE_TEST_SRC ${PROJECT_ROOT}/led_node/tests)
set(LEDSERVER_TEST_SRC ${PROJECT_ROOT}/led_server/tests)
set(STUBS_SRC ${PROJECT_ROOT}/unit_tests/stubs)
find_package(GTest REQUIRED GTEST_ROOT=/home/mitikkak/googletest/googletest)

set( CMAKE_BUILD_TYPE Debug)
set(sources
    ${TEST_SRC}/Runner.cpp
    ${TEST_SRC}/TestRadioMode.cpp
)
include_directories(${PROJECT_ROOT}
                    ${SHARED_SRC}
                    ${STUBS_SRC}
                   )
set(led_node_sources
     ${LED_NODE_TEST_SRC}/TestLedNodeLoop.cpp
     ${LEDNODE_SRC}/Loop.cpp
     ${LEDNODE_SRC}/Components.cpp
   )
set(led_server_sources
    ${LEDSERVER_TEST_SRC}/TestLedServerLoop.cpp
    ${LEDSERVER_SRC}/LedServerLoop.cpp
   )
set(shared_sources
     ${SHARED_SRC}/Messages.cpp
     ${SHARED_SRC}/RadioMode.cpp
   )
set(stub_sources
    ${STUBS_SRC}/Arduino.cpp
    ${STUBS_SRC}/RF24.cpp
   )

add_definitions(-c -g -w -std=gnu++11)
add_definitions(-Dnode_number=1)
add_executable(${PROJECT_NAME} ${sources} ${led_node_sources} ${led_server_sources} ${shared_sources} ${stub_sources})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)


