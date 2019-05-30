#include <iostream>
#include "World.h"
#include "constants.h"
#include "ContactListener.h"
#include "yaml-cpp/yaml.h"
#include "Stage.h"
#include "GroundBlocks/RockBlock.h"
#include "GroundBlocks/MetalBlock.h"
#include "GroundBlocks/MetalDiagonalBlock.h"

World::World(size_t width, size_t height) : _width(width), _height(height) {
    b2Vec2 gravity(GRAVITY_X, GRAVITY_Y);
    _world = new b2World(gravity);
    _world->SetContactListener(new ContactListener(_world));
}

World::~World() {
    delete _world;
}

/************************ Getters ************************/
size_t World::getWidth() const {
    return _width;
}

size_t World::getHeight() const {
    return _height;
}

Chell *World::getChell(size_t id) {
    if (id < _chells.size())
        return _chells[id];
    return nullptr;
}

const std::vector<Rock *> &World::getRocks() const {
    return _rocks;
}

const std::map<size_t, Button *> &World::getButtons() const {
    return _buttons;
}


const std::map<size_t, Gate *> &World::getGates() const {
    return _gates;
}

const std::map<size_t, EnergyReceiver *> &World::getEnergyReceivers() const {
    return _energy_receivers;
}

/************************ Step ************************/
void World::step() {
    _world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSTION_ITERATIONS);
    // Orden de acciones: primero las que su estado afectan a otros
    for (auto &button : _buttons)
        button.second->updateState();
    for (auto &gate : _gates)
        gate.second->updateState();
    for (auto &energy_receiver : _energy_receivers)
        energy_receiver.second->updateState();
    for (auto & chell : _chells)
        chell.second->move();
}

/************************ Create Bodies ************************/
b2Body *World::createStaticBox(const float &x, const float &y,
        const float &box_width, const float &box_height,
        const float &friction) {
    b2BodyDef body_def;
    body_def.position.Set(x, y);
    body_def.type = b2_staticBody;

    b2PolygonShape shape;
    shape.SetAsBox(box_width, box_height);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.friction = friction;

    b2Body *body = _world->CreateBody(&body_def);

    body->CreateFixture(&fixture);
    return body;
}

b2Body *World::createDynamicBox(const float &x, const float &y,
        const float &box_width, const float &box_height, const float &density) {
    b2BodyDef body_def;
    body_def.position.Set(x, y);
    body_def.type = b2_dynamicBody;
    body_def.fixedRotation = true;

    b2PolygonShape shape;
    shape.SetAsBox(box_width, box_height);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = density;

    b2Body *body = _world->CreateBody(&body_def);

    body->CreateFixture(&fixture);
    return body;
}

void World::createRockBlock(const float &width, const float &height,
        const float &x, const float &y) {
    auto body = createStaticBox(x, y, width / 2, height / 2, BLOCK_FRICTION);
    body->SetUserData(new RockBlock());
}

void World::createMetalBlock(const float &width, const float &height,
        const float &x, const float &y) {
    auto body = createStaticBox(x, y , width/2, height/2, BLOCK_FRICTION);
    body->SetUserData(new MetalBlock());
}

void World::createMetalDiagonalBlock(const float &width, const float &height,
                                     const float &x, const float &y,
                                     const uint8_t &orientation) {
    b2Vec2 vertices[3];
    int32 count = 3;
    switch (orientation) {
        case O_NE:
            vertices[0].Set(0, 0);
            vertices[1].Set(width, 0);
            vertices[2].Set(0, height);
            break;
        case O_NO:
            vertices[0].Set(0, 0);
            vertices[1].Set(width, 0);
            vertices[2].Set(width, height);
            break;
        case O_SE:
            vertices[0].Set(0, height);
            vertices[1].Set(width, height);
            vertices[2].Set(0, 0);
            break;
        case O_SO:
            vertices[0].Set(0, height);
            vertices[1].Set(width, height);
            vertices[2].Set(width, 0);
            break;
        default:    // No existe este caso
            break;
    }

    b2BodyDef body_def;
    body_def.position.Set(x, y);
    body_def.type = b2_staticBody;

    b2Body *body = _world->CreateBody(&body_def);

    b2PolygonShape shape;
    shape.Set(vertices, count);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.friction = BLOCK_FRICTION;

    body->CreateFixture(&fixture);
}

void World::createRock(const float &x, const float &y) {
    auto body = createDynamicBox(x, y, ROCK_WIDTH, ROCK_HEIGHT, ROCK_DENSITY);
    auto *rock = new Rock(body);
    body->SetUserData(rock);
    _rocks.push_back(rock);
}

void World::createAcid(const float &x, const float &y) {
    auto body = createStaticBox(x, y, ACID_WIDTH, ACID_HEIGHT, ACID_FRICTION);
    body->SetUserData((void *) ACID);   // Suficiente que sea una macro
}

void World::createButton(const size_t &id, const float &x, const float &y) {
   auto body = createStaticBox(x, y, BUTTON_WIDTH, BUTTON_HEIGHT,
           BUTTON_FRICTION);
   auto *button = new Button();
   body->SetUserData(button);
   _buttons.insert({id, button});
}

void World::createGate(const size_t &id, const float &x, const float &y,
                       const std::vector<size_t>& buttons_needed,
                       const std::vector<size_t>& energy_receiver_needed) {
    auto body = createStaticBox(x, y, GATE_WIDTH, GATE_HEIGHT, GATE_FRICTION);
    auto *gate = new Gate();
    for (auto &button_id : buttons_needed)
        gate->addButtonNeeded(_buttons.at(button_id));
    for (auto &e_rec_id : energy_receiver_needed)
        gate->addEnergyReceiverNeeded(_energy_receivers.at(e_rec_id));
    body->SetUserData(gate);
    _gates.insert({id, gate});
}

void World::createEnergyReceiver(const size_t &id, const float &x,
                                 const float &y) {
    auto body = createStaticBox(x, y, ENRG_RECV_WIDTH, ENRG_RECV_HEIGHT,
            ENRG_RECV_FRICTION);
    auto *e_recv = new EnergyReceiver();
    body->SetUserData(e_recv);
    _energy_receivers.insert({id, e_recv});
}

void World::createChell(const float &x, const float &y, size_t id) {
//    todo: restitution necesaria ? => puede hacer sdl
    auto body = createDynamicBox(x, y, CHELL_WIDTH, CHELL_HEIGHT,
            CHELL_DENSITY);
    auto *chell = new Chell(id, body);
    body->SetUserData(chell);
    _chells.insert({id, chell});
}

