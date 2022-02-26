#include "building.h"

#include <Adafruit_ST7735.h>


void Building::draw(Adafruit_ST7735 &tft, BLA::Matrix<4, 4> &camera)
{
    for (uint8_t idx=0; idx<size; idx+=4)
    {
        for (uint8_t i=0; i<4; ++i)
        {
            auto v0 = camera * vertices[indexes[idx+i]];
            auto v1 = camera * vertices[indexes[idx+((i+1)%4)]];

            BLA::Matrix<3, 3> scale{
                30, 0, 0,
                0, 30, 0,
                0, 0, 1
            };
            BLA::Matrix<3, 3> translate{
                1, 0, tft.width()/2.0,
                0, 1, tft.height()/2.0,
                0, 0, 1
            };

            BLA::Matrix<3> p0{ -v0(0)/v0(2), -v0(1)/v0(2), 1 };
            BLA::Matrix<3> p1{ -v1(0)/v1(2), -v1(1)/v1(2), 1 };
            p0 = translate * (scale * p0);
            p1 = translate * (scale * p1);
            uint8_t x0 = p0(0);
            uint8_t y0 = p0(1);
            uint8_t x1 = p1(0);
            uint8_t y1 = p1(1);

            tft.writeLine(x0, y0, x1, y1, 0xFFFF);
        }
    }
}