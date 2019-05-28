#include <src/YamlData/YamlParser.h>
#include "Game.h"
#include<vector>

using std::vector;

Game::Game(const std::string &config_file) {
    YamlParser config(config_file);

    StageData stage_data = config.loadStage();

    size_t box_side_length = config.loadBoxSize();

    vector<RockBlockData> rock_blocks_data_vector;
    try {
        rock_blocks_data_vector = config.loadRockBlocks();
    } catch (...) { // No hay bloques roca
        rock_blocks_data_vector.clear();    // Vector vacio
    }

    vector<MetalBlockData> metal_blocks_data_vector;
    try {
        metal_blocks_data_vector = config.loadMetalBlocks();
    } catch (...) { // No hay bloques metal
        metal_blocks_data_vector.clear();
    }

//    _stage = new Stage(stage_data.getWidth(), stage_data.getHeight());

}
