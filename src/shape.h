#include <BasicLinearAlgebra.h>

#pragma once

class Adafruit_ST7735;

struct Shape
{
    BLA::Matrix<4> *vertices = nullptr;
    uint8_t *indexes = nullptr;
    uint8_t size = 0;

    Shape() = default;

    void draw(Adafruit_ST7735& tft);
};