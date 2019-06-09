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
#include <Server/GroundBlocks/RockBlock.h>
#include <Server/Obstacles/Acid.h>
#include <Server/GroundBlocks/MetalDiagonalBlock.h>
#include <Server/GroundBlocks/MetalBlock.h>
#include <Server/Obstacles/EnergyBarrier.h>
#include <vector>
#include <map>
#include <list>

class World {
private:
    b2World *_world;
    const size_t _width;
    const size_t _height;
    std::vector<Chell*> _chells;
    std::vector<Rock*> _rocks;
    std::vector<Button*> _buttons;
    std::vector<Gate*> _gates;
    std::vector<EnergyReceiver*> _energy_receivers;
    std::vector<EnergyTransmitter*> _energy_transmitters;
    std::vector<EnergyBall*> _energy_balls;
    // _portals ?
    // _pin_tools ?
    // todo: YAML::Node _config => configuracion de constants.h

    // Vector para llevar registro de objetos que modificaron su estado/posicion durante step
    std::vector<Collidable*> _objects_to_update;
    // Lista con id e identificador de la clase para los objetos que tendran que ser eliminados
    std::list<std::pair<unsigned int ,std::string>> _objects_to_delete;

    /* Atributos para evitar leaks */
    ContactListener* _contact_listener;
    std::vector<RockBlock*> _rock_blocks;
    std::vector<Acid*> _acids;
    std::vector<MetalDiagonalBlock*> _metal_diagonal_blocks;
    std::vector<MetalBlock*> _metal_blocks;
    std::vector<EnergyBarrier*> _energy_barriers;


    // box_width y box_height seran los valores que se usaran en setAsBox
    b2Body *createStaticBox(const float &x, const float &y, const float &box_half_width,
                            const float &box_half_height, const float &friction);

    b2Body *createDynamicBox(const float &x, const float &y, const float &box_half_width,
                            const float &box_half_height, const float &density);

    void stepEnergyBalls();
    void stepEnergyTransmitters();
    void stepEnergyReceivers();
    void stepButtons();
    void stepGates();
    void stepChells();
    void stepRocks();


public:
    // todo: archivo yaml en el constructor
    World(const size_t &width, const size_t &height);

    ~World();

    void step();

    size_t getWidth() const;

    size_t getHeight() const;

    b2World *getWorld() const;

    // POST: no continuar utilizando el puntero devuelto posterior a un step, ya que podria haber
    //  sido eliminado por alguna accion, volver a utilizar el metodo para verificar su existencia.
    Chell *getChell(const size_t &id);
    Rock *getRock(const size_t& id);
    Button *getButton(const size_t& id);
    Gate *getGate(const size_t& id);
    EnergyReceiver *getEnergyReceiver(const size_t& id);
    EnergyBall *getEnergyBall(const size_t& id);

    void createChell(const float &x, const float &y, size_t id);

    /* WIDT Y HEIGHT ES DE EL TOTAL DEL CUERPO */
    void createRockBlock(const float& width, const float& height,
            const float& x, const float& y);

    void createMetalBlock(const float& width, const float& height,
            const float& x, const float& y);

    // X e Y deben ser la posicion de la punta inferior izquierda, pensando el bloque diagonal
    // como un cuadrado completo, sin importar la orientacion del mismo
    void createMetalDiagonalBlock(const float& width, const float& height,
            const float& x, const float& y, const uint8_t& orientation);

    void createRock(const float& x, const float& y);

    void createAcid(const float& x, const float& y);

    void createButton(const size_t& id, const float& x, const float& y);

    void createGate(const size_t& id, const float& x, const float& y,
            const std::vector<size_t>& buttons_needed,
            const std::vector<size_t>& energy_receiver_needed);

    void createEnergyReceiver(const size_t& id, const float& x, const float& y);

    void createEnergyTransmitter(const float &x, const float &y, const uint8_t &direction);

    // El parametro es el transmisor origen
    void createEnergyBall(EnergyTransmitter *energy_transm);

    void createEnergyBarrier(const float& x, const float& y, const uint8_t& direction);
};


#endif //TP_FINAL_ESCENARIO_H
