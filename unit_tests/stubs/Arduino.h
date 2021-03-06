
#pragma once

#include <assert.h>
#include "TinyDebugSerial.h"

typedef char byte;

static constexpr unsigned LOW = 0;
static constexpr unsigned HIGH = 1;

namespace Arduino {

static constexpr unsigned numPins = 14;
unsigned ledState(unsigned const pin);
void reset();
extern unsigned long timeNow;
extern unsigned long timeStep;
}

void digitalWrite(unsigned pin, unsigned state);
unsigned long millis();
unsigned long micros();

extern TinyDebugSerial Serial;


