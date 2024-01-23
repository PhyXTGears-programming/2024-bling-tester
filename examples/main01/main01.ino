//#include <Wire.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Standard SPI library
#include <Adafruit_seesaw.h>
#include "FastLED.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Standard SPI library
//#include <seesaw_neopixel.h>

#define SS_SWITCH        28
#define RELAY_PIN 2
#define SEESAW_ADDR          0x36
#define DATA_PIN 15 // Data ouput pin
#define NUM_LED 73
//print("test");
Adafruit_seesaw encoder;
CRGB leds[NUM_LED];
int32_t encoderStartPosition = 0;
int16_t positionOffset;

void setup() {
      pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH); // Set high to supply power to LED string
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LED);  // GRB ordering is typical
  Serial.begin(115200);
  delay(1000);
  Wire.setSDA(0);
  Wire.setSCL(1);
  while (!Serial) delay(10);

  Serial.println("Looking for seesaw!");
  
  if (! encoder.begin(SEESAW_ADDR)) {
    Serial.println("Couldn't find seesaw on default address");
    while(1) delay(10);
  }
  Serial.println("seesaw started");
/***
  uint32_t version = ((encoder.getVersion() >> 16) & 0xFFFF);
  if (version  != 4991){
    Serial.print("Wrong firmware loaded? ");
    serial.println(version);
    while(1) delay(10);
  }
  serial.println("Found Product 4991");
**/
  // get starting position
  encoderStartPosition = encoder.getEncoderPosition();

  Serial.println("Turning on interrupts");
  delay(10);
  encoder.setGPIOInterrupts((uint32_t)1 << SS_SWITCH, 1);
  encoder.enableEncoderInterrupt();
}

void loop(){
  
  static int32_t encoderPosition = 0;
  
  leds[0 + encoderPosition] = CRGB(55,0,0);
    
  encoderPosition = encoder.getEncoderPosition() - encoderStartPosition;

  if (encoderPosition < 0) {
    encoderPosition = 0;
  } else if (encoderPosition > NUM_LED - 1) {
    encoderPosition == NUM_LED - 1;
  }
  
    leds[0 + encoderPosition] = CRGB(0,55,0);
//    leds[1] = CRGB(55,55,0);
//    leds[2] = CRGB(0,55,0); 
//    leds[3] = CRGB(0,55,55);
//    leds[4] = CRGB(0,0,55);
//    leds[5] = CRGB(55,0,55);
//    leds[6] = CRGB(0,0,0);
    FastLED.show();
  //if (! encoder.digitalRead(SS_SWITCH)) {
  //  serial.println("Button pressed!");
  //}

//  positionOffset = checkPosition();
//  if (positionOffset != 0) {
//    Serial.println(encoderPosition);  
//    Serial.println(positionOffset);  
//    (encoderPosition);  
//
//  }
  
    Serial.println(encoderPosition);

  // don't overwhelm serial port
  delay(10);
}


//uint16_t checkPosition() {
//  int16_t new_position = encoder.getEncoderPosition();
//  uint16_t positionOffset;
//  // did encoder move?
//  if (encoderPosition != new_position) {
//    
//    positionOffset = encoderPosition - new_position;
//    encoderPosition = new_position;
//  }
//  return positionOffset;
//  
//}

//-\
// -\- \
//- - - <<<|==>-
//  / - / ^SPACESHIP^
//-/
