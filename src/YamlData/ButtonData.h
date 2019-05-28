#ifndef PORTAL_BUTTONDATA_H
#define PORTAL_BUTTONDATA_H


#include <cstdio>

class ButtonData {
private:
    size_t _id;
    float _x;
    float _y;

public:
    ButtonData(const size_t& id, const float& x, const float& y);

    size_t getId() const;

    float getX() const;

    float getY() const;
};


#endif //PORTAL_BUTTONDATA_H
