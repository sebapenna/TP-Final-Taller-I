#ifndef TP_FINAL_ESCENARIO_H
#define TP_FINAL_ESCENARIO_H

#include <map>
#include <src/chell.h>
#include "Box2D/Box2D.h"

class Stage {
private:
    b2World *_world;
    const size_t _width;
    const size_t _height;
    std::map<size_t, Chell*> _chells;

public:
    Stage(size_t width, size_t height);

    ~Stage();

    void step();

    size_t getWidth() const;

    size_t getHeight() const;

    void createChell(float32 x, float32 y, size_t id);

    Chell *getChell(size_t id);
};


#endif //TP_FINAL_ESCENARIO_H
