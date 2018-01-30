
#include "RF24.h"
#include "shared/RadioPins.h"
extern RF24 radio;

static const int switchPin = 8;

#ifdef ARDUINO_attiny
#include "TinyDebugSerial.h"
extern TinyDebugSerial _SERIAL;
#else
#define _SERIAL Serial
#endif

#ifdef BLUETOOTH_ON
#include "SoftwareSerial.h"
extern SoftwareSerial _BLUETOOTH;
#endif

#include "shared/Addresses.h"
extern int msgIdTable[maxNumberOfNodes];
