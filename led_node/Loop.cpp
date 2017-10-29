
#include "Components.h"
#include "Blink.h"

TIME prevLog = 0;
int timeOuts = 0;
int msgs = 0;
TIME stateChanged = 0;

void sendPingResponse(Ping const&  req)
{
  radio.stopListening();
  Ping resp(PING_RESPONSE, req.header.transactionId);
  radio.write( &resp, sizeof(resp) );
}
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

TIME timePrev = 0;
TIME prevSwapped = 0;
bool isSending = false;
bool connectionEstablished = false;
TIME const CONNECTION_WAIT_PERIOD = 30000;
TIME const MODE_SWAP_PERIOD = 5000;
Blink blinker(5, 300);
Ping req(0,0);

bool swapMode(TIME const timeNow)
{
    if (timeNow - prevSwapped >= MODE_SWAP_PERIOD)
    {
        prevSwapped = timeNow;
        isSending = (isSending == true) ? false : true;
        return true;
    }
    return false;
}

#ifndef NODE_ALWAYS_ON
void loop() {
    TIME const timeNow = millis();
    if (!isSending)
    {
        //digitalWrite(sendIndicator, LOW);
        if (swapMode(timeNow))
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
        if (swapMode(timeNow))
        {
            _SERIAL.println("end of sending period");
            return;
        }
        sendPingResponse(req);
    }
}
#else
void loop() {

}
#endif
