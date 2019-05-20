#include "stage.h"

Stage::Stage() {
    b2Vec2 gravity(0.0f, -10.0f);
    _world = new b2World(gravity);
}

Stage::~Stage() {
    delete _world;
}
