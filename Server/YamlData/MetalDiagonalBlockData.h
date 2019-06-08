#ifndef PORTAL_METALDIAGONALBLOCKDATA_H
#define PORTAL_METALDIAGONALBLOCKDATA_H

#include <string>

class MetalDiagonalBlockData {
private:
    const float _width;
    const float _height;
    float _x;
    const float _y;
    uint8_t _orientation;

public:
    MetalDiagonalBlockData(const float& width, const float& height,
            const float& x, const float& y, const std::string& orientation);

    const float getWidth() const;

    const float getHeight() const;

    const float getX() const;

    const float getY() const;

    const uint8_t getOrientation() const;
};


#endif //PORTAL_METALDIAGONALBLOCKDATA_H
