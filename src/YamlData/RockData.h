#ifndef PORTAL_ROCKDATA_H
#define PORTAL_ROCKDATA_H


#include <cstdio>

class RockData {
private:
    const float _x;
    const float _y;

public:
    RockData(const float& x, const float& y);

    const float getX() const;

    const float getY() const;
};


#endif //PORTAL_ROCKDATA_H
