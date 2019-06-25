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
#include "Server/Model/Obstacles/Cake.h"
#include "Server/Model/Shots/Portal.h"
#include "RayCastCallback.h"
#include "Server/Model/Shots/PinTool.h"
#include <Server/Model/GroundBlocks/RockBlock.h>
#include <Server/Model/Obstacles/Acid.h>
#include <Server/Model/GroundBlocks/MetalDiagonalBlock.h>
#include <Server/Model/GroundBlocks/MetalBlock.h>
#include <Server/Model/Obstacles/EnergyBarrier.h>
#include <Server/Configuration.h>
#include <Server/Model/CollidableData/CollidableData.h>
#include <vector>
#include <map>

class World {
private:
    b2World *_world;
    size_t _width;
    size_t _height;
    float _time_step, _velocity_iterations, _position_iterations;

    std::shared_ptr<Configuration> _configuration;
    ContactListener *_contact_listener;

    Cake *_cake = nullptr;
    std::vector<RockBlock *> _rock_blocks;
    std::vector<Acid *> _acids;
    std::vector<MetalDiagonalBlock *> _metal_diagonal_blocks;
    std::vector<MetalBlock *> _metal_blocks;
    std::vector<EnergyBarrier *> _energy_barriers;
    std::vector<Chell *> _chells;
    std::vector<Rock *> _rocks;
    std::vector<Button *> _buttons;
    std::vector<Gate *> _gates;
    std::vector<EnergyReceiver *> _energy_receivers;
    std::vector<EnergyTransmitter *> _energy_transmitters;
    std::map<size_t, EnergyBall *> _energy_balls;

    // Mapa que contiene pin tools y portales, ambos obejtos disparables. El incremento de ids no
    // diferenciara los unos de los otros.
    std::map<size_t, Collidable *> _shootables;


    std::vector<Collidable *> _objects_to_update; // Objetos que modificaron su estado en step
    std::vector<std::pair<size_t, uint8_t>> _objects_to_delete; // <id, classId> elementos a borrar


    // Portales/Pintools creados previo a step que deben moverse a objects_to_update
    std::vector<Collidable *> _new_shootables;
    // Vector de id de aquellos portales/pin tools que las chells decidieron eliminar o cambiaron
    // por nuevos portales/pin tools y deberan ser eliminados durante step.
    std::vector<size_t> _shootables_to_delete;

    std::vector<size_t> _want_to_kill;  // ids chells que quieren matar chell que no llego a cake

    size_t _chells_alive = 0;   // Cuenta la cantidad de chells que siguen en la partida


    // Elimina aquellos portales o pintool que ya no son utilizados por las disintas chell
    void deleteOldShootables();

    // Actualiza los ids de las chells que quieren matar a otra chell y las quita del listado en
    // caso que ya no esten en condiciones de matar a otra;
    void updateChellsWantingToKill();

    // Verifica si es posible matar a la chell que no llego a la cake y en caso de ser posible la
    // borra del juego
    void killChellIfPossible();

    // Step para los vectores de los distintos tipos de collidable
    template<class T>
    void stepCollidableVector(std::vector<T *> &vector);

    // Step para energy balls, diferenciado por ser otra estructura
    void stepEnergyBalls();

    // Step para pin tools, diferenciado por que su estado implica tareas distintas al resto
    void stepPinTools();

    // El parametro es el transmisor origen. Bola de energia es el unico elemento del cual world
    // es responsable de su creacion
    void createEnergyBall(EnergyTransmitter *energy_transm);

public:
    World(const size_t &width, const size_t &height, std::shared_ptr<Configuration> configuration);

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
    const std::map<size_t, Collidable*> &getShootables() const;

    void addAcid(Acid *acid);
    void addChell(Chell *chell);
    void addButton(Button *button);
    void addCake(Cake *cake);
    void addEnergyBarrier(EnergyBarrier *barrier);
    void addEnergyReceiver(EnergyReceiver *receiver);
    void addEnergyTransmitter(EnergyTransmitter *transmitter);
    void addGate(Gate *gate);
    void addRockBlock(RockBlock *block);
    void addMetalBlock(MetalBlock *block);
    void addMetalDiagonalBlock(MetalDiagonalBlock *block);
    void addRock(Rock *rock);
    void addShootable(const size_t& shootable_id, Collidable *shootable);
    void addShootableToDelete(const size_t& id);

    size_t getNextButtonId();
    size_t getNextReceiverId();
    size_t getNextTransmitterId();
    size_t getNextGateId();
    size_t getNextRockId();
    size_t getNextChellId();
    size_t getNextShootableId();
    size_t getNextEnergyBallId();

    // Indica que chell del id indicado decidio matar a otra chell que no llego a la cake.
    // Internamente se verifica si dicha chell esta verdaderamente en el lugar de la cake y en
    // tal caso se lo agregara al vector _want_to_kill. En caso de que la chell se aleje de la
    // cake su id sera borrado de las chells que quieren eliminar la chell restante.
    void killLastingChell(const size_t &killer_id);

    // Realiza el disparo del portal y posible creacion del mismo
    void shootPortal(const size_t &chell_id, const float &dest_x, const float &dest_y,
            const int16_t &color);

    // Elimina los portales de la chell con el id indicado
    void resetPortals(const size_t &chell_id);

    // Realiza el disparo del pin tool y posible creacion del mismo
    void shootPinTool(const size_t &chell_id, const float &dest_x, const float &dest_y);

    void createCollidable(std::shared_ptr<CollidableData> collidable_data);

    // Retorna true en caso de que todas las chells que forman parte de world estan en cake;
    bool allChellsInCake();
};


#endif //TP_FINAL_ESCENARIO_H
