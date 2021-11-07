
#include "Components.h"
RF24 radio(CE_PIN,CSN_PIN);
#ifdef ARDUINO_attiny
TinyDebugSerial _SERIAL;
#endif
#ifdef BLUETOOTH_ON
static constexpr int sw_serial_tx_pin{2};
static constexpr int sw_serial_rx_pin{3};
SoftwareSerial _BLUETOOTH(sw_serial_rx_pin, sw_serial_tx_pin);
#endif

extern int msgIdTable[maxNumberOfNodes]{};
