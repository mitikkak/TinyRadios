
#include "Arduino.h"
#include "Components.h"
#include "shared/Addresses.h"

void setup()
{
    Serial.begin(9600);
    Serial.println("begin");
    radio.begin(); // Start up the radio

    radio.setAutoAck(1); // Ensure autoACK is enabled
    radio.setRetries(15, 15); // Max delay between retries & number of retries
    radio.openReadingPipe(1, led_server_address); // Read on pipe 1 for device address '1Node'
    radio.setPALevel(RF24_PA_LOW);
    pinMode(switchPin, OUTPUT);
}
