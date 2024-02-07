#include "FastLED.h"
CRGB leds[30];
void setup() {
FastLED.addLeds<NEOPIXEL, 6>(leds, 30); 
}
void loop() { 
  static uint8_t hue = 0;
  FastLED.showColor(CHSV(hue++, 200, 200)); 
  delay(100);
}
