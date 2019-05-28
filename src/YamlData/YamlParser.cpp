#include "../constants.h"
#include "RockBlockData.h"
#include "StageData.h"
#include "YamlParser.h"
#include <yaml-cpp/yaml.h>
#include <vector>

using std::vector;
using std::map;
using std::string;
using std::stof;

YamlParser::YamlParser(const string& filename) {
    std::string fname_src(YAML_PATH);
    fname_src.append(filename);
    YAML::Node file = YAML::LoadFile(fname_src);
    _config_file = file;
}

StageData YamlParser::loadStage() {
    return {_config_file["stage"]["height"].as<size_t >(),
            _config_file["stage"]["width"].as<size_t >()};
}

size_t YamlParser::loadBoxSize() {
    return _config_file["box_side_length"].as<size_t>();
}

std::vector<RockBlockData> YamlParser::loadRockBlocks() {
    vector<RockBlockData> rock_block_vector;
    vector<map<string, string>> block_data_vector = _config_file["block_rock"]
            .as<vector<map<string, string>>>();

    for (auto it : block_data_vector) {
        RockBlockData rock_block_data(stof(it["width"]), stof(it["height"]),
                stof(it["x"]), stof(it["y"]));
        rock_block_vector.push_back(rock_block_data);
    }

    return std::move(rock_block_vector);
}

std::vector<MetalBlockData> YamlParser::loadMetalBlocks() {
    vector<MetalBlockData> metal_block_vector;
    vector<map<string, string>> block_data_vector = _config_file["block_metal"]
            .as<vector<map<string, string>>>();

    for (auto it : block_data_vector) {
        MetalBlockData metal_block_data(stof(it["width"]), stof(it["height"]),
                                      stof(it["x"]), stof(it["y"]));
        metal_block_vector.push_back(metal_block_data);
    }

    return std::move(metal_block_vector);
}
