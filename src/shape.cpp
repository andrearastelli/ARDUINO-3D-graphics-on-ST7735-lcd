#include "shape.h"

#include <Adafruit_ST7735.h>

void Shape::draw(Adafruit_ST7735& tft)
{
    tft.startWrite();
    tft.setAddrWindow(0, 0, tft.width(), tft.height());

    for(uint8_t idx=0; idx<size; idx+=3)
    {
        auto v0 = vertices[indexes[idx]];
        auto v1 = vertices[indexes[idx+1]];
        auto v2 = vertices[indexes[idx+2]];

        tft.writeLine(v0(0), v0(1), v1(0), v1(1), 0xFFFF);
        tft.writeLine(v1(0), v1(1), v2(0), v2(1), 0xFFFF);
        tft.writeLine(v2(0), v2(1), v0(0), v0(1), 0xFFFF);
    }

    tft.endWrite();
}