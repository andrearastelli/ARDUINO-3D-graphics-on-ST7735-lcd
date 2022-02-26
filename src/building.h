#include "shape.h"

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

        indexes = new uint8_t[36]{
            0, 1, 2,
            0, 2, 3,
            4, 5, 6,
            4, 6, 7,
            0, 1, 5,
            0, 5, 4,
            1, 2, 6,
            1, 6, 5,
            2, 3, 7,
            2, 7, 6,
            3, 0, 4,
            3, 4, 7
        };

        size = 36;
    }
};