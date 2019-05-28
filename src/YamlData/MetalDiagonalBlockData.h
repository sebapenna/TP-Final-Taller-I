#ifndef PORTAL_METALDIAGONALBLOCKDATA_H
#define PORTAL_METALDIAGONALBLOCKDATA_H

#include <string>

class MetalDiagonalBlockData {
private:
    float _width;
    float _height;
    float _x;
    float _y;
    uint8_t _orientation;

public:
    MetalDiagonalBlockData(const float& width, const float& height,
            const float& x, const float& y, const std::string& orientation);

    float getWidth() const;

    float getHeight() const;

    float getX() const;

    float getY() const;

    uint8_t getOrientation() const;
};


#endif //PORTAL_METALDIAGONALBLOCKDATA_H
