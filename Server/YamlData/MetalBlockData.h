
#ifndef PORTAL_METALBLOCKDATA_H
#define PORTAL_METALBLOCKDATA_H


class MetalBlockData {
private:
    const float _width;
    const float _height;
    const float _x;
    const float _y;

public:
    MetalBlockData(const float& width, const float& height, const float& x,
                  const float& y);

    const float getWidth() const;

    const float getHeight() const;

    const float getX() const;

    const float getY() const;
};


#endif //PORTAL_METALBLOCKDATA_H
