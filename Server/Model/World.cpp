#include <Server/Model/EnergyBlocks/EnergyTransmitter.h>
#include <Server/Model/GroundBlocks/MetalDiagonalBlock.h>
#include <Server/Model/GroundBlocks/MetalBlock.h>
#include <Server/Model/GroundBlocks/RockBlock.h>
#include <Server/Model/Obstacles/EnergyBarrier.h>
#include <Server/Model/Obstacles/Acid.h>
#include <Server/Model/ContactListener.h>
#include <Server/Model/constants.h>
#include <yaml-cpp/yaml.h>
#include <algorithm>
#include <memory>
#include <iostream>
#include "World.h"

using std::remove_if;
using std::vector;
using std::for_each;
using std::string;

World::World(const size_t &width, const size_t &height) : _width(width), _height(height) {
    b2Vec2 gravity(GRAVITY_X, GRAVITY_Y);
    _world = new b2World(gravity);
    _contact_listener = new ContactListener(_world);
    _world->SetContactListener(_contact_listener);
}

template<class T>
void deletePointerVector(vector<T> &v) {
    for (auto &ptr : v) {
        delete ptr;
        ptr = nullptr;
    }
}

World::~World() {
    deletePointerVector<Chell*>(_chells);
    deletePointerVector<RockBlock*>(_rock_blocks);
    deletePointerVector<Button*>(_buttons);
    deletePointerVector<Gate*>(_gates);
    deletePointerVector<Acid*>(_acids);
    deletePointerVector<EnergyTransmitter*>(_energy_transmitters);
    deletePointerVector<EnergyReceiver*>(_energy_receivers);
    deletePointerVector<EnergyBall*>(_energy_balls);
    deletePointerVector<Rock*>(_rocks);
    deletePointerVector<MetalDiagonalBlock*>(_metal_diagonal_blocks);
    deletePointerVector<MetalBlock*>(_metal_blocks);
    deletePointerVector<EnergyBarrier*>(_energy_barriers);
    delete _contact_listener;
    delete _world;
}

/************************ Getters ************************/
size_t World::getWidth() const {
    return _width;
}

size_t World::getHeight() const {
    return _height;
}

Chell *World::getChell(const size_t &id) {
    return (id < _chells.size()) ? _chells[id] : nullptr;
}

Rock *World::getRock(const size_t &id) {
    return (id < _rocks.size()) ? _rocks[id] : nullptr;
}


Button *World::getButton(const size_t &id) {
    return (id < _buttons.size()) ? _buttons[id] : nullptr;
}

Gate *World::getGate(const size_t &id) {
    return (id < _gates.size()) ? _gates[id]: nullptr;
}

EnergyReceiver *World::getEnergyReceiver(const size_t &id) {
    return (id < _energy_receivers.size()) ? _energy_receivers[id] : nullptr;
}


EnergyBall *World::getEnergyBall(const size_t &id) {
    return (id < _energy_balls.size()) ? _energy_balls[id] : nullptr;
}

b2World *World::getWorld() const {
    return _world;
}


/************************ Step ************************/
void World::step() {
    // Vacio estructuras de objetos actualizados/eliminados durante step
    _objects_to_update.clear();
    _objects_to_delete.clear();
    _world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSTION_ITERATIONS);
    // Orden de acciones: primero las que su estado afectan a otros
    stepEnergyTransmitters();
    stepEnergyBalls();
    stepButtons();
    stepEnergyReceivers();
    stepGates();
    stepChells();
    stepRocks();

}

void World::stepGates() {
    for (auto &gate : _gates) {
        gate->updateState();
        if (gate->actedDuringStep())
            _objects_to_update.push_back(gate);
    }
}

void World::stepButtons() {
    for (auto &button : _buttons) {
        button->updateState();
        if (button->actedDuringStep())
            _objects_to_update.push_back(button);
    }
}

void World::stepEnergyReceivers() {
    for (auto &energy_receiver : _energy_receivers) {
        energy_receiver->updateState();
        if (energy_receiver->actedDuringStep())
            _objects_to_update.push_back(energy_receiver);
    }
}

void World::stepEnergyTransmitters() {
    for (auto &energy_transmitter : _energy_transmitters) {
        if (energy_transmitter->releaseEnergyBall())
            this->createEnergyBall(energy_transmitter);
        if (energy_transmitter->actedDuringStep())
            _objects_to_update.push_back(energy_transmitter);
    }
}

//template <class T>  // Libera memoria de entidades con capacidad de morir
//bool deleted(T* ptr) {
//    return ptr->isDead() ? (delete ptr, ptr = nullptr, true) : false;
//}

void World::stepChells() {
    for (int i = 0; i < _chells.size(); ++i) {
        auto chell = _chells[i];
        if (chell) {    // Verifico no haberlo eliminado previamente
            if (!chell->isDead()) { // Verifico que no murio en algun contacto
                chell->move();
                if (chell->actedDuringStep())
                    _objects_to_update.push_back(chell);
            } else {
                _world->DestroyBody(chell->getBody());
                _objects_to_delete.emplace_back(i, chell->getClassId());
                delete chell;
                _chells[i] = nullptr;
            }
        }
    }
//    _chells.erase(remove_if(_chells.begin(), _chells.end(), deleted<Chell>), _chells.end());
}

