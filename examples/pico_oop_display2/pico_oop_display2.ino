
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

// Display has x0, y0 top left; x is horizontal increasing right; y is vertical increasing down

int short_delay = 200;
int long_delay = 4000;

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
    } // End Rectangle init

    // Draw the rectangle on the screen
    void Draw() {
      // Fill the whole rectangle with border color
      tft.fillRect(x0, y0, width, height, borderColor); 

      // Create the inner fill rectangle, leaving the border visible
      int16_t innerX = x0 + border; 
      int16_t innerY = y0 + border;
      int16_t innerW = width - 2 * border;
      int16_t innerH = height - 2 * border;
      tft.fillRect(innerX, innerY, innerW, innerH, fillColor);

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
      tft.println(screenText);
    } // End rectangle draw


    void Delete(uint16_t screenColor)
    {
      tft.fillRect(x0, y0, width, height, screenColor);
    }

    // Updates the screen text
    void Update(String txt) {
      screenText = txt;
    } 

}; // End Rectangle class

class Circle {
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
    Circle(int16_t x, int16_t y, int8_t b, int8_t r, uint16_t bc, uint16_t fc, String txt, uint16_t tc, int8_t ts) { 
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
    } // End circle init

    // Draw the circle on the screen
    void Draw() {    
      // Fill the whole cicle with border color      
      tft.fillCircle(x0, y0, radius, borderColor);

      // Create the inner fill circle, leaving the border visible      
      uint16_t innerR = radius - 2 * border;
      tft.fillCircle(x0, y0, innerR, fillColor);
      
      // Text for this object
      if (textSize == 1)
      {
        cursorx = x0 - floor((6.040 * textLength) / 2);
      }
      else if (textSize == 2)
      {
        cursorx = x0 - floor((11.5 * textLength) / 2);
      }
      else if (textSize == 3)
      {
        cursorx = x0 - floor((17 * textLength) / 2);
      }
      else if (textSize == 4)
      {
        cursorx = x0 - floor((22 * textLength) / 2);
      }
      else if (textSize == 5)
      {
        cursorx = x0 - floor((28 * textLength) / 2);
      }
      cursory = y0 - floor((9 * textSize) / 2);
      tft.setCursor(cursorx, cursory);
      tft.setTextSize(textSize);
      tft.setTextColor(textColor);
      tft.println(screenText);
      } // End circle draw

    void Delete(uint16_t screenColor)
    {
      tft.fillCircle(x0, y0, radius, screenColor);
    }

    // Updates the screen text
    void Update(String txt) {
      screenText = txt;
    } 
    
}; // End circle class

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
    Vline(int16_t x, int16_t y, int8_t w, int16_t l, bool lv, uint16_t lc) {
      x0 = x;
      y0 = y;
      lineWidth = w;
      lineLength = l;
      lineVert = lv;
      lineColor = lc;
      } 

      
    // Draw the line on the screen
    void Draw() { 
      if (lineVert == true)
      {
        tft.fillRect(x0, y0, lineWidth, lineLength, lineColor);
      }
      if (lineVert == false)
      {
        tft.fillRect(x0, y0, lineLength, lineWidth, lineColor);
      }
    } // End draw line
    
    void Delete(uint16_t lineClear)
    {
      if (lineVert == true)
      {
        tft.fillRect(x0, y0, lineWidth, lineLength, lineClear);
      }
      if (lineVert == false)
      {
        tft.fillRect(x0, y0, lineLength, lineWidth, lineClear);
      }
    }
}; // End line class

void setup() {
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
  //Text txt1(10,10,3,ST77XX_RED);

  Rectangle rect1(0, 0, 5, 50, 75, ST77XX_RED, ST77XX_GREEN, "abc", ST77XX_BLACK, 2);
  rect1.Draw();
  delay(long_delay);
  rect1.Update("def");
  rect1.Draw();
  //Rectangle rect2(200,20,5,80,50,ST77XX_YELLOW,ST77XX_RED,"DEF",ST77XX_BLACK,3);  
  delay(short_delay);
  Vline line1(65,0,5,150,true,ST77XX_YELLOW); //true is vertical; false is horizontal
  delay(short_delay);
  Circle circl1(130,70,2,40,ST77XX_RED,ST77XX_BLUE,"tuv",ST77XX_WHITE,3);
  circl1.Draw();
  delay(long_delay);
  circl1.Update("xyz");
  circl1.Draw();  
  delay(long_delay);
    //rect1.Delete(ST77XX_BLACK);
    delay(short_delay);
    //line1.Delete(ST77XX_BLACK);
    delay(short_delay);
    //circl1.Delete(ST77XX_BLACK);
} // End Setup

void loop() {
}
