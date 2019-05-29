#ifndef PORTAL_CHELLDATA_H
#define PORTAL_CHELLDATA_H


#include <cstdio>

class ChellData {
private:
    size_t _id;
    float _x;
    float _y;

public:
    ChellData(const size_t& id, const float& x, const float& y);

    size_t getId() const;

    float getX() const;

    float getY() const;
};


#endif //PORTAL_CHELLDATA_H
