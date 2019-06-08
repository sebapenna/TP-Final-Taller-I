#ifndef PORTAL_CHELLDATA_H
#define PORTAL_CHELLDATA_H


#include <cstdio>

class ChellData {
private:
    const size_t _id;
    const float _x;
    const float _y;

public:
    ChellData(const size_t& id, const float& x, const float& y);

    const size_t getId() const;

    const float getX() const;

    const float getY() const;
};


#endif //PORTAL_CHELLDATA_H
