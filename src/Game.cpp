#include <src/YamlData/YamlParser.h>
#include<vector>
#include "Game.h"

using std::vector;

Game::Game(const std::string &config_file) {
    YamlParser config(config_file);

    // Configuracion stage
    StageData stage_data = config.loadStage();

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
//    _stage = new Stage(stage_data.getWidth(), stage_data.getHeight());
//stage.createBlocks
// stage.createRocks
//stage.createAcid
//stage.createButton
//stage.createGate
//stage.createBarrier

    /* Configurar bloques roca */

    /* Configurar bloques metal */

    /* Configurar bloques metal diagonal */

    /* Configurar rocas */

    /* Configurar botones */

    /* Configurar compuertas */

    /* Configurar acido */

    /* Configurar emisores energia */

    /* Configurar receptor energia */

    /* Configurar barreras energia */

}
