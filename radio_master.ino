
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
#include "Messages.h"
//#include "Tracer.h"

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool const radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(9,10);
/**********************************************************/
#if 0
typedef uint64_t NodeAddress;
NodeAddress my_address = 0x1122334455667788LL;
NodeAddress node_address = 0x8877665544332211LL;
#else
byte my_address[7] = "Master";
byte node_address[7] = "A_Node";
#endif

struct Tracer
{
  const char* name;
  int failed_writes;
  int wrong_message;
  int tr_id_ok;
  int motion;
  int ledError;
  int timeouts;
  Tracer(const char* n): 
   name(n),
   failed_writes(0),
   wrong_message(0),
   tr_id_ok(0),
   motion(0),
   ledError(0),
   timeouts(0)
   {}
   void log(const long timeNow) const
   {
        Serial.print(name);
        Serial.print(F(", time:"));
        Serial.print(timeNow);
        Serial.print(F(", failed writes: "));
        Serial.print(failed_writes);
        Serial.print(F(", timeouts: "));
        Serial.print(timeouts);    
        Serial.print(F(", wrong: "));
        Serial.print(wrong_message);
        Serial.print(F(", tr_id_ok: "));
        Serial.print(tr_id_ok);
        Serial.print(F(", ledError: "));
        Serial.print(ledError);
        Serial.print(F(", motion: "));
        Serial.println(motion);    
    }
};

void setup() {
  Serial.begin(115200);
  radio.begin();
  uint8_t const autoAckStatus = radio.setAutoAck(1); // Ensure autoACK is enabled
  Serial.print("autoAck : ");
  Serial.println(autoAckStatus, HEX);
  radio.setRetries(15,15); // Max delay between retries & number of retries
  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses

  // Start the radio listening for data
  radio.openReadingPipe(1,my_address);
  //radio.startListening();
}

//Tracer motionTracer("MOTION");
//Tracer ledTracer("LED");
Request motion_request(MOTION_REQUEST);
Request ledRequest(LED_REQUEST);

void write_request(Tracer& tracer, Request& request)
{
    request.header.transactionId++;
    //tracer.num_of_msg++;                          
     if (!radio.write( &request, sizeof(request) ))
     {
       tracer.failed_writes++;
     }  
}
bool read_response(Tracer& tracer, int const respMsgId, const int transactionId, const LedLevel led)
{
        Response response(0, 0);
        radio.read( &response, sizeof(response) );
        if (response.header.msgId != respMsgId)
        {
          tracer.wrong_message++;
        }
        //else
        //{
        //  tracer.right_message++;
        //}
        if (response.header.transactionId == transactionId)
        {
          tracer.tr_id_ok++;
        }
        if (response.motion)
        {
          tracer.motion++;
        }
        if (response.led != led) tracer.ledError++;
        return response.motion;
}
bool communicateWithNode(const int respMsgId, Tracer& tracer, Request& request, const int node)
{
    bool motion = false;
    radio.stopListening(); 
    
    radio.openWritingPipe(node_address);
    write_request(tracer, request);
    radio.startListening();  
    unsigned long const started_waiting_at = micros();
    boolean timeout = false;

    while ( ! radio.available() ){
      if (micros() - started_waiting_at > 20000 )
      {
          timeout = true;
          break;
      }      
    }
        
    if ( timeout ){tracer.timeouts++;}
    else
    {
      motion = read_response(tracer, respMsgId, request.header.transactionId, request.led);
    }
    return motion;
}

TIME prevLedStateChange = 0;
void changeLedNode(const int node, LedLevel const next, const TIME timeNow)
{
      prevLedStateChange = timeNow;
      ledRequest.led = next;
      Tracer ledTracer("LED");
      (void) communicateWithNode(LED_RESPONSE, ledTracer, ledRequest, node);
      ledTracer.log(timeNow);  
}
LedLevel ledState = Led_OFF;

bool overThreshold(const TIME timeNow)
{
  return (timeNow >= (prevLedStateChange + 3000));
}

TIME prevActionAt = 0;
bool idleSomeMore()
{
  const TIME idleThreshold = 1000;
  const TIME timeNow = millis();
  return (timeNow - prevActionAt < idleThreshold) ? true : false;
}

void loop() {
    if (idleSomeMore()) return;
    Tracer motionTracer("MOTION");
    bool const motion = communicateWithNode(MOTION_RESPONSE, motionTracer, motion_request, 0);
    TIME const timeNow = millis();
    motionTracer.log(timeNow);

    if (ledState == Led_OFF && motion && overThreshold(timeNow) )
    {
      ledState = Led_LOW;
      changeLedNode(0, ledState, timeNow);
    }
    else if (ledState != Led_OFF && !motion && overThreshold(timeNow))
    {
      ledState = Led_OFF;
      changeLedNode(0, ledState, timeNow);
    }
    prevActionAt = millis();
    
} // Loop

