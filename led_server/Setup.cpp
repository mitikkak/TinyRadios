
#include "Arduino.h"
#include "Components.h"

void setup()
{
    _SERIAL.begin(9600);
    _SERIAL.println("begin");
    int const beginStatus = radio.begin(); // Start up the radio

    radio.setAutoAck(1); // Ensure autoACK is enabled
    radio.setRetries(15, 15); // Max delay between retries & number of retries
    radio.openReadingPipe(1, my_address); // Read on pipe 1 for device address '1Node'
    radio.setPALevel(RF24_PA_LOW);
}
