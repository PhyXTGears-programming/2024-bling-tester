#include "pico_display.h"

void setup() {
  // put your setup code here, to run once:
  int short_delay = 200;
  int long_delay = 4000;
  Serial.begin(9600);
  Serial.println(F("Display Test"));

  // Initializer for a 1.9" 170x320 TFT display:
  tft.init(170, 320);          // Init ST7789 170x320
  tft.setRotation(1);

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  tft.setSPISpeed(120000000); // Max try 62,500,000

  tft.fillScreen(ST77XX_BLACK);

  Rectangle rect1(0, 0, 5, 50, 50, ST77XX_BLUE, ST77XX_YELLOW, "abc", ST77XX_RED, 2);
  rect1.Draw();
  delay(short_delay);
  rect1.Update("def");
  rect1.Draw();
  delay(short_delay);
  TxtString txt1(0, 65, "abc", 4, ST77XX_BLUE, ST77XX_BLACK);
  txt1.Draw();
  delay(short_delay);
  txt1.Update("def"); 
  txt1.Draw();
}

void loop() {
  // put your main code here, to run repeatedly:

}
