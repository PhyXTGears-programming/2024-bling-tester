// Simple I2C controller and responder demo - Earle F. Philhower, III
// Using both onboard I2C interfaces, have one controller and one responder and 
// send data both ways between them. Connect GPIO0 to GPIO2, GPIO1 to GPIO3 on a single Pico

#include <Wire.h>

void setup() {
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();

  delay(3000);
  Serial.println("\nI2C Scanner");
}

void loop() {
    // Read from the responder and print out
    Wire.requestFrom(0x30, 6);
    Serial.print("\nrecv: '");
    while(Wire.available()) {
        Serial.print((char)Wire.read());
    }
    Serial.println("'");
    delay(1000);
}
