
#include "Arduino.h"
#include "Components.h"
#include "shared/Messages.h"
#include "Loop.h"

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
int node = 0;
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
        bool const success = onePingRound(mode, node, transactionId, timeSpent, attempts);
        Serial.print("node "); Serial.print(node); Serial.print("transactionId: "); Serial.print(transactionId);
        Serial.print(", success: "); Serial.println(success);
        if (success)
        {
            node = (node < 2) ? node+1 : 0;
        }
    }
}
