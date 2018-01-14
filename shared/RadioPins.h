
#pragma once

static const int CE_PIN = 9;
#ifdef ARDUINO_attiny
// dependent on RF24's tiny85 specific 3pin -feature
static const int CSN_PIN = CE_PIN;
#else
static const int CSN_PIN = 10;
#endif
