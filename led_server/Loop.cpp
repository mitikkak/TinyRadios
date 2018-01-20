
#include "Arduino.h"
#include "Components.h"
#include "shared/Messages.h"
#include "Loop.h"

#ifdef BLUETOOTH_ON
int counter = 0;
const String resp = "RESP:";
boolean ledon = false;
void ledOn()
{
  //digitalWrite(led, HIGH);
  //delay(10);
}
void ledOff()
{
  //digitalWrite(led, LOW);
  //delay(10);
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
  if(string == "TO")
  {
    counter++;
    char cnt_str_buffer[10] = {0};
    itoa(counter, cnt_str_buffer, 10);
    resp += cnt_str_buffer;
    resp += ";";

    _BLUETOOTH.print(resp + "#"); //debug
    ledOn();
    ledon = true;
  }
  if(string =="TF")
  {
     counter = 0;
     resp = "RESP:";
     ledOff();
     ledon = false;
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

TIME prevLog = 0;
int transactionId = 0;
int node = 0;
int msgId = LED_ON_REQUEST;
void loop()
{
    TIME timeSpent = -1;
    {
        transactionId++;
        TIME const listenPeriod = 1000;
        TIME const sendPeriod = 100;
        RadioMode mode(listenPeriod, sendPeriod);
        unsigned int respTrId = 0;

        bool const success = onePingRound(mode, node, transactionId, timeSpent, respTrId, msgId);
        _SERIAL.print("node "); _SERIAL.print(node); _SERIAL.print("transactionId: "); _SERIAL.print(transactionId);
        _SERIAL.print("/");_SERIAL.print(respTrId);
        _SERIAL.print(", success: "); _SERIAL.println(success);
        if (success)
        {
            if (node < 2)
            {
                node++;
            }
            else
            {
                node = 0;
                msgId = (msgId == LED_ON_REQUEST) ? LED_OFF_REQUEST : LED_ON_REQUEST;
            }

        }
    }
}
#endif
