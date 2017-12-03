
#pragma once
#include "Messages.h"
#include "RadioMode.h"
#include "TinyDebugSerial.h"

void ledNodeLoop();
void ledNodeLoopElse(Ping const&  req, RF24& radio, RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL);
