#pragma once

#include "Arduino.h"
#include "TinyDebugSerial.h"
#include "RF24.h"
#include "Messages.h"

extern TinyDebugSerial _SERIAL;
extern RF24 radio;
const int ledPin = 4;

// dependent on RF24's tiny85 specific 3pin -feature
#define CE_PIN 9
#define CSN_PIN CE_PIN

#ifndef node_number
    #error "node_number not available! Check your build system."
#endif

static constexpr char node_id{node_number};
const byte remote_address[5] = {0xAA, 0xBB, 0xCC, 0xDD, 0x0};
const byte my_address[5] = {0xAA, 0xBB, 0xCC, 0xDD, node_id};

