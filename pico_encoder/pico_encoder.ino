/*
 * This example shows how to read from a seesaw encoder module.
 * The available encoder API is:
 *      int32_t getEncoderPosition();
        int32_t getEncoderDelta();
        void enableEncoderInterrupt();
        void disableEncoderInterrupt();
        void setEncoderPosition(int32_t pos);
 */
#include <Wire.h>
#include "Adafruit_seesaw.h"
//#include <seesaw_neopixel.h>

#define SS_SWITCH        28

#define SEESAW_ADDR          0x36

Adafruit_seesaw encoder;

int32_t encoderPosition;
int16_t positionOffset;

void setup() {
  Serial.begin(115200);
  delay(5000);
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
    Serial.println(version);
    while(1) delay(10);
  }
  Serial.println("Found Product 4991");
**/
  // get starting position
  encoderPosition = encoder.getEncoderPosition();

  Serial.println("Turning on interrupts");
  delay(10);
  encoder.setGPIOInterrupts((uint32_t)1 << SS_SWITCH, 1);
  encoder.enableEncoderInterrupt();
}

void loop(){
  
  //if (! encoder.digitalRead(SS_SWITCH)) {
  //  Serial.println("Button pressed!");
  //}

  positionOffset = checkPosition();
  if (positionOffset != 0) {
    Serial.println(encoderPosition);  
    Serial.println(positionOffset);  
  }
  

  // don't overwhelm serial port
  delay(10);
}


uint16_t checkPosition() {
  int16_t new_position = encoder.getEncoderPosition();
  uint16_t positionOffset;
  // did encoder move?
  if (encoderPosition != new_position) {
    
    positionOffset = encoderPosition - new_position;
    encoderPosition = new_position;
  }
  return positionOffset;
}
