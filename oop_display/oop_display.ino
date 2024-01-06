
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

// Display has x0, y0 top left; x is increasing right; y is increasing down

int short_delay = 200;
int long_delay = 4000;

class Rectangle
{
  // Class Member Variables
  // These are initialized at startup
  int x0;               // Top left corner
  int y0;               // Top left corner
  int border;           // Border width
  int width;            // Width of rectangle (x-direction)
  int height;           // Height of rectangle (y-direction)
  uint16_t borderColor; // Border color
  uint16_t fillColor;   // Fill color
  int16_t cursorx;      // Cursor x
  int16_t cursory;      // Cursor y
  int8_t textSize;      // Text Size
  uint16_t textColor;   // Text color
  String screenText;    // Screen Text

  // Constructor - creates a Rectangle with text
  // Initializes the member variables
  public:
  Rectangle(int x,int y,int b,int h,int w,uint16_t bc,uint16_t fc,String txt,uint16_t tc, int ts)
  {
  x0 = x;
  y0 = y;
  border = b;
  height = h;
  width = w;
  borderColor = bc;
  fillColor = fc;
  screenText = String(txt);
  textSize = ts;
  textColor = tc;
  tft.fillRect(x0,y0,width,height,borderColor);
  int innerX = x0 + border;
  int innerY = y0 + border;
  int innerW = width - 2 * border;
  int innerH = height - 2 * border;
  tft.fillRect(innerX,innerY,innerW,innerH,fillColor);
  cursorx = x0 + 20;
  cursorx = y0 + 20;
  tft.setCursor(cursorx, cursory);
  tft.setTextSize(textSize);
  tft.setTextColor(textColor);
  tft.println(screenText);
  }

  void Delete(uint16_t screenColor)
  {
    tft.fillRect(x0,y0,width,height,screenColor);
  }
};

class Circle
{
  // Class Member Variables
  // These are initialized at startup
  int x0;               // Top left corner
  int y0;               // Top left corner
  int border;           // Border width
  int radius;           // Radius of circle 
  uint16_t borderColor; // Border color
  uint16_t fillColor;   // Fill color

  // Constructor - creates a Circle
  // and initializes the member variables and state
  public:
  Circle(int x, int y,int b,int r,uint16_t bc,uint16_t fc)
  {
  x0 = x;
  y0 = y;
  border = b;
  radius = r;
  borderColor = bc;
  fillColor = fc;
  tft.fillCircle(x0,y0,radius,borderColor);
  uint16_t innerR = radius - 2 * border;
  tft.fillCircle(x0,y0,innerR,fillColor);
  }
  
  void Delete(uint16_t screenColor)
  {
    tft.fillCircle(x0,y0,radius,screenColor);
  }
};

class Text
{
  // Class Member Variables
  // These are initialized at startup
  int x0;             // Cursor x
  int y0;             // Cursor y
  int textSize;       // Text Size
  uint16_t textColor; // Text color

  // Constructor - creates text
  // and initializes the member variables and state
  public:
  Text(int x, int y,int ts,uint16_t tc)
  {
  /************
  x0 = x;
  y0 = y;
  textSize = ts;
  textColor = tc;
  tft.setCursor(x0, y0);
  tft.setTextSize(textSize);
  tft.setTextColor(textColor);
  ****/
  }
  
  void Update(int x, int y,int ts,uint16_t tc)
  {
    x0 = x;
    y0 = y;
    textSize = ts;
    textColor = tc;
    tft.setCursor(x0, y0);
    tft.setTextSize(textSize);
    tft.setTextColor(textColor);
    tft.println("xxx");
  }
  void Delete()
  {
    tft.setCursor(x0, y0);
    tft.println("DDD");
  }
  
};

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("Hello! ST77xx TFT Test"));

  // Initializer for a 1.9" 170x320 TFT display:
  tft.init(170, 320);           // Init ST7789 170x320
  tft.setRotation(1);

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  tft.setSPISpeed(40000000); // Max try 62,500,000
  
  tft.fillScreen(ST77XX_BLACK);
  //Text txt1(10,10,3,ST77XX_RED);

  Rectangle rect1(0,0,10,75,75,ST77XX_RED,ST77XX_GREEN,"abc",ST77XX_BLUE,2);
  delay(short_delay);
  Rectangle rect2(75,75,10,75,75,ST77XX_BLUE,ST77XX_YELLOW,"xyz",ST77XX_RED,2);
  delay(short_delay);
  Circle circ1(200,40,5,38,ST77XX_RED,ST77XX_GREEN);
  delay(short_delay);
  Circle circ2(280,115,5,38,ST77XX_BLUE,ST77XX_YELLOW);
  //txt1.Update(10,10,3,ST77XX_RED);
  //delay(4000);
  //txt1.Delete();
  delay(4000);
  rect1.Delete(ST77XX_BLACK);
  delay(short_delay);
  rect2.Delete(ST77XX_BLACK);
  delay(short_delay);
  circ1.Delete(ST77XX_BLACK);
  delay(short_delay);
  circ2.Delete(ST77XX_BLACK);
  delay(5000);
  
  Serial.println("done");
  //delay(short_delay);
}

void loop() {

}
