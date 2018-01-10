#pragma once

#include "RadioMode.h"
#ifdef ARDUINO_attiny
#include "TinyDebugSerial.h"
#endif
#include "RF24.h"

void ledNodeLoop();
void ledNodeLoopElse(RF24& radio, RadioMode& mode, const int transactionId, TIME const timeNow);
int ledNodeLoopIf(RadioMode& mode, TIME const timeNow);
void sendPingResponse(Ping const&  resp, RF24& radio);
