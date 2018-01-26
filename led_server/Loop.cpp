
#include "Arduino.h"
#include "Components.h"
#include "shared/Messages.h"
#include "Loop.h"
#include "shared/Addresses.h"

TIME prevLog = 0;
int transactionId = 0;
//int node = 0;
int msgIdTable[maxNumberOfNodes] = {LED_ON_REQUEST, LED_ON_REQUEST, LED_ON_REQUEST};
void orderOneNode(const int node = 0)
{
    TIME timeSpent = -1;
    transactionId++;
    TIME const listenPeriod = 1000;
    TIME const sendPeriod = 100;
    RadioMode mode(listenPeriod, sendPeriod);
    unsigned int respTrId = 0;
    int& msgId = msgIdTable[node];
    bool const success = onePingRound(mode, node, transactionId, timeSpent, respTrId, msgId);
    _SERIAL.print("node "); _SERIAL.print(node); _SERIAL.print("transactionId: "); _SERIAL.print(transactionId);
    _SERIAL.print("/");_SERIAL.print(respTrId);
    _SERIAL.print(", success: "); _SERIAL.println(success);
    if (success)
    {
        msgId = (msgId == LED_ON_REQUEST) ? LED_OFF_REQUEST : LED_ON_REQUEST;
    }
}

#ifdef BLUETOOTH_ON
boolean ledon = false;
void ledOn()
{
  Serial.println("led on");
  orderOneNode();
  //digitalWrite(led, HIGH);
  //delay(10);
}
void ledOff()
{
  Serial.println("led off");
  orderOneNode();
  //digitalWrite(led, LOW);
  //delay(10);
}
void toggleLed(const int node_idx)
{
  Serial.print("toggle led: "); Serial.println(node_idx);
  orderOneNode(node_idx);
}
void loop()
{
  String string = "";
  while(_BLUETOOTH.available() > 0)
  {
    char const command = ((byte)_BLUETOOTH.read());
    if(command == ':')
    {
      break;
    }
    else
    {
      string += command;
    }
    delay(1);
  }
  if (string == "") {return;}

  Serial.println(string);
  if(string == "SC")
  {
      String resp = "RESP:";
      for (unsigned node = 0; node < maxNumberOfNodes; node++)
      {
        char cnt_str_buffer[10] = {0};
        itoa(node, cnt_str_buffer, 10);
        resp += cnt_str_buffer;
        resp += ";";
      }
      _BLUETOOTH.print(resp + "#");
  }
  else if(string =="CL")
  {
  }
  else if (string.substring(0, 3) == "LED")
  {
      Serial.println(string.substring(3));
      int const node = string.substring(3).toInt();
      toggleLed(node);
  }

}
#else
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

void loop()
{
    {
        orderOneNode();
    }
}
#endif
