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
#include "Cake.h"
#include "Portal.h"
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

    std::vector<Chell *> _chells;
    std::vector<Rock *> _rocks;
    std::vector<Button *> _buttons;
    std::vector<Gate *> _gates;
    std::vector<EnergyReceiver *> _energy_receivers;
    std::vector<EnergyTransmitter *> _energy_transmitters;
    std::vector<EnergyBall *> _energy_balls;
    std::vector<size_t> _want_to_kill;  // ids chells que quiere matar chell que no llego a cake
    Cake *_cake = nullptr;
    std::map<size_t, Portal*> _portals;
    // _pin_tools ?
    // todo: YAML::Node _config => configuracion de constants.h

    // Vector de objetos que modificaron su estado/posicion durante step
    std::vector<Collidable *> _objects_to_update;

    // Vector de pares con los datos <id, classId> de los elementos a eliminar
    std::vector<std::pair<size_t, uint8_t>> _objects_to_delete;

    // Vector de id de aquellos portales que las chells decidieron eliminar o cambiaron por
    // nuevos portales y deberan ser eliminados durante step.
    std::vector<size_t> _portals_to_delete;

    /* Atributos para evitar leaks */
    ContactListener *_contact_listener;
    std::vector<RockBlock *> _rock_blocks;
    std::vector<Acid *> _acids;
    std::vector<MetalDiagonalBlock *> _metal_diagonal_blocks;
    std::vector<MetalBlock *> _metal_blocks;
    std::vector<EnergyBarrier *> _energy_barriers;
    // todo: UN SOLO VECTOR COLLIDABLE? => va a necesitar getX getY getWidth getHeight

    // box_width y box_height seran los valores que se usaran en setAsBox. Setea friccion en 0
    // por default
    b2Body *createStaticBox(const float &x, const float &y, const float &box_half_width,
                            const float &box_half_height, const float &friction = 0);

    b2Body *createDynamicBox(const float &x, const float &y, const float &box_half_width,
                             const float &box_half_height, const float &density);

    void stepEnergyBalls();

    void stepEnergyTransmitters();

    void stepEnergyReceivers();

    void stepButtons();

    void stepGates();

    void stepChells();

    void stepRocks();

    bool inConditionToKillMissingChell();

public:
    World(const size_t &width, const size_t &height);

    // Constructor para demorar construccion hasta momento en que se tienen datos de width y height.
    World() = default;

    ~World();

    // Asignacion por movimiento.
    // PRE: solo utilizar cuando se construye nuevo World, no cuando ya se lo haya utilizado
    World &operator=(World &&other);

    World &operator=(World &other) = delete;

    // Step del world. Aplica todas las acciones ante asignadas a los distintos objetos.
    // Vacia las estructuras de elementos actualizados/eliminados antes de realizar el step. Se
    // encarga de evaluar si es posible eliminar la unica chell que no esta en cake, si las demas
    // chells asi lo hubiesen decidido y eliminarla.
    void step();


    /***************************************** Getters *************************************/
    size_t getWidth() const;

    size_t getHeight() const;

    b2World *getWorld() const;

    // POST [PARA TODOS LOS GETTERS DE PUNTEROS]: no continuar utilizando el puntero devuelto
    // posterior a un step, ya que podria haber sido eliminado por alguna accion, volver a utilizar
    // el metodo para verificar su existencia. En caso de id no existir o cuerpo haber sido
    // eliminado se retornara nullptr
    Chell *getChell(const size_t &id);

    Rock *getRock(const size_t &id);

    Button *getButton(const size_t &id);

    Gate *getGate(const size_t &id);

    EnergyReceiver *getEnergyReceiver(const size_t &id);

    EnergyBall *getEnergyBall(const size_t &id);

    Cake *getCake() const;

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

    const std::map<size_t, Portal *> &getPortals() const;


    /******************************* Creacion Objetos **********************************/
    // PRE [PARA AMBOS CREATE BLOCK[: width y height son ancho y alto del cuerpo completo
    void createRockBlock(const float &width, const float &height, const float &x, const float &y);

    void createMetalBlock(const float &width, const float &height, const float &x, const float &y);

    // X e Y deben ser la posicion de la punta inferior izquierda, pensando el bloque diagonal
    // como un cuadrado completo, sin importar la orientacion del mismo
    void createMetalDiagonalBlock(const float &width, const float &height,
                                  const float &x, const float &y, const uint8_t &orientation);

    void createRock(const float &x, const float &y);

    void createAcid(const float &x, const float &y);

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

    void createEnergyBarrier(const float &x, const float &y, const uint8_t &direction);

    void createCake(const float &x, const float &y);

    // Indica que chell del id indicado decidio matar a la chell que no llego a la cake.
    // Internamente se verifica si dicha chell esta verdaderamente en el lugar de la cake y en
    // tal caso se lo agregara al vector _want_to_kill. En caso de que la chell se aleje de la
    // cake su id sera borrado de las chells que quieren eliminar la chell restante.
    void killLastingChell(const size_t &kiler_id);

    void shootPortal(const size_t &chell_id, const float &dest_x, const float &dest_y, const int16_t &color);

    // Angulo sera 0 si no hay que rotar cuerpo (colision con pared recta), 45 para rotar cuerpo
    // hacia izquierda y -45 para rotar hacia derecha (ambos casos colision cara diagonal)
    Portal * createPortal(const float &x, const float &y, b2Vec2 normal, const int16_t &color,
                          const int &angle);

    // Actualiza los ids de las chells que quieren matar a otra chell y las quita del listado en
    // caso que ya no esten en condiciones de matar a otra;
    void updateChellsWantingToKill();

    // Verifica si es posible matar a la chell que no llego a la cake y en caso de ser posible la
    // borra del juego
    void killChell();


    // Elimina aquellos portales que ya no son utilizados por las disintas chell
    void deleteOldPortals();
};


#endif //TP_FINAL_ESCENARIO_H
