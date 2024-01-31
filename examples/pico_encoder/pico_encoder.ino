#include <Wire.h>
#include <pico_encoder.h>

//#define SEESAW_ADDR          0x36

void setup() {
  Serial.begin(115200);
  delay(5000);
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire.begin();
  while (!Serial) delay(10);

  // Start Encoder
  startEncoder();

}

void loop(){
  
  positionOffset = checkPosition();
  if (positionOffset != 0) {
    //Serial.println(encoderPosition);  
    Serial.println(positionOffset);  
  }
  

  // don't overwhelm serial port
  delay(10);
}
