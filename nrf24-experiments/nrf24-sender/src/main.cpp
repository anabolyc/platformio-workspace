#include "main.h"
#include "RF24.h"

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 1;

RF24 radio(NRF_CE, NRF_CSN);
/**********************************************************/

SoftwareSerial _Serial(SERIAL_RX, SERIAL_TX);

byte addresses[][6] = {"1Node", "2Node"};

// Used to control whether this node is sending or receiving
// 1 = PING OUT
// 0 = PONG BACK
bool role = 1;

void setup()
{
  _Serial.begin(SERIAL_SPEED);
  _Serial.println(F("RF24/examples/GettingStarted"));
  _Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing and reading pipe on each radio, with opposite addresses
  if (radioNumber)
  {
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1, addresses[0]);
  }
  else
  {
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
  }

  //pinMode(SENS_PIN, INPUT);
  // Start the radio listening for data
  radio.startListening();
}

void loop()
{

  radio.printDetails();

  /****************** Ping Out Role ***************************/
  if (role == 1)
  {

    radio.stopListening(); // First, stop listening so we can talk.

    _Serial.print(F("Now sending: "));
    unsigned long start_time = micros(); // Take the time, and send it.  This will block until complete
    //uint8_t start_time = analogRead(SENS_PIN);
    _Serial.println(start_time);
    if (!radio.write(&start_time, sizeof(unsigned long)))
    {
      _Serial.println(F("failed"));
    }

    // radio.startListening();                                    // Now, continue listening

    // unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    // boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not

    // while ( ! radio.available() ){                             // While nothing is received
    //   if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
    //       timeout = true;
    //       break;
    //   }
    // }

    // if ( timeout ){                                             // Describe the results
    //     _Serial.println(F("Failed, response timed out."));
    // }else{
    //     unsigned long got_time;                                 // Grab the response, compare, and send to debugging spew
    //     radio.read( &got_time, sizeof(unsigned long) );
    //     unsigned long end_time = micros();

    //     // Spew it
    //     _Serial.print(F("Sent "));
    //     _Serial.print(start_time);
    //     _Serial.print(F(", Got response "));
    //     _Serial.print(got_time);
    //     _Serial.print(F(", Round-trip delay "));
    //     _Serial.print(end_time-start_time);
    //     _Serial.println(F(" microseconds"));
    // }

    // Try again 1s later
    delay(1000);
  }

  /****************** Pong Back Role ***************************/

  if (role == 0)
  {
    unsigned long got_time;

    if (radio.available())
    {
      // Variable for the received timestamp
      while (radio.available())
      {                                               // While there is data ready
        radio.read(&got_time, sizeof(unsigned long)); // Get the payload
      }

      radio.stopListening();                         // First, stop listening so we can talk
      radio.write(&got_time, sizeof(unsigned long)); // Send the final one back.
      radio.startListening();                        // Now, resume listening so we catch the next packets.
      _Serial.print(F("Sent response "));
      _Serial.println(got_time);
    }
  }

  /****************** Change Roles via _Serial Commands ***************************/

  if (_Serial.available())
  {
    char c = toupper(_Serial.read());
    if (c == 'T' && role == 0)
    {
      _Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      role = 1; // Become the primary transmitter (ping out)
    }
    else if (c == 'R' && role == 1)
    {
      _Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
      role = 0; // Become the primary receiver (pong back)
      radio.startListening();
    }
  }

} // Loop
