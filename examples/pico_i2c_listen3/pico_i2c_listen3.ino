#include <Wire.h>
#include <string>
#include <bits/stdc++.h>

void setup() {
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.onReceive(recv);
  Wire.begin(0x30);
  Serial.begin(115200);
  delay(5000);
  Serial.println("I2C Scanning for input");
}

static byte buff[100];
bool char_in = false;
std::string localString("");
void loop() {

    // Print out string from controller
    delay(1000);
    Serial.println("Waiting for input");  
    if (char_in == true){
      Serial.printf("buff: '%s'\r\n", buff); 
      
      //char* a(buff);
      //std::string s(a);
      //Serial.printf("localString: '%s'\r\n", s); 
      char_in =  false;
    }
    

}

void recv(int len) {
    int i;
    for (i=0; i<len; i++){
      buff[i] = Wire.read();
      //BYTE *Bytes = new BYTE[len];
      //memcpy(Bytes, ByteStr, len);
      //Serial.printf("localString: '%s'\r\n", ByteStr);
      localString = localString + std::to_string(buff[i]) ;
    }
    //std::string localString(buff.begin(), buff.end());
    Serial.printf("localString: '%s'\r\n", localString);
    //buff[i] = '\0';
    char_in =  true;

}
