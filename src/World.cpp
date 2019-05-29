#include <iostream>
#include "World.h"
#include "constants.h"
#include "ContactListener.h"
#include "yaml-cpp/yaml.h"
#include "Stage.h"

World::World(size_t width, size_t height) : _width(width), _height(height) {
    b2Vec2 gravity(GRAVITY_X, GRAVITY_Y);
    _world = new b2World(gravity);
    _world->SetContactListener(new ContactListener(_world));

    /* PISO PARA TESTEAR */
    b2BodyDef piso_def;
    piso_def.position.Set(0, -10);
    piso_def.type = b2_staticBody;

    b2Body *piso_body = _world->CreateBody(&piso_def);

    b2PolygonShape piso_box;
    piso_box.SetAsBox(50, 10);

    b2FixtureDef piso_fixture;
    piso_fixture.shape = &piso_box;
    piso_fixture.friction = BLOCK_FRICTION;
    piso_fixture.density = BLOCK_DENSITY;

    piso_body->CreateFixture(&piso_fixture);
}

World::~World() {
    delete _world;
}

void World::step() {
    _world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSTION_ITERATIONS);
    for (auto & _chell : _chells)
        _chell.second->move();
    // Aplicar update/move de todos los cuerpos
}

size_t World::getWidth() const {
    return _width;
}

size_t World::getHeight() const {
    return _height;
}

void World::createChell(float32 x, float32 y, size_t id) {
    b2BodyDef b_def;
    b_def.type = b2_dynamicBody;
    b_def.position.Set(x, y);
    b_def.fixedRotation = true;

    b2PolygonShape b_shape;
    b_shape.SetAsBox(CHELL_WIDTH, CHELL_HEIGHT);

    b2FixtureDef b_fixture;
    b_fixture.shape = &b_shape;
    b_fixture.density = CHELL_DENSITY;
//    todo: restitution necesaria ? => puede hacer sdl
    auto *n_chell_body = _world->CreateBody(&b_def);

    n_chell_body->CreateFixture(&b_fixture);

    auto *n_chell = new Chell(id, n_chell_body);

    _chells.insert({id, n_chell});
}

Chell *World::getChell(size_t id) {
    if (id < _chells.size())
        return _chells[id];
    return nullptr;
}

