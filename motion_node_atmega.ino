
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
#include <Messages.h>

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
//bool radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
#define CE_PIN 9
#define CSN_PIN 10
RF24 radio(CE_PIN,CSN_PIN);
/**********************************************************/
byte master_address[7] = "Master";
byte my_address[7] = "A_Moti";

// Used to control whether this node is sending or receiving
//bool role = 0;

int const motionPin = 3;
void setup() {
  radio.begin(); // Start up the radio
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openWritingPipe(master_address); // Write to device address '2Node'
  radio.openReadingPipe(1,my_address); // Read on pipe 1 for device address '1Node'
  radio.startListening(); // Start listening
  pinMode(motionPin, INPUT);
}

void loop() {
  
  #if 1
  radio.startListening(); // Now, continue listening

    unsigned long started_waiting_at = micros(); // Set up a timeout period, get the current microseconds
  boolean timeout = false; // Set up a variable to indicate if a response was received or not

  while ( !radio.available() ){ // While nothing is received
    if (micros() - started_waiting_at > 2000/*200000*/ ){ // If waited longer than 200ms, indicate timeout and exit while loop
      timeout = true;
      break;
    }

  }

  if ( !timeout ){ // Describe the results
    MotionRequest request;
    radio.read( &request, sizeof(request) );
    radio.stopListening(); // First, stop listening so we can talk.
    MotionResponse response(request.header.transactionId);
    response.motion = digitalRead(motionPin);
    response.status = request.verify();
    radio.write( &response, sizeof(response) );
  }
  #endif

} // Loop

