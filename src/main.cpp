#include <Adafruit_GFX.h>    // core graphics library
#include <Adafruit_ST7735.h> // hardware-specific library
#include <BasicLinearAlgebra.h>

#include <math.h>

// #define DEBUG
#include "building.h"
#include "starfield.h"


static const int sclk = 13;
static const int mosi = 11;
static const int cs = 10;
static const int dc = 9;
static const int rst = 8;

// Option 1: use any pins but a little slower
Adafruit_ST7735 tft = Adafruit_ST7735(/*cs=*/6, /*dc=*/7, /*rst=*/5);

Building b0{2}, b1{2};
Starfield s{30};

void setup()
{
  #ifdef DEBUG
  Serial.begin(9600); // serial monitor stuff
  Serial.println("TFT ST7735 display test");
  Serial.println();
  #endif

  tft.initSPI();
  tft.initR(INITR_BLACKTAB); // initialize a ST7735S chip, black tab
  tft.setSPISpeed(8000000);

  tft.fillScreen(ST7735_BLACK);

}

float theta{0.0f};

void loop()
{
  tft.fillScreen(0x0000);

  BLA::Matrix<4, 4> camera = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };

  BLA::Matrix<4, 4> rotate{
    cos(theta)*cos(theta), cos(theta)*sin(theta)*sin(theta)-sin(theta)*cos(theta),  cos(theta)*sin(theta)*cos(theta)+sin(theta)*sin(theta),  0,
    sin(theta)*cos(theta), sin(theta)*sin(theta)*sin(theta)+cos(theta)*cos(theta),  sin(theta)*sin(theta)*cos(theta)-cos(theta)*sin(theta),  0,
    -sin(theta),           cos(theta)*sin(theta),                                   cos(theta)*cos(theta),                                   0,
    0,                     0,                                                       0,                                                       1
  };
  BLA::Matrix<4, 4> translate {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 3,
    0, 0, 0, 1
  };
  camera = translate * camera;
  camera = rotate * camera;

  camera = BLA::Invert(camera);


  tft.startWrite();
  b0.draw(tft, camera);
  // b1.draw(tft, camera);
  s.draw(tft, camera);
  tft.endWrite();

  theta += 0.1f;

  delay(100);
}