//#include <Wire.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Standard SPI library
#include <Adafruit_seesaw.h>
#include "FastLED.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Standard SPI library
//#include <seesaw_neopixel.h>

#define SS_SWITCH        28
#define RELAY_PIN 2
#define SEESAW_ADDR          0x36
#define DATA_PIN 15 // Data ouput pin
#define NUM_LED 200
#define TFT_CS        17
#define TFT_RST       27
#define TFT_DC        22
#define TFT_MOSI      19  // Data out
#define TFT_SCLK      18  // Clock out
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

//print("test");
Adafruit_seesaw encoder;
CRGB leds[NUM_LED];
int32_t encoderStartPosition = 0;
int16_t positionOffset;

void setup() {

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Set high to supply power to LED string
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LED);  // GRB ordering is typical
  Serial.begin(115200);
  delay(1000);
  Wire.setSDA(0);
  Wire.setSCL(1);
//  while (!Serial) delay(10);  idk why this was here but i'm leaving it in case it's inportant fsr

  Serial.println("Looking for seesaw!");
  
  if (! encoder.begin(SEESAW_ADDR)) {
    Serial.println("Couldn't find seesaw on default address");
    while(1) delay(10);
  }
  Serial.println("seesaw started");
  Rectangle rect1(0,0,5,50,75,ST77XX_RED,ST77XX_GREEN,encoderPosition,ST77XX_BLACK,2);
/***
  uint32_t version = ((encoder.getVersion() >> 16) & 0xFFFF);
  if (version  != 4991){
    Serial.print("Wrong firmware loaded? ");
    serial.println(version);
    while(1) delay(10);
  }
  serial.println("Found Product 4991");
**/
  // get starting position
  encoderStartPosition = encoder.getEncoderPosition();

  Serial.println("Turning on interrupts");
  delay(10);
  encoder.setGPIOInterrupts((uint32_t)1 << SS_SWITCH, 1);
  encoder.enableEncoderInterrupt();
}

void loop(){
  
  static int32_t encoderPosition = 0;
  
  leds[0 + encoderPosition] = CRGB(55,0,0);
    
  encoderPosition = encoder.getEncoderPosition() - encoderStartPosition;

  if (encoderPosition < 0) {
    encoderPosition = 0;
  } else if (encoderPosition > NUM_LED - 1) {
    encoderPosition == NUM_LED - 1;
  }
  
    leds[0 + encoderPosition] = CRGB(0,55,0);
    FastLED.show();
    
  //if (! encoder.digitalRead(SS_SWITCH)) {
  //  serial.println("Button pressed!");
  //}

//  positionOffset = checkPosition();
//  if (positionOffset != 0) {
//    Serial.println(encoderPosition);  
//    Serial.println(positionOffset);  
//    (encoderPosition);  
//
//  }
    Serial.println(encoderPosition);

  // don't overwhelm serial port
  delay(10);
}


//uint16_t checkPosition() {
//  int16_t new_position = encoder.getEncoderPosition();
//  uint16_t positionOffset;
//  // did encoder move?
//  if (encoderPosition != new_position) {
//    
//    positionOffset = encoderPosition - new_position;
//    encoderPosition = new_position;
//  }
//  return positionOffset;
//  
//}



// Display has x0, y0 top left; x is horizontal increasing right; y is vertical increasing down

int short_delay = 200;
int long_delay = 4000;

class Rectangle
{
  // Class Member Variables
  // These are initialized at startup
  int16_t x0;               // Top left corner
  int16_t y0;               // Top left corner
  int8_t border;           // Border width
  int8_t width;            // Width of rectangle (x-direction)
  int8_t height;           // Height of rectangle (y-direction)
  uint16_t borderColor; // Border color
  uint16_t fillColor;   // Fill color
  int16_t cursorx;      // Cursor x
  int16_t cursory;      // Cursor y
  int8_t textSize;      // Text Size
  uint16_t textColor;   // Text color
  String screenText;    // Screen Text
  int8_t textLength;    // Screen Text length
  String tempString;

