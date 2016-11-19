
#ifdef __AVR_ATtiny84__
#error board not supported!
#endif

#include "RF24.h"
#include <Messages.h>
#include "MySerial.h"

#define CE_PIN 9
#ifdef __AVR_ATtiny85__
#define CSN_PIN 9
#else
#define CSN_PIN 10
#endif
RF24 radio(CE_PIN,CSN_PIN);
/**********************************************************/
byte remote_address[7] = "Remote";
byte my_address[7] = "Switch";

const int switchPin = 4;
void setup() {
  _SERIAL.begin(9600);
  _SERIAL.println("begin");
  int const beginStatus = radio.begin(); // Start up the radio
  
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openWritingPipe(remote_address); // Write to device address '2Node'
  radio.openReadingPipe(1,my_address); // Read on pipe 1 for device address '1Node'
  radio.startListening();
  pinMode(switchPin, OUTPUT);
  digitalWrite(switchPin, LOW);
}

TIME prevLog = 0;
int timeOuts = 0;
int msgs = 0;
int nextState = LOW;
void loop() 
{
  bool timeout = false;
  TIME const started_waiting_at = micros();
  while ( !radio.available() ){ // While nothing is received
    if (micros() - started_waiting_at > 20000 ){ // If waited longer than 200ms, indicate timeout and exit while loop
      //_SERIAL.println("timeout");
      timeOuts++;
      timeout = true;
      break;
    }

  }
  if (!timeout)
  {
    SwitchRequest request(0);
    radio.read( &request, sizeof(request) );
    msgs++;
    if (request.header.msgId == SWITCH_REQUEST)
    {
      nextState = (request.state == SwitchRequest::SWITCH_ON) ? HIGH : LOW;
      _SERIAL.print("new state: "); _SERIAL.println(nextState);
    }
  }
  digitalWrite(switchPin, nextState);
  if (millis() - prevLog >= 1000)
  {
    prevLog = millis();
     _SERIAL.print(timeOuts); _SERIAL.print("/"); _SERIAL.println(msgs);
  }
}