void World::stepEnergyBalls() {
    for (int i = 0; i < _energy_balls.size(); ++i) {
        auto energy_ball = _energy_balls[i];
        if (energy_ball) { // Verifico no haberlo eliminado previamente
            energy_ball->updateLifetime();
            if (energy_ball->isDead()) {
                _world->DestroyBody(energy_ball->getBody());
                _objects_to_delete.emplace_back(i, energy_ball->getClassId());
                delete energy_ball;
                _energy_balls[i] = nullptr;
            } else if (energy_ball->actedDuringStep()) {
                _objects_to_update.push_back(energy_ball);
            }
        }
    }
//    _energy_balls.erase(remove_if(_energy_balls.begin(), _energy_balls.end(), deleted<EnergyBall>),
//            _energy_balls.end());
}

void World::stepRocks() {
    for (int i = 0; i < _rocks.size(); ++i) {
        auto rock = _rocks[i];
        if (rock) {
            if (rock->isDead()) {
                _world->DestroyBody(rock->getBody());
                _objects_to_delete.emplace_back(i, rock->getClassId());
                delete rock;
                _rocks[i] = nullptr;
            } else if (rock->actedDuringStep()) {
                _objects_to_update.push_back(rock);
            }
        }
    }
//    _rocks.erase(remove_if(_rocks.begin(), _rocks.end(), deleted<Rock>), _rocks.end());
}

/************************ Create Bodies ************************/
b2Body *World::createStaticBox(const float &x, const float &y,
        const float &box_half_width, const float &box_half_height,
        const float &friction) {
    b2BodyDef body_def;
    body_def.position.Set(x, y);
    body_def.type = b2_staticBody;

    b2PolygonShape shape;
    shape.SetAsBox(box_half_width, box_half_height);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.friction = friction;

    b2Body *body = _world->CreateBody(&body_def);

    body->CreateFixture(&fixture);
    return body;
}

b2Body *World::createDynamicBox(const float &x, const float &y,
        const float &box_half_width, const float &box_half_height,
        const float &density) {
    b2BodyDef body_def;
    body_def.position.Set(x, y);
    body_def.type = b2_dynamicBody;
//    body_def.fixedRotation = false;
    body_def.fixedRotation = true;

    b2PolygonShape shape;
    shape.SetAsBox(box_half_width, box_half_height);

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
    auto rock_block = new RockBlock(x, y, width, height);
    body->SetUserData(rock_block);
    _rock_blocks.push_back(rock_block);
}

void World::createMetalBlock(const float &width, const float &height,
        const float &x, const float &y) {
    auto body = createStaticBox(x, y , width/2, height/2, BLOCK_FRICTION);
    auto metal_block = new MetalBlock(x, y, width, height);
    body->SetUserData(metal_block);
    _metal_blocks.push_back(metal_block);
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

    auto met_diag_block = new MetalDiagonalBlock(x, y, width, height, orientation);
    body->SetUserData(met_diag_block);
    _metal_diagonal_blocks.push_back(met_diag_block);
}

void World::createRock(const float &x, const float &y) {
    auto body = createDynamicBox(x, y, ROCK_HALF_LEN, ROCK_HALF_LEN,
            ROCK_DENSITY);
    // id se incrementa con tamaño del vector de rocas
    auto *rock = new Rock(_rocks.size(), body);
    body->SetUserData(rock);
    _rocks.push_back(rock);
}

void World::createAcid(const float &x, const float &y) {
    auto body = createStaticBox(x, y, ACID_HALF_WIDTH, ACID_HALF_HEIGHT,
            ACID_FRICTION);
    auto acid = new Acid(x, y);
    body->SetUserData(acid);   // Suficiente que sea una macro
    _acids.push_back(acid);
}

void World::createButton(const float &x, const float &y) {
   auto body = createStaticBox(x, y, BUTTON_HALF_WIDTH, BUTTON_HALF_HEIGHT,
           BUTTON_FRICTION);
    // id se incrementa con tamaño del vector de botones
    auto *button = new Button(_buttons.size(), x, y);
   body->SetUserData(button);
   _buttons.push_back(button);
}

void World::createGate(const float &x, const float &y, const std::vector<size_t> &buttons_needed,
                       const std::vector<size_t> &energy_receiver_needed) {
    auto body = createStaticBox(x, y, GATE_HALF_WIDTH, GATE_HALF_HEIGHT,
            GATE_FRICTION);
    // id se incrementa con tamaño del vector de gates
    auto *gate = new Gate(_gates.size(), x, y);

    for (auto &button_id : buttons_needed)
        gate->addButtonNeeded(_buttons.at(button_id));

    for (auto &e_rec_id : energy_receiver_needed)
        gate->addEnergyReceiverNeeded(_energy_receivers.at(e_rec_id));

    body->SetUserData(gate);
    _gates.push_back(gate);
}

