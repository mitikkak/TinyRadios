
INCLUDE_DIRECTORIES(${TINY85_SRC} ${ALTERNATE_TINY85_SRC} ${TINY_DBG_SERIAL_SRC})
add_definitions(-c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=attiny85 -DF_CPU=8000000L -DARDUINO=10612 -DARDUINO_attiny -DARDUINO_ARCH_AVR)
set(CMAKE_EXE_LINKER_FLAGS "-w -Os -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=attiny85")