  // Constructor - creates a Rectangle with text
  // Initializes the member variables
<<<<<<< HEAD
class Rectangle {
  public:
    // Class Member Variables
    // These are initialized at startup
    int16_t x0;               // Top left corner
    int16_t y0;               // Top left corner
    int8_t border;           // Border width
    int8_t width;            // Width of rectangle (x-direction)
    int8_t height;           // Height of rectangle (y-direction)
    uint16_t borderColor; // Border color
    uint16_t fillColor;   // Fill color
    int16_t cursorx;      // Cursor x
    int16_t cursory;      // Cursor y
    int8_t textSize;      // Text Size
    uint16_t textColor;   // Text color
    String screenText;    // Screen Text
    int8_t textLength;    // Screen Text length
    String tempString;

    // Constructor - creates a Rectangle with text
    // Initializes the member variables
  public:
    Rectangle(int16_t x, int16_t y, int8_t b, int8_t w, int8_t h, uint16_t bc, uint16_t fc, String txt, uint16_t tc, int8_t ts)
    {
      x0 = x;
      y0 = y;
      border = b;
      height = h; //y-dimension
      width = w; //x-dimension
      borderColor = bc;
      fillColor = fc;
      screenText = String(txt);
      textLength = screenText.length();
      textSize = ts;
      textColor = tc;
    }
    void Draw() {
      tft.fillRect(x0, y0, width, height, borderColor);
      int16_t innerX = x0 + border;
      int16_t innerY = y0 + border;
      int16_t innerW = width - 2 * border;
      int16_t innerH = height - 2 * border;
      // Text for this object
      if (textSize == 1)
      {
        cursorx = floor((x0 + width / 2)) - floor((6.040 * textLength) / 2);
      }
      else if (textSize == 2)
      {
        cursorx = floor((x0 + width / 2)) - floor((11.5 * textLength) / 2);
      }
      else if (textSize == 3)
      {
        cursorx = floor((x0 + width / 2)) - floor((17 * textLength) / 2);
      }
      else if (textSize == 4)
      {
        cursorx = floor((x0 + width / 2)) - floor((22 * textLength) / 2);
      }
      else if (textSize == 5)
      {
        cursorx = floor((x0 + width / 2)) - floor((28 * textLength) / 2);
      }
      cursory = floor((y0 + height / 2)) - floor((9 * textSize) / 2);
      tft.setCursor(cursorx, cursory);
      tft.setTextSize(textSize);
      tft.setTextColor(textColor);
      tft.fillRect(innerX, innerY, innerW, innerH, fillColor);
      tft.println(screenText);
    }


    void Delete(uint16_t screenColor)
    {
      tft.fillRect(x0, y0, width, height, screenColor);
    }

    void Update(String txt) {
      screenText = txt;
    }

};


=======
  public:
  Rectangle(int16_t x,int16_t y,int8_t b,int8_t w,int8_t h,uint16_t bc,uint16_t fc,String txt,uint16_t tc, int8_t ts) 
  {
    x0 = x;
    y0 = y;
    border = b;
    height = h; //y-dimension
    width = w; //x-dimension
    borderColor = bc;
    fillColor = fc;
    screenText = String(txt);
    textLength = screenText.length();
    textSize = ts;
    textColor = tc;
    tft.fillRect(x0,y0,width,height,borderColor);
    int16_t innerX = x0 + border;
    int16_t innerY = y0 + border;
    int16_t innerW = width - 2 * border;
    int16_t innerH = height - 2 * border;
    // Text for this object
    if (textSize == 1) 
    {
      cursorx = floor((x0 + width/2)) - floor((6.040*textLength)/2);
    }
    else if (textSize == 2) 
    { 
      cursorx = floor((x0 + width/2)) - floor((11.5*textLength)/2);
    }
    else if (textSize == 3) 
    { 
      cursorx = floor((x0 + width/2)) - floor((17*textLength)/2);
    }
    else if (textSize == 4)
    { 
      cursorx = floor((x0 + width/2)) - floor((22*textLength)/2);
    }
    else if (textSize == 5) 
    { 
      cursorx = floor((x0 + width/2)) - floor((28*textLength)/2);
    }
    cursory = floor((y0 + height/2)) - floor((9*textSize)/2);
    tft.setCursor(cursorx,cursory);
    tft.setTextSize(textSize);
    tft.setTextColor(textColor);
    tft.fillRect(innerX,innerY,innerW,innerH,fillColor);
    tft.println(screenText);
  } // End Rectangle()

