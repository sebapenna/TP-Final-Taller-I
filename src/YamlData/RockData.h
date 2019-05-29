#ifndef PORTAL_ROCKDATA_H
#define PORTAL_ROCKDATA_H


#include <cstdio>

class RockData {
private:
    float _x;
    float _y;

public:
    RockData(const float& x, const float& y);

    float getX() const;

    float getY() const;
};


#endif //PORTAL_ROCKDATA_H
