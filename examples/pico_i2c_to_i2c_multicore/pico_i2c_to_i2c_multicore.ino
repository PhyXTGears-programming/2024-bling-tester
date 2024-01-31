// Simple I2C controller and responder demo - Earle F. Philhower, III
// Using both onboard I2C interfaces, have one controller and one responder and 
// send data both ways between them. Connect GPIO0 to GPIO2, GPIO1 to GPIO3 on a single Pico

#include <Wire.h>
bool core0_status = false;
bool core1_status = false;

// Running on core0
void setup() {
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();
  Serial.begin(115200);
  delay(1000);
}

static char buff[100];
// Running on core0
void loop() {
    static int p;
    char b[90];

    // Write a value over I2C to the responder
    Serial.println();
    Wire.beginTransmission(0x30);
    sprintf(b, "pass %d", p++);
    Serial.println("Sending to Core 1");
    Wire.write(b, strlen(b));
    Wire.endTransmission();
    
    // Ensure the responder processing is done and print it out 
    delay(3000);
    Serial.printf("buff: '%s'\r\n", buff);

    // Read from the responder and print out
    Wire.requestFrom(0x30, 6);
    Serial.print("\nrecv: ' From Core 2:");
    while(Wire.available()) {
        Serial.print((char)Wire.read());
    }
    Serial.println("'");
    delay(1000);
}

// Running on core1
void setup1() {
  delay(1000);
  Wire1.setSDA(6);
  Wire1.setSCL(7);
  Wire1.begin(0x30);
  Wire1.onReceive(recv);
  Wire1.onRequest(req);
}

// Running on core1
void loop1() {
  //Serial.printf("C1: Stay on target...\n");
  //delay(500);
}

// These are called in an **INTERRUPT CONTEXT** which means NO serial port
// access (i.e. Serial.print is illegal) and no memory allocations, etc.

// Called when the I2C responder gets written to
void recv(int len) {
    int i;
    // Just stuff the sent bytes into a global the main routine can pick up and use
    for (i=0; i<len; i++) buff[i] = Wire1.read();
    buff[i] = 0;
}

// Called when the I2C responder is read from
void req() {
    static int ctr = 765;
    char buff[7];
    // Return a simple incrementing hex value
    sprintf(buff, "%06X", (ctr++) % 65535);
    Wire1.write(buff, 6);
}
