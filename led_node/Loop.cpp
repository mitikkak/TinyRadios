
#include "Components.h"
#include "Blink.h"
#include "Constants.h"
#include "RadioMode.h"

TIME prevLog = 0;
int timeOuts = 0;
int msgs = 0;
TIME stateChanged = 0;

unsigned int reqs = 0;
unsigned int timeouts = 0;

Ping getPingRequest()
{
  radio.startListening();
  bool timeout = false;
  Ping req(0,0);
  #if 0
  TIME const started_waiting_at = micros();
  while ( !radio.available() ){ // While nothing is received
    if (micros() - started_waiting_at > 10000 ){ // If waited longer than 200ms, indicate timeout and exit while loop
      //_SERIAL.println("timeout");
      timeout = true;
      timeouts++;
      break;
    }
  }
  if (!timeout)
  #else
  if (radio.available())
  #endif
  {
    radio.read( &req, sizeof(req) );
  }
  return req;
}

RadioMode mode;


bool connectionEstablished = false;
TIME const CONNECTION_WAIT_PERIOD = 30000;
Blink blinker(5, 300, ledPin);
Ping req(0,0);



#include "LedNodeLoop.h"

#ifndef NODE_ALWAYS_ON
void loop() {
    TIME const timeNow = millis();
    if (!mode.isSending())
    {
        //digitalWrite(sendIndicator, LOW);
        if (mode.swap(timeNow))
        {
            _SERIAL.print(prevLog);
            _SERIAL.print(", reqs: "); _SERIAL.println(reqs);
            connectionEstablished = false;
            reqs = 0;
            digitalWrite(ledPin, LOW);
            return;
        }
        req = getPingRequest();
        if (req.header.msgId == PING_REQUEST)
        {
          if (!connectionEstablished)
          {
              blinker.begin(timeNow);
          }
          blinker.update(timeNow);
          connectionEstablished = true;
          reqs++;
        }
    }
    else
    {
        //digitalWrite(sendIndicator, HIGH);
        if (mode.swap(timeNow))
        {
            _SERIAL.println("end of sending period");
            return;
        }
        ledNodeLoopElse(req, radio);
    }
}
#else
void loop() {

}
#endif
