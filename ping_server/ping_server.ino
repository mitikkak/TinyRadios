
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
byte remote_address[8] = "p_client";
byte my_address[5] = {0xAB, 0xBA, 0xAC, 0xDC, 0x1};

const int ledPin = 4;
void setup() {
  _SERIAL.begin(9600);
  _SERIAL.println("begin");
  int const beginStatus = radio.begin(); // Start up the radio
  
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openWritingPipe(remote_address); // Write to device address '2Node'
  radio.openReadingPipe(1,my_address); // Read on pipe 1 for device address '1Node'
  //radio.setPALevel(RF24_PA_LOW);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

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
void loop() 
{
  #if 0
  TIME const timeNow = millis();
  if (timeNow - timePrev < 10) { return; }
  timePrev= timeNow;
  #endif
  Ping const req = getPingRequest();
  if (req.header.msgId == PING_REQUEST)
  {
    digitalWrite(ledPin, HIGH);
    reqs++;
    sendPingResponse(req);
  }
  
  if (millis() - prevLog >= 5000)
  {
    prevLog = millis();
    _SERIAL.print(prevLog);
    _SERIAL.print(", reqs: "); _SERIAL.print(reqs);
    _SERIAL.print(", timeouts: "); _SERIAL.println(timeouts);
    if (!reqs)
    {
      digitalWrite(ledPin, LOW);
    }
    reqs = 0;
    timeouts = 0;
  }
}

