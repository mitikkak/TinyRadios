
#include "Components.h"
RF24 radio(CE_PIN,CSN_PIN);
#ifdef ARDUINO_attiny
TinyDebugSerial _SERIAL;
#endif
