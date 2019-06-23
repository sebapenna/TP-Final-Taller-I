#include <Server/Model/constants.h>
#include <Server/Model/Shots/Shooter.h>
#include <yaml-cpp/yaml.h>
#include <algorithm>
#include <memory>
#include <iostream>
#include "World.h"

using std::remove_if;
using std::vector;
using std::for_each;
using std::string;
using std::shared_ptr;

World::World(const size_t &width, const size_t &height, shared_ptr<Configuration> c) :
_width(width), _height(height), _configuration(c) {
    b2Vec2 gravity(c->getGravityX(), c->getGravityY());
    _velocity_iterations = c->getVelocityIterations();
    _position_iterations = c->getPositionIterations();
    _time_step = 1 / c->getFps();
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

template<class T>
void deletePointerMap(std::map<size_t, T> &v) {
    for_each(v.begin(), v.end(), [](std::pair<size_t, T> p) {
        delete p.second;
        p.second = nullptr;
    });
}

World::~World() {
    deletePointerVector<Chell*>(_chells);
    deletePointerVector<RockBlock*>(_rock_blocks);
    deletePointerVector<Button*>(_buttons);
    deletePointerVector<Gate*>(_gates);
    deletePointerVector<Acid*>(_acids);
    deletePointerVector<EnergyTransmitter*>(_energy_transmitters);
    deletePointerVector<EnergyReceiver*>(_energy_receivers);
    deletePointerVector<Rock*>(_rocks);
    deletePointerVector<MetalDiagonalBlock*>(_metal_diagonal_blocks);
    deletePointerVector<MetalBlock*>(_metal_blocks);
    deletePointerVector<EnergyBarrier*>(_energy_barriers);
    deletePointerMap<EnergyBall*>(_energy_balls);
    deletePointerMap<Collidable*>(_shootables);
    delete _cake;
    delete _contact_listener;
    delete _world;
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

/******************************************* Step **********************************************/
void World::updateChellsWantingToKill() {
    _want_to_kill.erase(remove_if(_want_to_kill.begin(), _want_to_kill.end(), [this](size_t &id) {
        // Borro si se alejo de cake o murio
        auto chell = getChell(id);
        return (chell) ? !chell->reachedCake() : true;
    }), _want_to_kill.end());
}

bool World::inConditionToKillMissingChell() {
    if (_chells.size() == 1)    // Tengo solo un chell
        return false;
    return (_want_to_kill.size() == (_chells.size() - 1));
}

void World::killChell() {
    if (inConditionToKillMissingChell())
        for (int i = 0; i < _chells.size(); ++i)
            if (auto chell = _chells[i])
                if (!chell->reachedCake()) {    // Elimino chell que no estaba en Cake
                    _world->DestroyBody(chell->getBody());
                    _objects_to_delete.emplace_back(i, chell->classId());
                    delete chell;
                    _chells[i] = nullptr;
                }
}

void World::deleteOldShootables() {
    for (auto &id : _shootables_to_delete) {
        auto shootable = _shootables.find(id);  // Id peretence a un shootable existente
        if (shootable != _shootables.end()) {
            if (shootable->second->classId() == PORTAL) {
                auto p = (Portal*) shootable->second;
                _world->DestroyBody(p->getBody());
            } else {
                auto p = (PinTool*) shootable->second;
                _world->DestroyBody(p->getBody());
            }
            _objects_to_delete.emplace_back(id, shootable->second->classId());
            delete shootable->second;
            shootable->second = nullptr;
            _shootables.erase(id);
        }
    }
    _shootables_to_delete.clear(); // Vacio vector shootables a eliminar
}


void World::step() {
    // Vacio estructuras de objetos actualizados/eliminados durante step
    _objects_to_update.clear();
    _objects_to_delete.clear();
    _world->Step(_time_step, _velocity_iterations, _position_iterations);
    // Orden de acciones: primero las que su estado afectan a otros
    stepCollidableVector<EnergyTransmitter>(_energy_transmitters);
    stepEnergyBalls();
    stepCollidableVector<Button>(_buttons);
    stepCollidableVector<EnergyReceiver>(_energy_receivers);
    stepCollidableVector<Gate>(_gates);
    stepCollidableVector<Chell>(_chells);
    stepCollidableVector<Rock>(_rocks);
    // Primero realizo step de pin tools y luego deleteOldShootables para eliminar los que
    // finalizo su tiempo de vida
    stepPinTools();
    for (auto &shot_object : _new_shootables)
        _objects_to_update.push_back(shot_object);   // Agrego nuevos portales
    _new_shootables.clear();
    deleteOldShootables();
    updateChellsWantingToKill();
    killChell();
}

template <class T>
void World::stepCollidableVector(std::vector<T *> &vector) {
    for (int i = 0; i < vector.size(); ++i) {
        auto collidable = vector[i];
        if (collidable) {    // Verifico no haberlo eliminado previamente
            collidable->step(_time_step);
            if (collidable->isDead(_time_step)) {
                if (collidable->classId() == CHELL) {
                    auto chell = (Chell*) collidable;
                    resetPortals(chell->id());  // Elimino portales de chell muerta
                }
                _world->DestroyBody(collidable->getBody());
                _objects_to_delete.emplace_back(i, collidable->classId());
                delete collidable;
                collidable = nullptr;
                vector[i] = nullptr;
            } else if (collidable->actedDuringStep()) {
                if (collidable->classId() == ENERGY_TRANSMITTER) // Accion de transmisor crea bola
                    this->createEnergyBall((EnergyTransmitter*) collidable);
                _objects_to_update.push_back(collidable);
            }
        }
    }
}

void World::stepPinTools() {
    for (auto &shootable : _shootables) {
        if (shootable.second) {
            if (shootable.second->classId() == PIN_TOOL) {
                auto pintool = (PinTool *) shootable.second;
                pintool->step(_time_step);
                if (pintool->isDead(_time_step)) {
                    _shootables_to_delete.push_back(pintool->id()); // Se eliminan posteriormente
                    auto chell = getChell(pintool->getOwnerChellId());
                    chell->resetPinTool();
                }
            }
        }
    }
}

void World::stepEnergyBalls() {
    for (int i = 0; i < _energy_balls.size(); ++i) {
        auto energy_ball = _energy_balls[i];
        if (energy_ball) { // Verifico no haberlo eliminado previamente
            energy_ball->step(_time_step);
            if (energy_ball->isDead(_time_step)) {
                _world->DestroyBody(energy_ball->getBody());
                _objects_to_delete.emplace_back(energy_ball->id(), energy_ball->classId());
                _energy_balls.erase(energy_ball->id());
                delete energy_ball;
            } else if (energy_ball->actedDuringStep()) {
                _objects_to_update.push_back(energy_ball);
            }
        }
    }
}

void World::killLastingChell(const size_t &killer_id) {
    auto chell = getChell(killer_id);
    if (chell->reachedCake()) {
        // Agrego solamente si no habia sido previamente agregado y llego a Cake
        if (std::find(_want_to_kill.begin(), _want_to_kill.end(), killer_id) == _want_to_kill.end())
            _want_to_kill.push_back(killer_id);
    }
}

/****************************************** Getters **********************************************/
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

const vector<Collidable *> &World::getObjectsToUpdate() const {
    return _objects_to_update;
}

const vector<std::pair<size_t, uint8_t>> &World::getObjectsToDelete() const {
    return _objects_to_delete;
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

const std::map<size_t, Collidable *> &World::getShootables() const {
    return _shootables;
}

Cake *World::getCake() const {
    return _cake;
}

/***************************************** Id Getter *******************************************/
size_t World::getNextButtonId() {
    return _buttons.size();
}

size_t World::getNextReceiverId() {
    return _energy_receivers.size();
}

size_t World::getNextTransmitterId() {
    return _energy_transmitters.size();
}

size_t World::getNextGateId() {
    return _gates.size();
}

size_t World::getNextRockId() {
    return _rocks.size();
}

size_t World::getNextChellId() {
    return _chells.size();
}

size_t World::getNextShootableId() {
    size_t next_id = 0;
    if (!_shootables.empty())
        next_id = _shootables.rbegin()->first + 1;    // Obtengo id del ultimo elemento (mayor id)
    return next_id;
}


size_t World::getNextEnergyBallId() {
    size_t next_id = 0;
    if (!_energy_balls.empty())
        next_id = _energy_balls.rbegin()->first + 1;    // Obtengo id del ultimo elemento (mayor id)
    return next_id;
}

/***************************************** Setters / Adders ************************************/
void World::addAcid(Acid *acid) {
    _acids.push_back(acid);
}

void World::addButton(Button *button) {
    _buttons.push_back(button);
}

void World::addCake(Cake *cake) {
    _cake = cake;
}

void World::addEnergyBarrier(EnergyBarrier *barrier) {
    _energy_barriers.push_back(barrier);
}

void World::addEnergyReceiver(EnergyReceiver *receiver) {
    _energy_receivers.push_back(receiver);
}

void World::addEnergyTransmitter(EnergyTransmitter *transmitter) {
    _energy_transmitters.push_back(transmitter);
}

void World::addGate(Gate *gate) {
    _gates.push_back(gate);
}

void World::addMetalBlock(MetalBlock *block) {
    _metal_blocks.push_back(block);
}

void World::addMetalDiagonalBlock(MetalDiagonalBlock *block) {
    _metal_diagonal_blocks.push_back(block);
}

void World::addRockBlock(RockBlock *block) {
    _rock_blocks.push_back(block);
}

void World::addRock(Rock *rock) {
    _rocks.push_back(rock);
}

void World::addChell(Chell *chell) {
    _chells.push_back(chell);
}

void World::addShootable(const size_t& shootable_id, Collidable *shootable) {
    _shootables.insert({shootable_id, shootable});
    _new_shootables.push_back(shootable); // Agrego a vector de objetos que se deben actualizar
}

void World::addShootableToDelete(const size_t& id) {
    _shootables_to_delete.push_back(id);
}


/*********************************** Create Bodies *****************************************/
void World::createCollidable(std::shared_ptr<CollidableData> collidable_data) {
    collidable_data->build(this, _configuration);
}

void World::createEnergyBall(EnergyTransmitter *energy_transm) {
    float x = energy_transm->x(), y = energy_transm->y();
    // Sumo delta para evitar posible colision con el transmisor
    float dist_to_ball_center = _configuration->getEnergyBlockHalfLen() +
            _configuration->getEnergyBallRadius() + DELTA_POS;
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
    // Reduzco tamaño para evitar contacto por delta
    shape.m_radius = _configuration->getEnergyBallRadius() - DELTA_POS;

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = _configuration->getEnergyBallDensity();
    fixture.restitution = 1;    // Debe rebotar contra ciertos cuerpos

    b2Body *body = _world->CreateBody(&body_def);
    body->CreateFixture(&fixture);

    auto *energy_ball = new EnergyBall(getNextEnergyBallId(), body, energy_transm->getDirection(),
            _configuration->getEnergyBallRadius(), _configuration->getEnergyBallLifetime(),
            _configuration->getEnergyBallForce());
    body->SetUserData(energy_ball);
    _energy_balls.emplace(energy_ball->id(), energy_ball);
}

/***************************************** Shootables *******************************************/
void World::shootPinTool(const size_t &chell_id, const float &dest_x, const float &dest_y) {
    auto chell = getChell(chell_id);
    if (!chell)
        return;
    chell->shoot(); // Registro que chell disparo
    Shooter::shoot(this, chell, dest_x, dest_y, _configuration);
}

void World::shootPortal(const size_t &chell_id, const float &dest_x, const float &dest_y,
                        const int16_t &colour) {
    auto chell = getChell(chell_id);
    if (!chell)
        return;
    chell->shoot(); // Registro que chell disparo
    Shooter::shoot(this, chell, dest_x, dest_y, colour, _configuration);
}

void World::resetPortals(const size_t &chell_id) {
    auto chell = getChell(chell_id);
    auto portals_ids = chell->resetPortals();
    // Verifico si chell tenia portales y los agrego a portales a eliminar
    if (portals_ids.first != -1)
        _shootables_to_delete.push_back(portals_ids.first);
    if (portals_ids.second != -1)
        _shootables_to_delete.push_back(portals_ids.second);
}
