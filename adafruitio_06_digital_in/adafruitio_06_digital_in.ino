// Adafruit IO Digital Input Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// digital pin 5
#define BUTTON_PIN 5
#define LED_PIN 2
#define PIEZEO_PIN 16
#define PHOTOCELL_PIN A0



// button state
bool current = false;
bool last = false;
unsigned long currTime;
unsigned long timeAtLastWater;
unsigned long wateringInterval = 0; //10 seconds, default watering interval
unsigned long alarmInterval = 5; //5 seconds
int toneFreq[] = { 262, 294, 330   // C4
                   }; // B4
int toneCount = sizeof(toneFreq)/sizeof(int);

int curLightVal = 0;
int lastLightVal = -1;



// set up the 'digital' and light feeds
AdafruitIO_Feed *digital = io.feed("digital");
AdafruitIO_Feed *light = io.feed("light");
AdafruitIO_Feed *waterIntervalFeed = io.feed("watering-interval");
AdafruitIO_Feed *analog = io.feed("analog");


void setup() {
  timeAtLastWater = - wateringInterval;
  // set button pin as an input
  pinMode(BUTTON_PIN, INPUT);

  // set LED pin as OUTPUT
  pinMode(LED_PIN, OUTPUT);

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while (! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  
//  light->onMessage(handleMessage);
  waterIntervalFeed->onMessage(setWaterInterval);

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // grab the current state of the button.
  // we have to flip the logic because we are
  // using a pullup resistor.
  if (digitalRead(BUTTON_PIN) == LOW){
    Serial.println("btn pressed");
    current = true;
    timeAtLastWater = millis()/1000;
  }
  else
    current = false;

  if(wateringInterval > 0){
    handleWaterChecks();
  }

  if (millis() - lastLightVal > 1000)
  {

    curLightVal = analogRead(PHOTOCELL_PIN);

    //Serial.println(current);

    analog->save(curLightVal);
    lastLightVal = millis();
  }

  // return if the value hasn't changed
  if (current == last)
    return;

  // save the current state to the 'digital' feed on adafruit io
  Serial.print("sending button -> ");
  Serial.println(current);
  digital->save(current);

  // store last button state
  last = current;

}


/**
 * Checks to see if the user needs to water plant.
 * If it needs watering, start alarm and activate light
 */
void handleWaterChecks(){
  
   currTime = millis()/1000;
     
   if(currTime > (timeAtLastWater + wateringInterval)){
    //plant needs to be watered
    
    if((currTime - (timeAtLastWater + wateringInterval))% alarmInterval == 0){
      //play alarm
      Serial.println("needs watering");
      for (int i=0; i < toneCount; ++i) {
        tone(PIEZEO_PIN, toneFreq[i]);
        delay(500);  // Pause for half a second.
      }
      // Loop down through all the tones from finish to start again.
      for (int i=toneCount-1; i >= 0; --i) {
        tone(PIEZEO_PIN, toneFreq[i]);
        delay(500);
      }
    }
    else {
       noTone(PIEZEO_PIN);
    }
     digitalWrite(LED_PIN, HIGH);
  }
  else{
    noTone(PIEZEO_PIN);
    digitalWrite(LED_PIN, LOW);
  }

}

void setWaterInterval(AdafruitIO_Data *data){
//    data->toInt()
    wateringInterval = data->toInt();
    Serial.println("New interval: ");
    Serial.print(wateringInterval);
    
}


// this function is called whenever an feed message is received
void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");

  if (data->toPinLevel() == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");

   // write the current state of the led
   digitalWrite(LED_PIN, data->toPinLevel());
 }


