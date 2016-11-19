
#ifndef __AVR_ATtiny85__
#error board not supported!
#endif

#include "RF24.h"
#include <Messages.h>
#include <TinyDebugSerial.h>
TinyDebugSerial mySerial = TinyDebugSerial();

#define CE_PIN 9
#define CSN_PIN 9
RF24 radio(CE_PIN,CSN_PIN);
/**********************************************************/
byte switch_address[7] = "Switch";
byte my_address[7] = "Remote";

#define _SERIAL mySerial

const int switchPin = 4;
void setup() {
  _SERIAL.begin(9600);
  _SERIAL.println("begin");
  int const beginStatus = radio.begin(); // Start up the radio
  
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openWritingPipe(switch_address); // Write to device address '2Node'
  radio.openReadingPipe(1,my_address); // Read on pipe 1 for device address '1Node'
  radio.stopListening();
  pinMode(switchPin, INPUT_PULLUP);
}

TIME timePrev = 0;
void loop() 
{
  TIME const timeNow = millis();
  if (timeNow - timePrev < 1000) { return; }
  timePrev= timeNow;
  int const switchState = digitalRead(switchPin);
  _SERIAL.print("switch: "); _SERIAL.println(switchState);
  SwitchRequest request(SWITCH_REQUEST);
  request.set(switchState);
  radio.write( &request, sizeof(request) ); 
}