  void Delete(uint16_t screenColor)
  {
    tft.fillRect(x0,y0,width,height,screenColor);
  }

};

>>>>>>> f62eeca8c51266db1fc9ff85a0e1bb0accf9e6de
class Circle 
{
  // Class Member Variables
  // These are initialized at startup
  int16_t x0;               // Top left corner
  int16_t y0;               // Top left corner
  int8_t border;           // Border width
  int8_t radius;           // Radius of circle 
  uint16_t borderColor; // Border color
  uint16_t fillColor;   // Fill color
  int16_t cursorx;      // Cursor x
  int16_t cursory;      // Cursor y
  int8_t textSize;      // Text Size
  uint16_t textColor;   // Text color
  String screenText;    // Screen Text
  int8_t textLength;    // Screen Text length
  String tempString;
  
  // Constructor - creates a Circle
  // and initializes the member variables and state
  public:
  Circle(int16_t x,int16_t y,int8_t b,int8_t r,uint16_t bc,uint16_t fc,String txt,uint16_t tc, int8_t ts) 
  {
    x0 = x;
    y0 = y;
    border = b;
    radius = r;
    borderColor = bc;
    fillColor = fc;
    screenText = String(txt);
    textLength = screenText.length();
    textSize = ts;
    textColor = tc;
    tft.fillCircle(x0,y0,radius,borderColor);
    uint16_t innerR = radius - 2 * border;
    tft.fillCircle(x0,y0,innerR,fillColor);
    // Text for this object
    if (textSize == 1)
    {
      cursorx = x0 - floor((6.040*textLength)/2);
    }
    else if (textSize == 2)
    { 
      cursorx = x0 - floor((11.5*textLength)/2);
    }
    else if (textSize == 3) 
    { 
      cursorx = x0 - floor((17*textLength)/2);
    }
    else if (textSize == 4) 
    { 
      cursorx = x0 - floor((22*textLength)/2);
    }
    else if (textSize == 5) 
    { 
      cursorx = x0 - floor((28*textLength)/2);
    }
    cursory = y0 - floor((9*textSize)/2);
    tft.setCursor(cursorx,cursory);
    tft.setTextSize(textSize);
    tft.setTextColor(textColor);
    tft.println(screenText);

  }
  void Delete(uint16_t screenColor)
  {
    tft.fillCircle(x0,y0,radius,screenColor);
  }
  
};

class Vline
{
  // Class Member Variables
  // These are initialized at startup
  int16_t x0;            // Left/top end of line
  int16_t y0;            // Left/top end of line
  bool lineVert;        // Line Vert (True)
  int8_t lineWidth;     // Line width
  int16_t lineLength;    // Line length
  uint16_t lineColor;   // Line color
  
  // Constructor - creates a Line
  // and initializes the member variables and state
  public:
  Vline(int16_t x,int16_t y,int8_t w,int16_t l,bool lv, uint16_t lc) 
  {
    x0 = x;
    y0 = y;
    lineWidth = w;
    lineLength = l;
    lineVert = lv;
    lineColor = lc;
    if (lineVert == true)
    {
      tft.fillRect(x0,y0,lineWidth,lineLength,lineColor);
    }
    if (lineVert == false)
    {
      tft.fillRect(x0,y0,lineLength,lineWidth,lineColor);
    }
  }
  void Delete(uint16_t lineClear)
  {
    if (lineVert == true)
    {
      tft.fillRect(x0,y0,lineWidth,lineLength,lineClear);
    }
    if (lineVert == false)
    {
      tft.fillRect(x0,y0,lineLength,lineWidth,lineClear);
    }
  }
};
