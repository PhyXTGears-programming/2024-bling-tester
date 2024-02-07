
//#include "pixeltypes.h"
#include "FastLED.h"
#include <pico_relay.h>
#include <Wire.h>

#define COLOR_ORDER GRB
#define NUM_LEDS 30
#define BRIGHTNESS 75
#define DATA_PIN 16 // Robot data ouput pin
#define LED_TYPE   WS2811

int color = 0;
//  1 = RED. 
//  2 = GREEN. 
//  3 = BLUE.
CRGB leds[NUM_LEDS];

void setup() {
    Wire.setSDA(8);
    Wire.setSCL(9);
    Wire.begin();
    delay(200);
    FastLED.addLeds<LED_TYPE, DATA_PIN,COLOR_ORDER> (leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

}
  //CRGB purple     = CHSV( HUE_PURPLE, 255, 255);
//CRGB color[9] = {
// CRGB(0,150,0)        // green      0
//,CRGB(255,208,0)      // yellow     1
//,CRGB(196,0,255)      // purple     2
//,CRGB(28,0,224)       // blue       3
//,CRGB(0,255,251)      // lightBlue  4
//,CRGB(255 ,225 ,225); // white      5
//,CRGB(59  ,43  ,11 ); // brown      6
//,CRGB(227 ,0   ,255);//9
//};


    CRGB green      = CRGB(0   ,150 ,0  );
    CRGB yellow     = CRGB(255 ,208 ,0  );
    CRGB purple     = CRGB(196 ,0   ,255);//    3
    CRGB blue       = CRGB(28  ,0   ,224);//    4
    CRGB red        = CRGB(150 ,0   ,0  );//    5
    CRGB lightBlue  = CRGB(0   ,255 ,251);//    6
    CRGB white      = CRGB(255 ,225 ,225);//    7
    CRGB brown      = CRGB(89  ,73  ,41 );//    8
    CRGB pink       = CRGB(237 ,0   ,205);//    9



    
void loop() {
  Wire.requestFrom(0x30, 6);
  Serial.print("\nrecv: '");
  while(Wire.available()) {
        Serial.print((char)Wire.read());
  }
  FastLED.setBrightness(  BRIGHTNESS );
  for (int i = 0; i < NUM_LEDS; i++){
   if (color == 1){
    leds[i] = CRGB(green);
    
   }//end of if
   
   if (color == 2){
    leds[i] = CRGB(yellow);
   }//end of if
   
    if (color == 3){
    leds[i] = CRGB(purple);
   }//end of if
   
   if (color == 4){
    leds[i] = CRGB(blue);
    
   }//end of if
   
   if (color == 5){
    leds[i] = CRGB(green);
   }//end of if
   
   if (color == 6){
    leds[i] = CRGB(lightBlue);
   }//end of if
   
   if (color == 7){
    leds[i] = CRGB(white);
    
   }//end of if
   
   if (color == 8){
    leds[i] = CRGB(brown);
   }//end of if
   
    if (color == 9){
    leds[i] = CRGB(pink);
    }//end of if
   
    if (color == 10){
    leds[i] = CRGB(red);
    }//end of if
   
  }//end of for loop 
    FastLED.show();
    delay(1000);
    color++;
    if (color == 11){
          color = 1;
    }
}
