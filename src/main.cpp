#include <Adafruit_GFX.h>    // core graphics library
#include <Adafruit_ST7735.h> // hardware-specific library
#include <BasicLinearAlgebra.h>

#include <math.h>

#include "shape.h"

static const int sclk = 13;
static const int mosi = 11;
static const int cs = 10;
static const int dc = 9;
static const int rst = 8;

// Option 1: use any pins but a little slower
Adafruit_ST7735 tft = Adafruit_ST7735(/*cs=*/6, /*dc=*/7, /*rst=*/5);

float x = 1.0f;
BLA::Matrix<4> vertices[8] {
  BLA::Matrix<4>{ x,  x,  x, 1},
  BLA::Matrix<4>{-x,  x,  x, 1},
  BLA::Matrix<4>{-x, -x,  x, 1},
  BLA::Matrix<4>{ x, -x,  x, 1},
  BLA::Matrix<4>{ x,  x, -x, 1},
  BLA::Matrix<4>{-x,  x, -x, 1},
  BLA::Matrix<4>{-x, -x, -x, 1},
  BLA::Matrix<4>{ x, -x, -x, 1}
};


void setup()
{
  // Serial.begin(9600); // serial monitor stuff
  // Serial.println("TFT ST7735 display test");
  // Serial.println();

  // tft.initSPI()
  tft.initR(INITR_BLACKTAB); // initialize a ST7735S chip, black tab
  // Serial.println("TFT initialized");
  tft.setSPISpeed(8000000);

  tft.fillScreen(ST7735_BLACK);
  // tft.fillRect(0, 0, tft.width(), tft.height(), 0x0000);
}

float theta{0.0f};
const int image_width = 128;
const int image_height = 160;
const float angle_of_view = 90;
const float near = 0.1;
const float far = 100;


unsigned long prevMillis{0};
const long interval{200};

void loop()
{

  // unsigned long currentMillis{millis()};

  // unsigned long start{millis()};
  // BLA::Matrix<4, 4> rotX{
  //   1, 0, 0, 0,
  //   0, cos(theta), sin(theta), 0,
  //   0, -sin(theta), cos(theta), 0,
  //   0, 0, 0, 1
  // };
  // BLA::Matrix<4, 4> rotY{
  //   cos(theta), 0, sin(theta), 0,
  //   0, 1, 0, 0,
  //   -sin(theta), 0, cos(theta), 0,
  //   0, 0, 0, 1
  // };
  // BLA::Matrix<4, 4> rotZ{
  //   cos(theta), sin(theta), 0, 0,
  //   -sin(theta), cos(theta), 0, 0,
  //   0, 0, 1, 0,
  //   0, 0, 0, 1
  // };

  // auto rot = rotZ*rotY*rotX;

  // BLA::Matrix<4, 4> scale {
  //   10, 0, 0, 0,
  //   0, 10, 0, 0,
  //   0, 0, 10, 0,
  //   0, 0, 0, 1
  // };

  BLA::Matrix<4, 4> camera{
     0,  0,  1,  abs(sin(theta)*2)+2,
     0,  1,  0,  0,
    -1,  0,  0,  0,
     0,  0,  0,  1
  };
  camera = BLA::Invert(camera);

  BLA::Matrix<4> nVertices[8];

  for (int i=0; i<8; ++i)
  {
    auto vtx = vertices[i];
    // vtx = scale * vtx;
    // vtx = rot * vtx;
    vtx = camera * vtx;

    // Serial << vtx;
    // Serial.print(" --- ");

    nVertices[i] = {
      -vtx(0)/vtx(2)*50 + tft.width()/2.0,
      -vtx(1)/vtx(2)*50 + tft.height()/2.0,
      1,
      1
    };
    // Serial << nVertices[i];
    // Serial.println();
  }

  // unsigned long end{millis()};
  // Serial.println("Matrix operations took: "+String(end-start)+"ms");


  // start = millis();

  tft.startWrite();
  tft.setAddrWindow(0, 0, tft.width()+2, tft.height()+2);
  tft.writeFillRect(0, 0, tft.width()+2, tft.height()+2, 0x0000);

  for (int i=0,j=1; i<4; ++i)
  {
    auto v0 = nVertices[i];
    auto v1 = nVertices[(j++)%4];
    if (v0(0) == v1(0))
      tft.writeFastVLine(v0(0), v0(1), v1(1)-v0(1), 0xFFFF);
    else
      tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);
  }
  for (int i=4,j=5; i<8; ++i)
  {
    auto v0 = nVertices[i];
    if (j==8) j=4;
    auto v1 = nVertices[j++];
    if (v0(0) == v1(0))
      tft.writeFastVLine(v0(0), v0(1), v1(1)-v0(1), 0xFFFF);
    else
      tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);
  }
  auto v0 = nVertices[0];
  auto v1 = nVertices[1];
  // tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  // v0 = nVertices[1];
  // v1 = nVertices[2];
  // tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  // v0 = nVertices[2];
  // v1 = nVertices[3];
  // tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  // v0 = nVertices[3];
  // v1 = nVertices[0];
  // tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  // v0 = nVertices[4];
  // v1 = nVertices[5];
  // tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  // v0 = nVertices[5];
  // v1 = nVertices[6];
  // tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  // v0 = nVertices[6];
  // v1 = nVertices[7];
  // tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  // v0 = nVertices[7];
  // v1 = nVertices[4];
  // tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  v0 = nVertices[0];
  v1 = nVertices[4];
  tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  v0 = nVertices[1];
  v1 = nVertices[5];
  tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  v0 = nVertices[2];
  v1 = nVertices[6];
  tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  v0 = nVertices[3];
  v1 = nVertices[7];
  tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);

  tft.endWrite();

  // end = millis();
  // Serial.println("Drawing operations took: "+String(end-start)+"ms");

  theta += 0.1f;

  delay(100);
}