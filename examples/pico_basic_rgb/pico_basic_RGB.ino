
#include "FastLED.h"

#define NUM_LEDS 7
#define DATA_PIN 15 // Data ouput pin
#define RELAY_PIN 2 // 

CRGB leds[NUM_LEDS];

void setup() {
    delay(200);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH); // Set high to supply power to LED string
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
}

void loop() {
    leds[0] = CRGB(55,0,0);
    leds[1] = CRGB(55,55,0);
    leds[2] = CRGB(0,55,0); 
    leds[3] = CRGB(0,55,55);
    leds[4] = CRGB(0,0,55);
    leds[5] = CRGB(55,0,55);
    leds[6] = CRGB(0,0,0);
    FastLED.show();
    delay(1000);
}
