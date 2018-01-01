#pragma once

#include "Arduino.h"
#include "TinyDebugSerial.h"
#include "RF24.h"
#include "Messages.h"
#include "RadioMode.h"

extern TinyDebugSerial _SERIAL;
extern RF24 radio;
extern RadioMode mode;
const int ledPin = 4;
//const int sendIndicator = 3;

// dependent on RF24's tiny85 specific 3pin -feature
#define CE_PIN 9
#define CSN_PIN CE_PIN

#ifndef node_number
    #error "node_number not available! Check your build system."
#endif

static constexpr char node_id{node_number};
const uint8_t my_address[5] = {0xAA, 0xBB, 0xCC, 0xDD, node_id};

