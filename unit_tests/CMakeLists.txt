
project(ut)

set(TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR})
find_package(GTest REQUIRED GTEST_ROOT=/home/mitikkak/googletest/googletest)

set( CMAKE_BUILD_TYPE Debug)
set(sources
    ${TEST_SRC}/Runner.cpp
    ${TEST_SRC}/TestRadioMode.cpp
)
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)


