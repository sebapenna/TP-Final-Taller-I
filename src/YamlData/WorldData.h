#ifndef PORTAL_WORLDDATA_H
#define PORTAL_WORLDDATA_H

#include <iostream>

class WorldData {
private:
    size_t _height;
    size_t _width;

public:
    WorldData(const size_t &height, const size_t &width);

    size_t getHeight() const;

    size_t getWidth() const;
};


#endif //PORTAL_WORLDDATA_H
