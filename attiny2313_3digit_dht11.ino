/* SevSeg Counter Example
 
 Copyright 2017 Dean Reading
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 
 This example demonstrates a very simple use of the SevSeg library with a 4
 digit display. It displays a counter that counts up, showing deci-seconds.
 */
#include "DHT.h"

#define DHTPIN 12     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object

int buttonState = 1;  

void setup() {
  dht.begin();
  byte numDigits = 3;
  byte digitPins[] = {9, 10, 11};
  byte segmentPins[] = {1, 2, 3, 4, 5, 6, 7, 8};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = true; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(75);
}

void loop() {
  pinMode(A1, INPUT_PULLUP);
  buttonState = digitalRead(A1);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
    
  if(buttonState == LOW){
    sevseg.setNumber(h,1);
  }
  else{
    sevseg.setNumber(t-3,1);
  }  
  sevseg.refreshDisplay(); // Must run repeatedly
}
/// END ///
