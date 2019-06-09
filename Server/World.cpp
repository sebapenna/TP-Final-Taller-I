#include <Server/EnergyBlocks/EnergyTransmitter.h>
#include <Server/GroundBlocks/MetalDiagonalBlock.h>
#include <Server/GroundBlocks/MetalBlock.h>
#include <Server/GroundBlocks/RockBlock.h>
#include <Server/Obstacles/EnergyBarrier.h>
#include <Server/Obstacles/Acid.h>
#include <Server/ContactListener.h>
#include <Server/constants.h>
#include <yaml-cpp/yaml.h>
#include <algorithm>
#include <memory>
#include <iostream>
#include "World.h"

using std::remove_if;
using std::vector;
using std::for_each;

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
    // todo: ELIMINAR TODOS LOS PUNTEROS DE CADA CLASE (destroy)
    // TODO: EN VECTOR PONER nullptr?
    _world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSTION_ITERATIONS);
    stepEnergyTransmitters();
    stepEnergyBalls();
    stepButtons();
    stepEnergyReceivers();
    stepGates();
    stepChells();
    stepRocks();
    // Orden de acciones: primero las que su estado afectan a otros
    // todo: GUARDAR REGISTRO DE LOS IDS DE LO QUE TENGO QUE ELIMINAR, CUALQUIERA SEA OBJETO CON
    //  ID VA A ALCANZAR (RESTO DE DATOS DEL DTO NO ME IMPORTAN). QUIZAS VOY A NECESITAR UN
    //  VECTOR DE CADA OBJETO PARA LOS UPDATED. O HACER UN MAP<ID,CLASSNAME(STRING)> PARA LOS QUE
    //  HAYA QUE ELIMNAR, SEPARADO DE LOS QUE NO MURIERON PERO SI SE ACTUALIZARON. DONDE HAGO
    //  DESTROY BODY TODAVIA TENGO EL ID, ME LO PUEDO GUARDAR AHI EN EL MAP
    // todo: ELIMINAR ROCAS QUE DESAPARECEN
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
    for (auto &energy_receiver : _energy_receivers)
        energy_receiver->updateState();
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
            if (!chell->isDead()) // Verifico que no murio en algun contacto
                chell->move();
            else {
                _world->DestroyBody(chell->getBody());
                _objects_to_delete.emplace_back(i, chell->getClassName());
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
                _objects_to_delete.emplace_back(i, energy_ball->getClassName());
                delete energy_ball;
                _energy_balls[i] = nullptr;
            }
        }
    }
//    _energy_balls.erase(remove_if(_energy_balls.begin(), _energy_balls.end(), deleted<EnergyBall>),
//            _energy_balls.end());
}

void World::stepRocks() {
    for (int i = 0; i < _rocks.size(); ++i) {
        auto rock = _rocks[i];
        if (rock && rock->isDead()) {
            _world->DestroyBody(rock->getBody());
            _objects_to_delete.emplace_back(i, rock->getClassName());
            delete rock;
            _rocks[i] = nullptr;
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
    body_def.fixedRotation = false;

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
    auto rock_block = new RockBlock();
    body->SetUserData(rock_block);
    _rock_blocks.push_back(rock_block);
}

void World::createMetalBlock(const float &width, const float &height,
        const float &x, const float &y) {
    auto body = createStaticBox(x, y , width/2, height/2, BLOCK_FRICTION);
    auto metal_block = new MetalBlock();
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

    auto met_diag_block = new MetalDiagonalBlock(orientation);
    body->SetUserData(met_diag_block);
    _metal_diagonal_blocks.push_back(met_diag_block);
}

void World::createRock(const float &x, const float &y) {
    auto body = createDynamicBox(x, y, ROCK_HALF_LEN, ROCK_HALF_LEN,
            ROCK_DENSITY);
    auto *rock = new Rock(body);
    body->SetUserData(rock);
    _rocks.push_back(rock);
}

void World::createAcid(const float &x, const float &y) {
    auto body = createStaticBox(x, y, ACID_HALF_WIDTH, ACID_HALF_HEIGHT,
            ACID_FRICTION);
    auto acid = new Acid();
    body->SetUserData(acid);   // Suficiente que sea una macro
    _acids.push_back(acid);
}

void World::createButton(const size_t &id, const float &x, const float &y) {
   auto body = createStaticBox(x, y, BUTTON_HALF_WIDTH, BUTTON_HALF_HEIGHT,
           BUTTON_FRICTION);
   auto *button = new Button();
   body->SetUserData(button);
   _buttons.push_back(button);
}

void World::createGate(const size_t &id, const float &x, const float &y,
                       const std::vector<size_t>& buttons_needed,
                       const std::vector<size_t>& energy_receiver_needed) {
    auto body = createStaticBox(x, y, GATE_HALF_WIDTH, GATE_HALF_HEIGHT,
            GATE_FRICTION);
    auto *gate = new Gate();
    for (auto &button_id : buttons_needed)
        gate->addButtonNeeded(_buttons.at(button_id));
    for (auto &e_rec_id : energy_receiver_needed)
        gate->addEnergyReceiverNeeded(_energy_receivers.at(e_rec_id));
    body->SetUserData(gate);
    _gates.push_back(gate);
}

void World::createEnergyReceiver(const size_t &id, const float &x, const float &y) {
    auto body = createStaticBox(x, y, ENRG_BLOCK_HALF_LEN, ENRG_BLOCK_HALF_LEN, ENRG_BLOCK_FRICTION);
    auto e_recv = new EnergyReceiver();
    body->SetUserData(e_recv);
    _energy_receivers.push_back(e_recv);
}

void World::createEnergyTransmitter(const float &x, const float &y,
                                    const uint8_t &direction) {
    auto body = createStaticBox(x, y, ENRG_BLOCK_HALF_LEN, ENRG_BLOCK_HALF_LEN,
                                ENRG_BLOCK_FRICTION);
    auto *e_transm = new EnergyTransmitter(body, direction);
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

    auto *energy_ball = new EnergyBall(body, energy_transm->getDirection());
    body->SetUserData(energy_ball);
    _energy_balls.push_back(energy_ball);
}

void World::createChell(const float &x, const float &y, size_t id) {
//    todo: restitution necesaria ? => puede hacer sdl
    auto body = createDynamicBox(x, y, CHELL_HALF_WIDTH, CHELL_HALF_HEIGHT,
            CHELL_DENSITY);
    auto chell = new Chell(id, body);
    body->SetUserData(chell);
    _chells.push_back(chell);
}

void World::createEnergyBarrier(const float &x, const float &y,
                                const uint8_t &direction) {
    float height = 0, width = 0;
    switch (direction) {
        case O_V:
            height = BARRIER_HALF_LENGTH;
            width = BARRIER_HALF_WIDTH;
            break;
        case O_H:
            height = BARRIER_HALF_WIDTH;
            width = BARRIER_HALF_LENGTH;
            break;
        default:    // No existe este caso
            break;
    }
    auto body = createStaticBox(x, y , width, height, 0);   // Friction = 0
    auto e_barrier = new EnergyBarrier();
    body->SetUserData(e_barrier);
    _energy_barriers.push_back(e_barrier);
}

