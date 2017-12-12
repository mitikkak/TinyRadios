#pragma once

#include "RadioMode.h"
#include "TinyDebugSerial.h"

void ledNodeLoop();
void ledNodeLoopElse(Ping const&  req, RF24& radio, RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL);
void ledNodeLoopIf(Ping const & req, unsigned int& reqs, RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL);
