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
#include "ContactListener.h"
#include <vector>
#include <map>
#include <src/GroundBlocks/RockBlock.h>
#include <src/Obstacles/Acid.h>
#include <src/GroundBlocks/MetalDiagonalBlock.h>
#include <src/GroundBlocks/MetalBlock.h>
#include <src/Obstacles/EnergyBarrier.h>

class World {
private:
    b2World *_world;
    const size_t _width;
    const size_t _height;
    std::vector<Chell*> _chells;    //todo: flagDead en chell
    std::vector<Rock*> _rocks; //todo: ->vector y flagDead
    std::vector<Button*> _buttons;
    std::vector<Gate*> _gates;
    std::vector<EnergyReceiver*> _energy_receivers;
    std::vector<EnergyTransmitter*> _energy_transmitters;
    std::vector<EnergyBall*> _energy_balls;
    // _portals ?
    // _pin_tools ?
    // todo: YAML::Node _config => configuracion de constants.h

    /* Atributos para evitar leaks */
    ContactListener* _contact_listener; // Referencia para evitar leak
    std::vector<RockBlock*> _rock_blocks;
    std::vector<Acid*> _acids;
    std::vector<MetalDiagonalBlock*> _metal_diagonal_blocks;
    std::vector<MetalBlock*> _metal_blocks;
    std::vector<EnergyBarrier*> _energy_barriers;

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

    const std::vector<Button *> &getButtons() const;

    const std::vector<Gate *> &getGates() const;

    const std::vector<EnergyReceiver *> &getEnergyReceivers() const;

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
