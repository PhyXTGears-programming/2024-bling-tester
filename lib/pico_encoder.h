
#include <Adafruit_seesaw.h>

Adafruit_seesaw encoder;


int32_t encoderPosition;
int16_t positionOffset;

#define SEESAW_ADDR          0x36


void startEncoder() {
  encoder.begin(SEESAW_ADDR);
  delay(100);
  encoderPosition = encoder.getEncoderPosition();
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
