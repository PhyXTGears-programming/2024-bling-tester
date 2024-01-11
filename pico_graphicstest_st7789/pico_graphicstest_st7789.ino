/**************************************************************************
  This is a library for several Adafruit displays based on ST77* drivers.

  This example works with the 1.14" TFT breakout
    ----> https://www.adafruit.com/product/4383
  The 1.3" TFT breakout
    ----> https://www.adafruit.com/product/4313
  The 1.47" TFT breakout
    ----> https://www.adafruit.com/product/5393
  The 1.54" TFT breakout
    ----> https://www.adafruit.com/product/3787
  The 1.69" TFT breakout
    ----> https://www.adafruit.com/product/5206
  The 1.9" TFT breakout
    ----> https://www.adafruit.com/product/5394
  The 2.0" TFT breakout
    ----> https://www.adafruit.com/product/4311

  Check out the links above for our tutorials and wiring diagrams.
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional).

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Standard SPI library

// Setup TFT display
#define TFT_CS        17
#define TFT_RST       27
#define TFT_DC        22
#define TFT_MOSI      19  // Data out
#define TFT_SCLK      18  // Clock out
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

float p = 3.1415926;
int short_delay = 200;

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("Hello! ST77xx TFT Test"));

  // Initializer for a 1.9" 170x320 TFT display:
  tft.init(170, 320);           // Init ST7789 170x320
  tft.setRotation(1);

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  tft.setSPISpeed(40000000);
  
  // large block of text
  tft.fillScreen(ST77XX_BLACK);
  Serial.println(F("Block of Text"));
  drawText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat.", ST77XX_YELLOW);
  delay(short_delay);

  // tft print function!
  Serial.println(F("Draw Text"));
  //drawVariousText();
  delay(short_delay);

  // a single pixel
  tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
  delay(short_delay);

  // line draw test
  //Serial.println(F("Draw Lines"));
  //drawLines(ST77XX_YELLOW);
  delay(short_delay);

  // optimized lines
  //Serial.println(F("Draw Fast Lines"));
  //drawFastLines(ST77XX_RED, ST77XX_BLUE);
  delay(short_delay);

  Serial.println(F("Draw Empty Rectangles"));
  //drawEmptyRectangles(ST77XX_GREEN);
  delay(short_delay);

  Serial.println(F("Draw Filled Rectangles"));
  //drawFilledRectangles(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(short_delay);
  
  tft.fillScreen(ST77XX_BLACK);
  Serial.println(F("Draw Filled Circles"));
  //drawFilledCircles(10, ST77XX_BLUE);
  Serial.println(F("Draw Empty Circles"));
  //drawEmptyCircles(10, ST77XX_WHITE);
  delay(short_delay);

  //draw_round_rectangles();
  delay(short_delay);

  Serial.println(F("Draw Triangles"));
  //drawTriangles();
  delay(short_delay);

  //mediabuttons();
  delay(short_delay);

  /*********
  Serial.println(F("Draw H, V, Slant Lines"));
  tft.fillScreen(ST77XX_BLACK);
  drawLine(10,20,50,75,ST77XX_GREEN);
  drawVertLine(50,75,100,ST77XX_RED);
  drawHorizLine(50,75,100,ST77XX_BLUE);
  ************/

  tft.fillScreen(ST77XX_BLACK);
  drawRectangle(0,0,10,75,75,ST77XX_RED,ST77XX_BLUE);
  drawCircle(125,0,5,50,ST77XX_RED,ST77XX_BLUE);


  Serial.println("done");
  delay(short_delay);
}

void loop() {
  //tft.invertDisplay(true);
  //delay(500);
  //tft.invertDisplay(false);
  //delay(500);
}

void drawVertLine(uint16_t x,uint16_t y,uint16_t h,uint16_t color) {
  tft.drawFastVLine(x, y, h, color);
}

void drawHorizLine(uint16_t x,uint16_t y,uint16_t w,uint16_t color) {
  tft.drawFastHLine(x, y, w, color);
}

void drawLine(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  tft.drawLine(x0, y0, x1, y1, color);
}

void drawLines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
    delay(0);
  }
}

void drawText(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void drawFastLines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void drawRectangle(uint16_t x0, uint16_t y0,uint16_t border,uint16_t height,uint16_t width,uint16_t borderColor,uint16_t fillColor){
  tft.fillRect(x0,y0,width,height,borderColor);
  uint16_t innerX = x0 + border;
  uint16_t innerY = y0 + border;
  uint16_t innerW = width - 2 * border;
  uint16_t innerH = height - 2 * border;
  tft.fillRect(innerX,innerY,innerW,innerH,fillColor);
}


void drawCircle(uint16_t x0, uint16_t y0,uint16_t border,uint16_t radius,uint16_t borderColor,uint16_t fillColor){
  tft.fillCircle(x0,y0,radius,borderColor);
  uint16_t innerR = radius - 2 * border;
  tft.fillCircle(x0,y0,innerR,fillColor);
}

void drawEmptyRectangles(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void drawFilledRectangles(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    //tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void drawFilledCircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void drawEmptyCircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void drawTriangles() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void draw_round_rectangles() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void drawVariousText() {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextSize(4);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}