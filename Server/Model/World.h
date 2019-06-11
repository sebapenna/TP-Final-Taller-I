#ifndef TP_FINAL_ESCENARIO_H
#define TP_FINAL_ESCENARIO_H

#include "Box2D/Box2D.h"
#include "Server/Model/Chell.h"
#include "Obstacles/Rock.h"
#include "Obstacles/Button.h"
#include "Obstacles/Gate.h"
#include "EnergyBlocks/EnergyReceiver.h"
#include "EnergyBlocks/EnergyTransmitter.h"
#include "Server/Model/EnergyBall.h"
#include "Server/Model/ContactListener.h"
#include <Server/Model/GroundBlocks/RockBlock.h>
#include <Server/Model/Obstacles/Acid.h>
#include <Server/Model/GroundBlocks/MetalDiagonalBlock.h>
#include <Server/Model/GroundBlocks/MetalBlock.h>
#include <Server/Model/Obstacles/EnergyBarrier.h>
#include <vector>
#include <map>

class World {
private:
    b2World *_world;
    size_t _width;
    size_t _height;

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

    // Vector de objetos que modificaron su estado/posicion durante step
    std::vector<Collidable*> _objects_to_update;

    // Vector de pares con los datos <id, classId> de los elementos a eliminar
    std::vector<std::pair<size_t , uint8_t>> _objects_to_delete;

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
    World(const size_t &width, const size_t &height);

    // Constructor para demorar construccion hasta momento en que se tienen datos de width y height.
    World() = default;

    ~World();

    // Asignacion por movimiento.
    // PRE: solo utilizar cuando se construye nuevo World, no cuando ya se lo haya utilizado
    World& operator=(World&& other);
    World& operator=(World& other) = delete;

    // Step del world. Aplica todas las acciones ante asignadas a los distintos objetos.
    // Vacia las estructuras de elementos actualizados/eliminados antes de realizar el step.
    void step();


    /***************************************** Getters *************************************/
    size_t getWidth() const;
    size_t getHeight() const;
    b2World *getWorld() const;

    // POST [PARA TODOS LOS GETTERS DE PUNTEROS]: no continuar utilizando el puntero devuelto
    // posterior a un step, ya que podria haber sido eliminado por alguna accion, volver a utilizar
    // el metodo para verificar su existencia.
    Chell *getChell(const size_t &id);
    Rock *getRock(const size_t& id);
    Button *getButton(const size_t& id);
    Gate *getGate(const size_t& id);
    EnergyReceiver *getEnergyReceiver(const size_t& id);
    EnergyBall *getEnergyBall(const size_t& id);

    const std::vector<Chell *> &getChells() const;
    const std::vector<Rock *> &getRocks() const;
    const std::vector<Button *> &getButtons() const;
    const std::vector<Gate *> &getGates() const;
    const std::vector<EnergyReceiver *> &getEnergyReceivers() const;
    const std::vector<EnergyTransmitter *> &getEnergyTransmitters() const;
    const std::vector<RockBlock *> &getRockBlocks() const;
    const std::vector<Acid *> &getAcids() const;
    const std::vector<MetalDiagonalBlock *> &getMetalDiagonalBlocks() const;
    const std::vector<MetalBlock *> &getMetalBlocks() const;
    const std::vector<EnergyBarrier *> &getEnergyBarriers() const;

    const std::vector<Collidable *> &getObjectsToUpdate() const;
    const std::vector<std::pair<size_t, uint8_t>> &getObjectsToDelete() const;


    /******************************* Creacion Objetos **********************************/
    // PRE [PARA AMBOS CREATE BLOCK[: width y height son ancho y alto del cuerpo completo
    void createRockBlock(const float& width, const float& height, const float& x, const float& y);
    void createMetalBlock(const float& width, const float& height, const float& x, const float& y);

    // X e Y deben ser la posicion de la punta inferior izquierda, pensando el bloque diagonal
    // como un cuadrado completo, sin importar la orientacion del mismo
    void createMetalDiagonalBlock(const float& width, const float& height,
            const float& x, const float& y, const uint8_t& orientation);

    void createRock(const float& x, const float& y);
    void createAcid(const float& x, const float& y);

    // PRE: Se debe crear en orden de id creciente
    void createChell(const float &x, const float &y);

    // PRE: Se debe crear en orden de id creciente
    void createButton(const float &x, const float &y);

    // PRE: Se debe crear en orden de id creciente. Se deben haber creado los buttons y gates
    // cuyos id paso en los vectores
    void createGate(const float &x, const float &y, const std::vector<size_t> &buttons_needed,
                    const std::vector<size_t> &energy_receiver_needed);

    // PRE: Se debe crear en orden de id creciente
    void createEnergyReceiver(const float &x, const float &y);

    void createEnergyTransmitter(const float &x, const float &y, const uint8_t &direction);

    // El parametro es el transmisor origen
    void createEnergyBall(EnergyTransmitter *energy_transm);

    void createEnergyBarrier(const float& x, const float& y, const uint8_t& direction);
};


#endif //TP_FINAL_ESCENARIO_H
