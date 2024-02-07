
#include <Wire.h>

void setup() {
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();
  Serial.begin(115200);
  delay(3000);
  Serial.println("RoboRio");
}


void loop() {
    
    // Write a value over I2C from RoboRio to the responder
    char b[90];
    Wire.beginTransmission(0x30);
    Serial.println("Sending aaa");
    Wire.write("aaa");
    Wire.endTransmission();
    delay(3000);
    Wire.beginTransmission(0x30);
    Serial.println("Sending bbb");
    Wire.write("bbb");
    Wire.endTransmission();    
    delay(3000);
    Wire.beginTransmission(0x30);
    Serial.println("Sending ccc");
    Wire.write("ccc");
    Wire.endTransmission();
    delay(4550);

}
