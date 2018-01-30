
#include "Components.h"
RF24 radio(CE_PIN,CSN_PIN);
#ifdef ARDUINO_attiny
TinyDebugSerial _SERIAL;
#endif
#ifdef BLUETOOTH_ON
static constexpr int sw_serial_rx_pin{7};
static constexpr int sw_serial_tx_pin{6};
SoftwareSerial _BLUETOOTH(sw_serial_rx_pin, sw_serial_tx_pin);
#endif

extern int msgIdTable[maxNumberOfNodes]{};
