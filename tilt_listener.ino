
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#if !defined __AVR_ATtiny85__ && !defined __AVR_ATtiny84__
#include <SPI.h>
#endif
#include "RF24.h"
#include "Messages.h"
#include "JeeLib.h"

#define DEBUGGING

#ifdef DEBUGGING
#if defined __AVR_ATtiny85__ || defined __AVR_ATtiny84__
#include <TinyDebugSerial.h>
TinyDebugSerial mySerial = TinyDebugSerial();
#define _SERIAL mySerial
#else
#define _SERIAL Serial
#endif
#endif

#include "DualMotors.h"

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
#if defined __AVR_ATtiny85__
#define CE_PIN 9
#define CSN_PIN 9
#elif defined __AVR_ATtiny84__
#error TODOO
#else
#define CE_PIN 9
#define CSN_PIN 10
#endif
RF24 radio(CE_PIN,CSN_PIN);
/**********************************************************/
byte my_address[7] = "Listnr";
byte remote_address[7] = "Remote";


struct Tracer
{
  const char* name;
  int failed_writes;
  int wrong_message;
  int pitch;
  int roll;
  int button;
  int timeouts;
  Tracer(const char* n): 
   name(n),
   failed_writes(0),
   wrong_message(0),
   pitch(0),
   roll(0),
   button(0),
   timeouts(0)
   {}
   void log(const long timeNow) const
   {
    #ifdef DEBUGGING
        _SERIAL.print(name);
        _SERIAL.print(F(", time:"));
        _SERIAL.print(timeNow);
        _SERIAL.print(F(", failed writes: "));
        _SERIAL.print(failed_writes);
        _SERIAL.print(F(", timeouts: "));
        _SERIAL.print(timeouts);    
        _SERIAL.print(F(", wrong: "));
        _SERIAL.print(wrong_message);
        _SERIAL.print(F(", pitch: "));
        _SERIAL.print(pitch);
        _SERIAL.print(F(", roll: "));
        _SERIAL.print(roll);
        _SERIAL.print(F(", button: "));
        _SERIAL.println(button);    
    #endif
    }
};
#define headLights 2
#define MO_R_E_PIN 5
#define MO_R_P1_PIN 4
#define MO_R_P2_PIN 3
#define MO_L_E_PIN 6
#define MO_L_P1_PIN 8
#define MO_L_P2_PIN 7
Motor motorLeft("Left", MO_L_E_PIN, MO_L_P1_PIN, MO_L_P2_PIN);
Motor motorRight("Right", MO_R_E_PIN, MO_R_P1_PIN, MO_R_P2_PIN);
DualMotors motors(motorLeft, motorRight);

void setup() {
  #ifdef DEBUGGING
  _SERIAL.begin(9600);
  _SERIAL.println("Start-up");
  #endif
  radio.begin();
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses

  // Start the radio listening for data
  radio.openReadingPipe(1,my_address);
  radio.openWritingPipe(remote_address);
  motors.init();
  pinMode(headLights, OUTPUT);
  digitalWrite(headLights, LOW);
}

void write_response(Tracer& tracer, int transactionId)
{
    Response response(TILT_RESPONSE, transactionId);
    if (!radio.write( &response, sizeof(response) ))
     {
       tracer.failed_writes++;
     }  
}
int read_request(Tracer& tracer)
{
        TiltRequest request(TILT_REQUEST);
        radio.read( &request, sizeof(request) );
        if (request.header.msgId != TILT_REQUEST)
        {
          tracer.wrong_message++;
        }
        tracer.pitch = request.tilt.pitch;
        tracer.roll = request.tilt.roll;
        tracer.button = request.button;
        
        return request.header.transactionId;
}
bool communicateWithNode(const int respMsgId, Tracer& tracer)
{
    radio.startListening();  
    unsigned long const started_waiting_at = micros();
    boolean timeout = false;
    boolean retValue = false;

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
      int const transactionId = read_request(tracer);
      radio.stopListening(); 
      write_response(tracer, transactionId);
      retValue = true;
    }
    
    return retValue;
}

ISR(WDT_vect) { Sleepy::watchdogEvent(); } 

TIME timePrevMsgServed = 0;
TIME timePrevAliveLogged = 0;
const TIME communicationBreakdownThreshold = 300;
const TIME activationThreshold = 1000;
const TIME deactivationThreshold = 1000;
const int PWR_SAVE_OFF = 0;
const int PWR_SAVE_ON = 1;
int powerSaveMode = PWR_SAVE_OFF;

void loop() {
    motorLeft.loggingOff();
    motorRight.loggingOff();
    TIME const timeNow = millis();
    if (powerSaveMode == PWR_SAVE_OFF)
    {
      Tracer tiltTracer("TILT");
      bool const msgReceived = communicateWithNode(TILT_RESPONSE, tiltTracer);
      //tiltTracer.log(timeNow);
  
      if (msgReceived)
      {
         timePrevMsgServed = timeNow;
        const int forwardWise = tiltTracer.roll;
        const int leftWise = tiltTracer.pitch;
        #if 1
        if (tiltTracer.button)
        {
        #ifdef DEBUGGING
        _SERIAL.print(forwardWise);
        _SERIAL.print(" ");
        _SERIAL.println(leftWise);
        #endif
          motorLeft.loggingOn();
          motorRight.loggingOn();
          digitalWrite(headLights, HIGH);
        }
        else
        {
          digitalWrite(headLights, LOW);
        }
        #endif
        motors.go(forwardWise, leftWise);
        // MotorControlOrders orders(forwardWise, leftWise);
        //motors.go(orders);
      }
      if (timeNow - timePrevMsgServed > communicationBreakdownThreshold)
      {
       motors.stop();
      }
    }
    #if 0
    else
    {
      #ifdef DEBUGGING
      _SERIAL.println("going to sleep now...");
      #endif  
      Sleepy::loseSomeTime(500);
    }
    #endif
    #ifdef DEBUGGING
    if (timeNow - timePrevAliveLogged > 5000)
    {
      timePrevAliveLogged = timeNow;
      _SERIAL.println("still alive!");
    }
    #endif

    #if 0
    if ((powerSaveMode == PWR_SAVE_ON) && (timeNow - timePrevMsgServed > activationThreshold))
    {
      #ifdef DEBUGGING
      _SERIAL.println("out of power save mode");
      #endif  
      timePrevMsgServed = timeNow;
      powerSaveMode = PWR_SAVE_OFF;
    }
    if ((powerSaveMode == PWR_SAVE_OFF) && (timeNow - timePrevMsgServed > deactivationThreshold))
    {
      #ifdef DEBUGGING
      _SERIAL.println("in power save mode");
      #endif
      timePrevMsgServed = timeNow;
      powerSaveMode = PWR_SAVE_ON;
    }
    #endif
}

