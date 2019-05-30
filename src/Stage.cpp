#include <src/YamlData/YamlParser.h>
#include<vector>
#include "Stage.h"

using std::vector;

Stage::Stage(const std::string &config_file) {
    YamlParser config(config_file);

    // Configuracion world
    WorldData world_data = config.loadWorldData();

    // Configuracion largo box
    size_t box_side_length = config.loadBoxSize();

    // Configuracion bloques roca
    vector<RockBlockData> rock_blocks_data_vector;
    try {
        rock_blocks_data_vector = config.loadRockBlocksData();
    } catch(...) { // No hay bloques roca
        rock_blocks_data_vector.clear();    // Vector vacio
    }

    // Configuracion bloques metal
    vector<MetalBlockData> metal_blocks_data_vector;
    try {
        metal_blocks_data_vector = config.loadMetalBlocksData();
    } catch(...) { // No hay bloques metal
        metal_blocks_data_vector.clear();
    }

    // Configuracion bloques metal diagonal
    vector<MetalDiagonalBlockData> metal_diagonal_blocks_data_vector;
    try {
        metal_diagonal_blocks_data_vector = config.loadMetalDiagonalBlockData();
    } catch(...) { // No hay bloques metal diagonal
        metal_diagonal_blocks_data_vector.clear();
    }

    // Configuracion rocas
    vector<RockData> rocks_vector;
    try {
        rocks_vector = config.loadRockData();
    } catch(...) { // No hay rocas
        rocks_vector.clear();
    }

    // Configuracion botones
    vector<ButtonData> buttons_vector;
    try {
        buttons_vector = config.loadButtonData();
    } catch(...) { // No hay botones
        buttons_vector.clear();
    }

    // Configuracion acido
    vector<AcidData> acid_vector;
    try {
        acid_vector = config.loadAcidData();
    } catch(...) {  // No hay acido
        acid_vector.clear();
    }

    // Configuracion compuertas
    vector<GateData> gates_vector;
    try {
        gates_vector = config.loadGateData();
    } catch(...) {  // No hay compuertas
        gates_vector.clear();
    }

    // Configuracion transmisores energia
    vector<EnergyTransmitterData> e_transm_vector;
    try {
        e_transm_vector = config.loadEnergyTransmitterData();
    } catch(...) {  // No hay emisores energia
        e_transm_vector.clear();
    }

    // Configuracion receptores energia
    vector<EnergyReceiverData> e_receiver_vector;
    try {
        e_receiver_vector = config.loadEnergyReceiverData();
    } catch(...) {  // No hay receptores energia
        e_receiver_vector.clear();
    }

    // Configuracion barreras energia
    vector<EnergyBarrierData> e_barrier_vector;
    try {
        e_barrier_vector = config.loadEnergyBarrierData();
    } catch(...) {  // No hay barreras eergia
        e_barrier_vector.clear();
    }

    // Configuracion chells
    vector<ChellData> chells_vector;
    try {
        chells_vector = config.loadChellData();
    } catch(...) {  // No hay chells
        chells_vector.clear();
    }



    // initializeStage(todos los vectores)
    _world = new World(world_data.getWidth(), world_data.getHeight());
    for (auto &it : rock_blocks_data_vector)
        _world->createRockBlock(it.getWidth(), it.getHeight(), it.getX(),
                it.getY());

    for (auto &it : metal_blocks_data_vector)
        _world->createMetalBlock(it.getWidth(), it.getHeight(), it.getX(),
                it.getY());

    for (auto &it : metal_diagonal_blocks_data_vector)
        _world->createMetalDiagonalBlock(it.getWidth(), it.getHeight(),
                it.getX(), it.getY(), it.getOrientation());

    for (auto &it : rocks_vector)
        _world->createRock(it.getX(), it.getY());

    for (auto &it : acid_vector)
        _world->createAcid(it.getX(), it.getY());

    for (auto &it : buttons_vector)
        _world->createButton(it.getId(), it.getX(), it.getY());

    for (auto &it : gates_vector)
        _world->createGate(it.getId(), it.getX(), it.getY(),
                it.getButtonsNeeded(), it.getEnergyReceiversNeeded());

    /* Configurar emisores energia */

    /* Configurar receptor energia */

    /* Configurar barreras energia */

}
