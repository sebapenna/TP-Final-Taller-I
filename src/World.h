#ifndef TP_FINAL_ESCENARIO_H
#define TP_FINAL_ESCENARIO_H

#include "Box2D/Box2D.h"
#include "Chell.h"
#include "Obstacles/Rock.h"
#include "Obstacles/Button.h"
#include "Obstacles/Gate.h"
#include "EnergyBlocks/EnergyReceiver.h"
#include "EnergyBlocks/EnergyTransmitter.h"
#include "EnergyBall.h"
#include <vector>
#include <map>

class World {
private:
    b2World *_world;
    const size_t _width;
    const size_t _height;
    std::map<size_t, Chell*> _chells;    //todo: ->vector y flagDead en chell
    std::vector<Rock*> _rocks; //todo: ->vector y flagDead
    std::map<size_t, Button*> _buttons; //todo: ->vector
    std::map<size_t, Gate*> _gates; //todo: ->vector
    std::map<size_t, EnergyReceiver*> _energy_receivers; //todo: ->vector
    std::vector<EnergyTransmitter*> _energy_transmitters;
    std::vector<EnergyBall*> _energy_balls;
    // _portals ?
    // _pin_tools ?
    // todo: YAML::Node _config => configuracion de constants.h

    // box_width y box_height seran los valores que se usaran en setAsBox
    b2Body *createStaticBox(const float &x, const float &y,
                            const float &box_half_width,
                            const float &box_half_height,
                            const float &friction);

    b2Body *createDynamicBox(const float &x, const float &y,
                            const float &box_half_width,
                            const float &box_half_height,
                            const float &density);

public:
    // todo: archivo yaml en el constructor
    World(size_t width, size_t height);

    ~World();

    void step();

    size_t getWidth() const;

    size_t getHeight() const;

    Chell *getChell(size_t id);

    const std::vector<Rock *> &getRocks() const;

    const std::map<size_t, Button *> &getButtons() const;

    const std::map<size_t, Gate *> &getGates() const;

    const std::map<size_t, EnergyReceiver *> &getEnergyReceivers() const;

    const std::vector<EnergyBall *> &getEnergyBalls() const;

    b2World *getWorld() const;

    void createChell(const float &x, const float &y, size_t id);

    /* WIDT Y HEIGHT ES DE EL TOTAL DEL CUERPO */
    void createRockBlock(const float& width, const float& height,
            const float& x, const float& y);

    void createMetalBlock(const float& width, const float& height,
            const float& x, const float& y);

    // X e Y deben ser la posicion de la punta inferior izquierda, pensando
    // el bloque diagonal como un cuadrado completo, sin importar la
    // orientacion del mismo
    void createMetalDiagonalBlock(const float& width, const float& height,
            const float& x, const float& y, const uint8_t& orientation);

    void createRock(const float& x, const float& y);

    void createAcid(const float& x, const float& y);

    void createButton(const size_t& id, const float& x, const float& y);

    void createGate(const size_t& id, const float& x, const float& y,
            const std::vector<size_t>& buttons_needed,
            const std::vector<size_t>& energy_receiver_needed);

    void createEnergyReceiver(const size_t& id, const float& x, const float& y);

    void createEnergyTransmitter(const float &x, const float &y,
                                 const uint8_t &direction);

    // El parametro es el transmisor origen
    void createEnergyBall(EnergyTransmitter *energy_transm);

    void createEnergyBarrier(const float& x, const float& y,
            const uint8_t& direction);
};


#endif //TP_FINAL_ESCENARIO_H
