#ifndef PORTAL_BUTTONDATA_H
#define PORTAL_BUTTONDATA_H


#include <cstdio>

class ButtonData {
private:
    const size_t _id;
    const float _x;
    const float _y;

public:
    ButtonData(const size_t& id, const float& x, const float& y);

    const size_t getId() const;

    const float getX() const;

    const float getY() const;
};


#endif //PORTAL_BUTTONDATA_H
