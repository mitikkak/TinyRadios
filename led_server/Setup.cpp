
#include "Arduino.h"
#include "Components.h"
#include "shared/Addresses.h"
#include "shared/Messages.h"

void initMsgIdTable()
{
    for (int i = 0; i < maxNumberOfNodes; i++)
    {
        msgIdTable[i] = LED_ON_REQUEST;
    }
}

void setup()
{
#ifdef BLUETOOTH_ON
      _BLUETOOTH.begin(9600);
#endif
    _SERIAL.begin(9600);
    _SERIAL.println("begin");
    radio.begin(); // Start up the radio

    radio.setAutoAck(1); // Ensure autoACK is enabled
    radio.setRetries(15, 15); // Max delay between retries & number of retries
    radio.setPALevel(RF24_PA_LOW);
    pinMode(switchPin, OUTPUT);
    initMsgIdTable();
}
