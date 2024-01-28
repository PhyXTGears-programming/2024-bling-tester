#include <pico_encoder.h>
#include <pico_display.h>
#include <FastLED.h>
#include <pico_relay.h>
#include <Wire.h>

#define NUM_LEDS 200 //this should be enough...right?
#define DATA_PIN 15 // Data ouput pin
#define TFT_CS        17
#define TFT_RST       27
#define TFT_DC        22
#define TFT_MOSI      19  // Data out
#define TFT_SCLK      18  // Clock out

CRGB leds[NUM_LEDS];   
TxtString txt1(35, 35, "Position", ST77XX_BLUE, ST77XX_BLACK, 3);
//int positionOffset;

void setup() {
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire.begin();
  //positionOffset = checkPosition();
  Serial.begin(9600);
  startEncoder();
  //while(!Serial) delay(10);
  //delay(200);
  setupRelay();
  ledStringOn();
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical

  // Initializer for a 1.9" 170x320 TFT display:
  Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
  tft.init(170, 320);          // Init ST7789 170x320
  tft.setRotation(1);
  tft.setSPISpeed(120000000); // Max try 62,500,000
  tft.fillScreen(ST77XX_BLACK);
    
}//end of setup

void loop() {

    //leds[encoderPosition] = CRGB(0,55,0);
    //FastLED.show();
    positionOffset = checkPosition();
    if (positionOffset != 0) {

        //tft.fillScreen(ST77XX_BLACK);
        txt1.Update(String(positionOffset));
        txt1.Draw();
        delay(10);
        Serial.println(encoderPosition);  
        Serial.println(positionOffset);  

  } //end of if
}//end of loop
