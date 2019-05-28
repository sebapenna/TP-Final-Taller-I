#ifndef PORTAL_ROCKBLOCKDATA_H
#define PORTAL_ROCKBLOCKDATA_H

class RockBlockData {
private:
    float _width;
    float _height;
    float _x;
    float _y;

public:
    RockBlockData(const float& width, const float& height, const float& x,
            const float& y);

    float getWidth() const;

    float getHeight() const;

    float getX() const;

    float getY() const;
};


#endif //PORTAL_ROCKBLOCKDATA_H
