#ifndef PORTAL_WORLDDATA_H
#define PORTAL_WORLDDATA_H

#include <iostream>

class WorldData {
private:
    const size_t _height;
    const size_t _width;

public:
    WorldData(const size_t &height, const size_t &width);

    const size_t getHeight() const;

    const size_t getWidth() const;
};


#endif //PORTAL_WORLDDATA_H
