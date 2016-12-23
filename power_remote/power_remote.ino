
#ifndef __AVR_ATtiny85__
//#error board not supported!
#endif

#include "RF24.h"
#include "Messages.h"
#ifndef __AVR_ATtiny85__
#define _SERIAL Serial
#else
#include <TinyDebugSerial.h>
TinyDebugSerial mySerial = TinyDebugSerial();
#define _SERIAL mySerial
#endif

#define CE_PIN 9
#ifdef __AVR_ATtiny85__
#define CSN_PIN 9
#else
#define CSN_PIN 10
#endif
RF24 radio(CE_PIN,CSN_PIN);
/**********************************************************/
byte switch_address[7] = "Switch";
byte my_address[7] = "Remote";


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
int prevState = 0xFFFF;
void loop() 
{
  TIME const timeNow = millis();
  if (timeNow - timePrev < 10) { return; }
  timePrev= timeNow;
  int const switchState = digitalRead(switchPin);
  if (switchState != prevState)
  {
    prevState = switchState;
    _SERIAL.print("switch: "); _SERIAL.println(switchState);
  }
  SwitchRequest request(SWITCH_REQUEST);
  request.set(switchState);  
  radio.write( &request, sizeof(request) ); 
}

