
#include "Components.h"
TinyDebugSerial _SERIAL = TinyDebugSerial();
RF24 radio(CE_PIN,CSN_PIN);
RadioMode mode(RadioMode::infinite, 900);
