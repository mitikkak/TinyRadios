#pragma once

#include "RadioMode.h"
#include "TinyDebugSerial.h"
#include "RF24.h"

void ledNodeLoop();
void ledNodeLoopElse(RF24& radio, RadioMode& mode, const int transactionId, TIME const timeNow, TinyDebugSerial& _SERIAL);
int ledNodeLoopIf(RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL);
void sendPingResponse(Ping const&  resp, RF24& radio);
