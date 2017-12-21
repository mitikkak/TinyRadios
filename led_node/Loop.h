#pragma once

#include "RadioMode.h"
#include "TinyDebugSerial.h"

void ledNodeLoop();
void ledNodeLoopElse(RF24& radio, RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL);
void ledNodeLoopIf(RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL);
