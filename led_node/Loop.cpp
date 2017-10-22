
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
  #if 1
  TIME const started_waiting_at = micros();
  while ( !radio.available() ){ // While nothing is received
    if (micros() - started_waiting_at > 500000 ){ // If waited longer than 200ms, indicate timeout and exit while loop
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
bool connectionEstablished = false;
TIME const CONNECTION_WAIT_PERIOD = 30000;

void loop() {
#if 0
TIME const timeNow = millis();
if (timeNow - timePrev < 10) { return; }
timePrev= timeNow;
#endif
Ping const req = getPingRequest();
if (req.header.msgId == PING_REQUEST)
{
  if (!connectionEstablished)
  {
    doBlink(3, 300);
  }
  connectionEstablished = true;
  digitalWrite(ledPin, HIGH);
  reqs++;
  for (unsigned i = 0; i < 10; i++)
  {
    sendPingResponse(req);
  }
}

if (millis() - prevLog >= CONNECTION_WAIT_PERIOD)
{
  prevLog = millis();
  _SERIAL.print(prevLog);
  _SERIAL.print(", reqs: "); _SERIAL.print(reqs);
  _SERIAL.print(", timeouts: "); _SERIAL.println(timeouts);
  if (!reqs)
  {
    connectionEstablished = false;
    digitalWrite(ledPin, HIGH);
  }
  reqs = 0;
  timeouts = 0;
}                     // wait for a second
}
