
#include "Components.h"
#ifdef ARDUINO_attiny
TinyDebugSerial _SERIAL;
#endif
RF24 radio(CE_PIN,CSN_PIN);
RadioMode mode(RadioMode::infinite, 900);
