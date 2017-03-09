
#ifdef __AVR_ATtiny84__
#error board not supported!
#endif

#include "RF24.h"
#include "Messages.h"

#ifdef __AVR_ATtiny85__
#include <TinyDebugSerial.h>
TinyDebugSerial mySerial = TinyDebugSerial();
#define _SERIAL mySerial
#else
#define _SERIAL Serial
#endif

#define CE_PIN 9
#ifdef __AVR_ATtiny85__
#define CSN_PIN 9
#else
#define CSN_PIN 10
#endif
RF24 radio(CE_PIN,CSN_PIN);
/**********************************************************/
//byte remote_address[8] = {0xAA, 0xAA, 0xBB, 0xBB, 0xCC, 0xCC, 0xDD, 0xDD};
byte remote_address[5] = {0xAB, 0xBA, 0xAC, 0xDC, 0x1};
byte my_address[8] = "p_client";

void setup() {
  _SERIAL.begin(9600);
  _SERIAL.println("begin");
  int const beginStatus = radio.begin(); // Start up the radio
  
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openWritingPipe(remote_address); // Write to device address '2Node'
  radio.openReadingPipe(1,my_address); // Read on pipe 1 for device address '1Node'
  radio.setPALevel(RF24_PA_LOW);
}

TIME prevLog = 0;
int timeOuts = 0;
int msgs = 0;
TIME stateChanged = 0;

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

const unsigned int MAX_ATTEMPTS = 10;
Ping onePingRound(unsigned int const rounds, TIME& timeSpent, unsigned int& attempts)
{
  TIME const timeStart = millis();
  do
  {
    attempts++;
    sendPingRequest(rounds);
    #if 1
    Ping const resp = getPingResponse();
    if (resp.header.msgId == PING_RESPONSE)
    {
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
TIME timePrev = 0;
void loop() 
{
  #if 0
  TIME const timeNow = millis();
  if (timeNow - timePrev < 10) { return; }
  timePrev= timeNow;
  #endif
  TIME timeSpent = -1;
  unsigned int attempts = 0;
  Ping const resp = onePingRound(stats.rounds, timeSpent, attempts);
  

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
    stats.attempts += attempts;
    stats.spent += timeSpent;
  }
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

