
#include "Arduino.h"
#include "Components.h"
#include "Messages.h"
#include "Loop.h"

#if 0
byte remote_address[3][5] = {
  {0xAB, 0xBA, 0xAC, 0xDC, 0x1},
  {0xAB, 0xBA, 0xAC, 0xDC, 0x2},
  {0xAB, 0xBA, 0xAC, 0xDC, 0x3}
};
#else
uint8_t remote_address[3][5] = {
  {0xAA, 0xBB, 0xCC, 0xDD, 0x1},
  {0xAA, 0xBB, 0xCC, 0xDD, 0x2},
  {0xAA, 0xBB, 0xCC, 0xDD, 0x3}
};
#endif
Ping noResp(0,0);
Ping getPingResponse()
{
  radio.startListening();
  bool timeout = false;
  TIME const started_waiting_at = micros();
  while ( !radio.available() ){ // While nothing is received
    if (micros() - started_waiting_at > 2000 ){ // If waited longer than 200ms, indicate timeout and exit while loop
      //Serial.println("timeout");
      return noResp;
    }
  }
  Ping resp(0,0);
  radio.read( &resp, sizeof(resp) );
  return resp;
}
struct Stats
{
  Stats(): rounds(0), attempts(0), ok(0), spent(0) {}
  unsigned int rounds;
  unsigned int attempts;
  unsigned int ok;
  unsigned int nok;
  TIME spent;
};
Stats stats;
const unsigned int MAX_ATTEMPTS = 10;
Ping onePingRound(unsigned int const receiver, unsigned int const rounds, TIME& timeSpent, unsigned int& attempts)
{
    radio.openWritingPipe(remote_address[receiver]); // Write to device address '2Node'
    TIME const timeStart = millis();
    do
    {
      attempts++;
      sendPingRequest(rounds);
      #if 1
      Ping const resp = getPingResponse();
      if (resp.header.msgId == PING_RESPONSE)
      {
        Serial.println("resp: ");
        timeSpent = millis()-timeStart;
        return resp;
      }
      #else
      timeSpent = millis()-timeStart;
      return noResp;
      #endif
    }
    while(attempts < MAX_ATTEMPTS);
    return noResp;
}

TIME prevLog = 0;
void loop()
{
    TIME timeSpent = -1;
    unsigned int attempts = 0;
    Ping const resp = onePingRound(0, stats.rounds, timeSpent, attempts);
    //Ping const resp2 = onePingRound(1, stats.rounds, timeSpent, attempts);
    //Ping const resp3 = onePingRound(2, stats.rounds, timeSpent, attempts);


    if (attempts < MAX_ATTEMPTS && timeSpent != -1)
    {
      if (resp.header.transactionId && (resp.header.transactionId == stats.rounds))
      {
        stats.ok++;
      }
      else
      {
        stats.nok++;
      }
    }
    stats.attempts += attempts;
    stats.spent += timeSpent;
    stats.rounds++;
    if (millis() - prevLog >= 5000)
    {
      prevLog = millis();
      Serial.print(prevLog);
      Serial.print(", rounds: "); Serial.print(stats.rounds);
      Serial.print(", ok:");Serial.print(stats.ok);
      Serial.print(", nok:");Serial.print(stats.nok);
      Serial.print(", attempts: "); Serial.print(stats.attempts);
      Serial.print(", spent: "); Serial.println(stats.spent);
    }
}
