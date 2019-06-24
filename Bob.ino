// Developer: Alexandros Gounis
// Info: This is meant to be paired with an iOS or an Android App
// App: BOB : Smart punchball device, 
// Developed at: Edinburgh Centre for Robotics
// United Kingdom, 2019

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    50
CRGB leds[NUM_LEDS];

int initialValue;
unsigned long starttime;
unsigned long endtime;
String roundTime = "07";
String difficulty;
String allData;
String score;
int roundTimeMils = 7000;
int total;
int correct = 0;
int thisRound;

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

// Adjust this number for the sensitivity of the 'click' force
// this strongly depend on the range! for 16G, try 5-10
// for 8G, try 10-20. for 4G try 20-40. for 2G try 40-80
#define CLICKTHRESHHOLD 80

void setup(void) {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  pinMode(2, OUTPUT);
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    // Couldn't start
    while (1);
  }
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

  // 0 = turn off click detection & interrupt
  // 1 = single click only interrupt output
  // 2 = double click only interrupt output, detect single click
  // Adjust threshhold, higher numbers are less sensitive
  //lis.setClick(2, CLICKTHRESHHOLD);

  Serial.begin(115200);  // initial the Serial
  Serial.setTimeout(0);
}


void loop() {

fill_solid( leds, 50, CRGB( 0, 0, 0) );
FastLED.show();

initialValue = random(1, 6);
thisRound = 0;

// Initial tone
  tone(2,440, 100);
  delay(100);
  tone(2,587.33, 100);
  delay(100);
  tone(2,880, 150);
  delay(1000);

  if (Serial.available())  {

    allData = Serial.readString();
    roundTime = allData.substring(1, 3);
    difficulty = allData.charAt(3);
    total = 0; correct = 0;    
    roundTimeMils = roundTime.toInt()*1000;
  }
  
// Illuminate the led zone from random value
  
if (initialValue == 1) {
  for (int idx = 0; idx <= 9; idx++) { 
            leds[idx] = CRGB (255, 0, 0);
            FastLED.show();
        }
  } else if (initialValue == 2) {
    for(int idx = 10; idx <= 19; idx++) { 
            leds[idx] = CRGB (255, 0, 0);
            FastLED.show();
        }
  } else if (initialValue == 3) {
    for(int idx = 20; idx <= 29; idx++) { 
            leds[idx] = CRGB (255, 0, 0);
            FastLED.show();
        }
  } else if (initialValue == 4) {
    for(int idx = 30; idx <= 39; idx++) { 
            leds[idx] = CRGB (255, 0, 0);
            FastLED.show();
        }
  } else {
    for(int idx = 40; idx <= 49; idx++) { 
            leds[idx] = CRGB (255, 0, 0);
            FastLED.show();
        }
  }

starttime = millis();
endtime = starttime;



while ((endtime - starttime) <=roundTimeMils) {
// code here
lis.read();      // get X Y and Z data at once

sensors_event_t event; 
lis.getEvent(&event);
  
  
  if  (initialValue == 1) {
    if ((event.acceleration.x < -2) && (event.acceleration.y > -7)) {
        correct += 1;
        thisRound = 1;
    }
  } else if  (initialValue == 2) {
    if ((event.acceleration.z < -6) && (event.acceleration.y > -6)) {
        correct += 1;
        thisRound = 1;
    } 
  } else if  (initialValue == 3) {
   if ((event.acceleration.y > -4.5) &&  (event.acceleration.z < -9)) {
        correct += 1;
        thisRound = 1;
    } 
  }  else if (initialValue == 4) {
    if ((event.acceleration.z > 0) && (event.acceleration.x > 5)){
        correct += 1;
        thisRound = 1;
    }
  } else {
    if ((event.acceleration.z > 0.3) && (event.acceleration.x < -2.2)) {
        correct += 1;
        thisRound = 1;
    }  
  }


  if (thisRound == 1) {
    fill_solid( leds, 50, CRGB( 0, 255, 0) );
    tone(2,587.33, 100);
    FastLED.show();
        delay(100);
        tone(2,880, 100);
        delay(100);
        tone(2,1108.73,100);
        delay(100);
        tone(2,1318.51,100);
        delay(500);

        

      delay(800);
break;
  }
  delay(200);
endtime = millis();
}


++total;
score = String(correct) + "/" + String(total);
   
Serial.print(score);
  

  return;
}
