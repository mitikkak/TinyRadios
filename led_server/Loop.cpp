
#include "Arduino.h"
#include "Components.h"
#include "Messages.h"

#if 0
byte remote_address[3][5] = {
  {0xAB, 0xBA, 0xAC, 0xDC, 0x1},
  {0xAB, 0xBA, 0xAC, 0xDC, 0x2},
  {0xAB, 0xBA, 0xAC, 0xDC, 0x3}
};
#else
byte remote_address[3][5] = {
  {0xAA, 0xBB, 0xCC, 0xDD, 0x1},
  {0xAA, 0xBB, 0xCC, 0xDD, 0x2},
  {0xAA, 0xBB, 0xCC, 0xDD, 0x3}
};
#endif
void sendPingRequest(unsigned int const rounds)
{
  radio.stopListening();
  Ping request(PING_REQUEST, rounds);
  radio.write( &request, sizeof(request) );
}
Ping noResp(0,0);
Ping getPingResponse()
{
  radio.startListening();
  bool timeout = false;
  TIME const started_waiting_at = micros();
  while ( !radio.available() ){ // While nothing is received
    if (micros() - started_waiting_at > 2000 ){ // If waited longer than 200ms, indicate timeout and exit while loop
      //_SERIAL.println("timeout");
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
Ping onePingRound(uint32_t const receiver, unsigned int const rounds, TIME& timeSpent, unsigned int& attempts)
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
        _SERIAL.println("resp: ");
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
      _SERIAL.print(prevLog);
      _SERIAL.print(", rounds: "); _SERIAL.print(stats.rounds);
      _SERIAL.print(", ok:");_SERIAL.print(stats.ok);
      _SERIAL.print(", nok:");_SERIAL.print(stats.nok);
      _SERIAL.print(", attempts: "); _SERIAL.print(stats.attempts);
      _SERIAL.print(", spent: "); _SERIAL.println(stats.spent);
    }
}
