#include <BasicLinearAlgebra.h>

#pragma once

class Adafruit_ST7735;

struct Starfield
{
    BLA::Matrix<4> *stars = nullptr;
    uint8_t num_stars = 0;

    Starfield(uint8_t num_stars) : num_stars{num_stars} {
        stars = new BLA::Matrix<4>[num_stars];

        for (uint8_t i=0; i<num_stars; ++i)
        {
            stars[i] = BLA::Matrix<4>{
                sin(random()*PI)*cos(random()*PI/2.0) * 100.0,
                sin(random()*PI)*sin(random()*PI/2.0) * 100.0,
                cos(random()*PI/2.0) * 100.0,
                1
            };
        }
    }

    void draw(Adafruit_ST7735 &tft, BLA::Matrix<4, 4> &camera)
    {
        for (uint8_t i=0; i<num_stars; ++i)
        {
            auto v = camera * stars[i];
            BLA::Matrix<3> p{ -v(0)/v(2), -v(1)/v(2), 1 };

            BLA::Matrix<3, 3> scale {
                30, 0, 0,
                0, 30, 0,
                0, 0, 1
            };
            BLA::Matrix<3, 3> translate {
                1, 0, tft.width()/2.0,
                0, 1, tft.height()/2.0,
                0, 0, 1
            };

            p = translate * (scale * p);

            // if (-p(2) < 1.0) continue;

            tft.writePixel(p(0), p(1), 0xFFFF);
        }
    }
};