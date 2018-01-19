
#include "led_node/Components.h"
#include "Blink.h"
#include "shared/Addresses.h"

#ifndef NODE_ALWAYS_ON
void setup() {
  _SERIAL.begin(9600);
  _SERIAL.println("begin");
  int const beginStatus = radio.begin(); // Start up the radio
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  if (node_id < maxNumberOfNodes)
  {
      radio.openReadingPipe(0,led_node_addresses[node_id]);
  }
  else
  {
      _SERIAL.print("node_id failure:"); _SERIAL.println(node_id);
  }
  radio.setPALevel(RF24_PA_LOW);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  //pinMode(sendIndicator, OUTPUT);
  //doBlink(3, 300);
  mode.start(RadioMode::listening, millis());
  radio.startListening();
}
#else
void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}
#endif
