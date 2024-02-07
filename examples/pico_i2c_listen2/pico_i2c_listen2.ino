#include <Wire.h>

void setup() {
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.onReceive(recv);
  Wire.begin(0x30);
  Serial.begin(115200);
  delay(5000);
  Serial.println("I2C Scanning for input");
}

static char buff[100];
bool char_in = false;

void loop() {

    // Print out string from controller
    delay(1000);
    Serial.println("Waiting for input");  
    if (char_in == true){
      Serial.printf("buff: '%s'\r\n", buff); 
      char_in =  false;
    }
    

}
// Called when the I2C responder gets written to
void recv(int len) {
    int i;
    // Just stuff the sent bytes into a global that the main routine can pick up and use
    for (i=0; i<len; i++) buff[i] = Wire.read();
    buff[i] = 0;
    char_in =  true;
}
