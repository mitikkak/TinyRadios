#pragma once

#include "RadioMode.h"
#include "TinyDebugSerial.h"

void ledNodeLoop();
void ledNodeLoopElse(Ping const&  req, RF24& radio, RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL);
void ledNodeLoopIf(unsigned int& reqs, bool const reqReceived, RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL);