void World::createEnergyReceiver(const float &x, const float &y) {
    auto body = createStaticBox(x, y, ENRG_BLOCK_HALF_LEN, ENRG_BLOCK_HALF_LEN, ENRG_BLOCK_FRICTION);
    // id se incrementa con tamaño del vector de receivers
    auto e_recv = new EnergyReceiver(_energy_receivers.size(), x, y);
    body->SetUserData(e_recv);
    _energy_receivers.push_back(e_recv);
}

void World::createEnergyTransmitter(const float &x, const float &y,
                                    const uint8_t &direction) {
    auto body = createStaticBox(x, y, ENRG_BLOCK_HALF_LEN, ENRG_BLOCK_HALF_LEN,
                                ENRG_BLOCK_FRICTION);
    // id se incrementa con tamaño del vector de transmitters
    auto *e_transm = new EnergyTransmitter(_energy_transmitters.size(), body, direction);
    body->SetUserData(e_transm);
    _energy_transmitters.push_back(e_transm);
}

void World::createEnergyBall(EnergyTransmitter *energy_transm) {
    auto *source_body = energy_transm->getBody();
    float x = source_body->GetPosition().x;
    float y = source_body->GetPosition().y;
    // Sumo delta para evitar posible colision con el transmisor
    float dist_to_ball_center = ENRG_BLOCK_HALF_LEN + ENRG_BALL_RADIUS + DELTA_POS;
    switch (energy_transm->getDirection()) {
        case O_N:
            y += dist_to_ball_center;
            break;
        case O_S:
            y -= dist_to_ball_center;
            break;
        case O_E:
            x += dist_to_ball_center;
            break;
        case O_O:
            x -= dist_to_ball_center;
            break;
        default:    // No existe este caso
            break;
    }
    b2BodyDef body_def;
    body_def.position.Set(x, y);
    body_def.type = b2_dynamicBody;
    body_def.gravityScale = 0;  // Cuerpo no afectado por gravedad

    b2CircleShape shape;
    shape.m_p.Set(0,0); // Posicion relativa al centro
    shape.m_radius = ENRG_BALL_RADIUS - DELTA_POS; // Reduzco tamaño para evitar contacto por delta

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = ENRG_BALL_DENSITY;

    b2Body *body = _world->CreateBody(&body_def);

    body->CreateFixture(&fixture);

    auto *energy_ball = new EnergyBall(_energy_balls.size(), body, energy_transm->getDirection());
    body->SetUserData(energy_ball);
    _energy_balls.push_back(energy_ball);
}

void World::createChell(const float &x, const float &y) {
    auto body = createDynamicBox(x, y, CHELL_HALF_WIDTH, CHELL_HALF_HEIGHT,
            CHELL_DENSITY);
    auto chell = new Chell(_chells.size(), body);
    body->SetUserData(chell);
    body->SetGravityScale(5);   // No permite que cuerpo flote tanto tiempo en el aire
    _chells.push_back(chell);
}

void World::createEnergyBarrier(const float &x, const float &y,
                                const uint8_t &direction) {
    float half_height = 0, half_width = 0;
    switch (direction) {
        case O_V:
            half_height = BARRIER_HALF_LENGTH;
            half_width = BARRIER_HALF_WIDTH;
            break;
        case O_H:
            half_height = BARRIER_HALF_WIDTH;
            half_width = BARRIER_HALF_LENGTH;
            break;
        default:    // No existe este caso
            break;
    }
    auto body = createStaticBox(x, y , half_width, half_height, 0);   // Friction = 0
    auto e_barrier = new EnergyBarrier(x, y, 2 * half_width, 2 * half_height);
    body->SetUserData(e_barrier);
    _energy_barriers.push_back(e_barrier);
}

const vector<Collidable *> &World::getObjectsToUpdate() const {
    return _objects_to_update;
}

const vector<std::pair<size_t, uint8_t>> &World::getObjectsToDelete() const {
    return _objects_to_delete;
}

World &World::operator=(World &&other) {
    if (&other == this)
        return *this;
    _width = other._width;
    _height = other._height;
    _world = other._world;
    _contact_listener = other._contact_listener;

    other._width = -1;
    other._height = -1;
    other._world = nullptr;
    other._contact_listener = nullptr;
    return *this;
}

const vector<Chell *> &World::getChells() const {
    return _chells;
}

const vector<Rock *> &World::getRocks() const {
    return _rocks;
}

const vector<Button *> &World::getButtons() const {
    return _buttons;
}

const vector<Gate *> &World::getGates() const {
    return _gates;
}

const vector<EnergyReceiver *> &World::getEnergyReceivers() const {
    return _energy_receivers;
}

const vector<EnergyTransmitter *> &World::getEnergyTransmitters() const {
    return _energy_transmitters;
}

const vector<RockBlock *> &World::getRockBlocks() const {
    return _rock_blocks;
}

const vector<Acid *> &World::getAcids() const {
    return _acids;
}

const vector<MetalDiagonalBlock *> &World::getMetalDiagonalBlocks() const {
    return _metal_diagonal_blocks;
}

const vector<MetalBlock *> &World::getMetalBlocks() const {
    return _metal_blocks;
}

const vector<EnergyBarrier *> &World::getEnergyBarriers() const {
    return _energy_barriers;
}


