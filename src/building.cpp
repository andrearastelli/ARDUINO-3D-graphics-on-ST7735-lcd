#include "building.h"

#include <Adafruit_ST7735.h>


void Building::draw(Adafruit_ST7735 &tft, BLA::Matrix<4, 4> &camera)
{
    // uint8_t minX = tft.width();
    // uint8_t maxX = 0;
    // uint8_t minY = tft.height();
    // uint8_t maxY = 0;
    // for (uint8_t i=0; i<8; ++i)
    // {
    //     minX = min(vertices[i](0), minX);
    //     minY = min(vertices[i](1), minX);
    //     maxX = max(vertices[i](0), maxX);
    //     maxY = max(vertices[i](1), maxY);
    // }

    // tft.setAddrWindow(minX, minY, maxX, maxY);

    for (uint8_t idx=0; idx<size; idx+=4)
    {
        auto v0 = camera * vertices[indexes[idx+0]];
        auto v1 = camera * vertices[indexes[idx+1]];
        auto v2 = camera * vertices[indexes[idx+2]];
        auto v3 = camera * vertices[indexes[idx+3]];

        tft.writeLine(
            -v0(0)/v0(2) * 30 + tft.width()/2.0, -v0(1)/v0(2) * 30 + tft.width()/2.0,
            -v1(0)/v1(2) * 30 + tft.width()/2.0, -v1(1)/v1(2) * 30 + tft.width()/2.0,
            0xFFFF
        );
        tft.writeLine(
            -v1(0)/v1(2) * 30 + tft.width()/2.0, -v1(1)/v1(2) * 30 + tft.width()/2.0,
            -v2(0)/v2(2) * 30 + tft.width()/2.0, -v2(1)/v2(2) * 30 + tft.width()/2.0,
            0xFFFF
        );
        tft.writeLine(
            -v2(0)/v2(2) * 30 + tft.width()/2.0, -v2(1)/v2(2) * 30 + tft.width()/2.0,
            -v3(0)/v3(2) * 30 + tft.width()/2.0, -v3(1)/v3(2) * 30 + tft.width()/2.0,
            0xFFFF
        );
        tft.writeLine(
            -v3(0)/v3(2) * 30 + tft.width()/2.0, -v3(1)/v3(2) * 30 + tft.width()/2.0,
            -v0(0)/v0(2) * 30 + tft.width()/2.0, -v0(1)/v0(2) * 30 + tft.width()/2.0,
            0xFFFF
        );
    }
}