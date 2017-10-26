
#include "RF24.h"
extern RF24 radio;
static const byte my_address[8] = "p_client";

#define CE_PIN 9
#define CSN_PIN 10

#define _SERIAL Serial
