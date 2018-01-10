
add_definitions(-c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10800 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR)
set(CMAKE_EXE_LINKER_FLAGS "-Os -Wl,--gc-sections -mmcu=atmega328p")
