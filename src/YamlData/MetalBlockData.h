
#ifndef PORTAL_METALBLOCKDATA_H
#define PORTAL_METALBLOCKDATA_H


class MetalBlockData {
private:
    float _width;
    float _height;
    float _x;
    float _y;

public:
    MetalBlockData(const float& width, const float& height, const float& x,
                  const float& y);

    float getWidth() const;

    float getHeight() const;

    float getX() const;

    float getY() const;
};


#endif //PORTAL_METALBLOCKDATA_H
