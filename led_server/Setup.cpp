
#include "Arduino.h"
#include "Components.h"
#include "shared/Addresses.h"

void setup()
{
    _SERIAL.begin(9600);
    _SERIAL.println("begin");
    radio.begin(); // Start up the radio

    radio.setAutoAck(1); // Ensure autoACK is enabled
    radio.setRetries(15, 15); // Max delay between retries & number of retries
    radio.setPALevel(RF24_PA_LOW);
    pinMode(switchPin, OUTPUT);
}
