
#include "Arduino.h"
#include "Components.h"
#include "shared/Messages.h"
#include "Loop.h"

#if 0
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
#endif
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

TIME prevLog = 0;
int transactionId = 0;
void loop()
{
    TIME timeSpent = -1;
    unsigned int attempts = 0;
    const int switchStatus = digitalRead(switchPin);
    //if (switchStatus == LOW)
    {
        transactionId++;
        TIME const listenPeriod = 1000;
        TIME const sendPeriod = 100;
        RadioMode mode(listenPeriod, sendPeriod);
        bool const success1 = onePingRound(mode, 0, transactionId, timeSpent, attempts);
        Serial.print("node 1 transactionId: "); Serial.print(transactionId);
        Serial.print(", success: "); Serial.println(success1);
        transactionId++;
        bool const success2 = onePingRound(mode, 1, transactionId, timeSpent, attempts);
        Serial.print("node 2 transactionId: "); Serial.print(transactionId);
        Serial.print(", success: "); Serial.println(success2);
        transactionId++;
        bool const success3 = onePingRound(mode, 2, transactionId, timeSpent, attempts);
        Serial.print("node 3 transactionId: "); Serial.print(transactionId);
        Serial.print(", success: "); Serial.println(success3);
    }
#if 0
    //Ping const resp2 = onePingRound(1, stats.rounds, timeSpent, attempts);
    //Ping const resp3 = onePingRound(2, stats.rounds, timeSpent, attempts);
    {
      if (success)
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
#endif
}
