#ifndef PORTAL_ROCKDATA_H
#define PORTAL_ROCKDATA_H


#include <cstdio>

class RockData {
private:
    size_t _id;
    float _x;
    float _y;

public:
    RockData(const size_t& id, const float& x, const float& y);

    size_t getId() const;

    float getX() const;

    float getY() const;
};


#endif //PORTAL_ROCKDATA_H
