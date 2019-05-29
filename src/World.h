#ifndef TP_FINAL_ESCENARIO_H
#define TP_FINAL_ESCENARIO_H

#include <map>
#include <src/Chell.h>
#include "Box2D/Box2D.h"

class World {
private:
    b2World *_world;
    const size_t _width;
    const size_t _height;
    std::map<size_t, Chell*> _chells;   //todo: pasar avector y flag en chell
    // muerto

public:
    World(size_t width, size_t height);

    ~World();

    void step();

    size_t getWidth() const;

    size_t getHeight() const;

    void createChell(float32 x, float32 y, size_t id);

    Chell *getChell(size_t id);
};


#endif //TP_FINAL_ESCENARIO_H
