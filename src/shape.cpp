#include "shape.h"

#include <Adafruit_ST7735.h>

void Shape::draw(Adafruit_ST7735 &tft, BLA::Matrix<4, 4> &camera)
{
    tft.setAddrWindow(0, 0, tft.width(), tft.height());

    #ifdef DEBUG
    Serial.print("indexes size: ");
    Serial.println(size);
    #endif

    for(uint8_t idx=0; idx<size; idx+=3)
    {
        auto v0 = camera * vertices[indexes[idx]];
        auto v1 = camera * vertices[indexes[idx+1]];
        auto v2 = camera * vertices[indexes[idx+2]];

        #ifdef DEBUG
        Serial.print("V0: "); Serial << v0; Serial.print('\n');
        Serial.print("V1: "); Serial << v0; Serial.print('\n');
        Serial.print("V2: "); Serial << v0; Serial.print('\n');
        #endif

        tft.writeLine(
            -v0(0)/v0(2) * 30 + tft.width()/2.0, -v0(1)/v0(2) * 30 + tft.height()/2.0,
            -v1(0)/v1(2) * 30 + tft.width()/2.0, -v1(1)/v1(2) * 30 + tft.height()/2.0,
            0xFFFF
        );
        tft.writeLine(
            -v1(0)/v1(2) * 30 + tft.width()/2.0, -v1(1)/v1(2) * 30 + tft.height()/2.0,
            -v2(0)/v2(2) * 30 + tft.width()/2.0, -v2(1)/v2(2) * 30 + tft.height()/2.0,
            0xFFFF
        );
        tft.writeLine(
            -v2(0)/v2(2) * 30 + tft.width()/2.0, -v2(1)/v2(2) * 30 + tft.height()/2.0,
            -v0(0)/v0(2) * 30 + tft.width()/2.0, -v0(1)/v0(2) * 30 + tft.height()/2.0,
            0xFFFF
        );
    }
}

void Shape::translate(BLA::Matrix<3> &p)
{
    BLA::Matrix<4, 4> translation{
        1, 0, 0, p(0),
        0, 1, 0, p(1),
        0, 0, 1, p(2),
        0, 0, 0, 1
    };

    for(uint8_t idx=0; idx<8; ++idx)
    {
        vertices[idx] = translation * vertices[idx];

        #ifdef DEBUG
        Serial << vertices[idx];
        Serial.println();
        #endif
    }
}