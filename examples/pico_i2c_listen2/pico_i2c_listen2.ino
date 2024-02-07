 




// Simple I2C controller and responder demo - Earle F. Philhower, III
// Using both onboard I2C interfaces, have one controller and one responder and 
// send data both ways between them. Connect GPIO0 to GPIO2, GPIO1 to GPIO3 on a single Pico

#include <Wire.h>

void setup() {
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin(0x30);
  Wire.onReceive(recv);
  Wire.onRequest(req);
  Serial.begin(115200);
  delay(3000);
  Serial.println("\nI2C Scanner");
}

static char buff[100];
void loop() {
    static int p;
    char b[90];

    // Ensure the responder processing is done and print it out 
    delay(1000);
    Serial.printf("buff: '%s'\r\n", buff);

    // Read from the responder and print out
    Wire.requestFrom(0x30, 6);
    Serial.print("\nrecv: '");
    while(Wire.available()) {
        Serial.print((char)Wire.read());
    }
    Serial.println("'");
    delay(5000);
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
