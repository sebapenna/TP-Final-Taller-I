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
        rock_blocks_data_vector = config.loadRockBlocks();
    } catch (...) { // No hay bloques roca
        rock_blocks_data_vector.clear();    // Vector vacio
    }

    // Configuracion bloques metal
    vector<MetalBlockData> metal_blocks_data_vector;
    try {
        metal_blocks_data_vector = config.loadMetalBlocks();
    } catch (...) { // No hay bloques metal
        metal_blocks_data_vector.clear();
    }

    // Configuracion bloques metal diagonal
    vector<MetalDiagonalBlockData> metal_diagonal_blocks_data_vector;
    try {
        metal_diagonal_blocks_data_vector = config.loadMetalDiagonalBlock();
    } catch (...) { // No hay bloques metal diagonal
        metal_diagonal_blocks_data_vector.clear();
    }

    //    loadRockData();

//   loadButtonData();

//    loadAcidData();
//
//    loadGateData();
//
//    loadEnergyTransmitterData();
//
//    loadEnergyReceiverData();
//
//    loadEnergyBarrierData();

//    _stage = new Stage(stage_data.getWidth(), stage_data.getHeight());

}
