
#include "Components.h"
#include "Blink.h"

#ifndef NODE_ALWAYS_ON
void setup() {
  _SERIAL.begin(9600);
  _SERIAL.println("begin");
  int const beginStatus = radio.begin(); // Start up the radio
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openWritingPipe(remote_address); // Write to device address '2Node'
  radio.openReadingPipe(1,my_address); // Read on pipe 1 for device address '1Node'
  radio.setPALevel(RF24_PA_LOW);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  //doBlink(3, 300);
}
#else
void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}
#endif
