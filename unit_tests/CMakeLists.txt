
project(ut)

set(TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR})
set(LED_NODE_TEST_SRC ${PROJECT_ROOT}/led_node/tests)
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
     ${LEDNODE_SRC}/LedNodeLoop.cpp
   )
set(shared_sources
     ${SHARED_SRC}/Messages.cpp
     ${SHARED_SRC}/RadioMode.cpp
   )

add_definitions(-c -g -Os -w -std=gnu++11)
add_executable(${PROJECT_NAME} ${sources} ${led_node_sources} ${shared_sources})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)


