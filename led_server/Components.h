
#include "RF24.h"
extern RF24 radio;

static const int CE_PIN = 9;
static const int CSN_PIN = 10;
static const int switchPin = 8;

#ifdef ARDUINO_attiny
#include "TinyDebugSerial.h"
extern TinyDebugSerial _SERIAL;
#else
#define _SERIAL Serial
#endif
