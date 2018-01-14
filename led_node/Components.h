#pragma once

#include "Arduino.h"
#include "RF24.h"
#include "Messages.h"
#include "RadioMode.h"
#include "shared/RadioPins.h"

#ifdef ARDUINO_attiny
#include "TinyDebugSerial.h"
extern TinyDebugSerial _SERIAL;
#else
#define _SERIAL Serial
#endif
extern RF24 radio;
extern RadioMode mode;
const int ledPin = 4;
//const int sendIndicator = 3;

#ifndef node_number
    #error "node_number not available! Check your build system."
#endif

static constexpr char node_id{node_number};
const uint8_t my_address[5] = {0xAA, 0xBB, 0xCC, 0xDD, node_id};

