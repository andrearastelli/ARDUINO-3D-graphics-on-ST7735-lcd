#include "shape.h"

class Adafruit_ST7735;

struct Building : public Shape
{
    Building(uint8_t height)
    {
        vertices = new BLA::Matrix<4>[8];

        vertices[0] = {-1, 0, 1, 1};
        vertices[1] = {1, 0, 1, 1};
        vertices[2] = {1, 0, -1, 1};
        vertices[3] = {-1, 0, -1, 1};
        vertices[4] = {-1, height, 1, 1};
        vertices[5] = {1, height, 1, 1};
        vertices[6] = {1, height, -1, 1};
        vertices[7] = {-1, height, -1, 1};

        indexes = new uint8_t[24]{
            0, 1, 2, 3,  // 4
            4, 5, 6, 7,  // 8
            0, 1, 5, 4,  // 12
            1, 2, 6, 5,  // 16
            2, 3, 7, 6,  // 20
            3, 0, 4, 7   // 24
        };

        size = 24;
    }

    void draw(Adafruit_ST7735 &tft, BLA::Matrix<4, 4> &camera) override;
};