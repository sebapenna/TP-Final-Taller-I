#include "../constants.h"
#include "YamlParser.h"
#include <yaml-cpp/yaml.h>
#include <vector>

using std::vector;
using std::map;
using std::string;
using std::stof;

YamlParser::YamlParser(const string& filename) {
    YAML::Node file = YAML::LoadFile(filename);
    _config = file;
}

StageData YamlParser::loadStage() {
    return {_config["stage"]["height"].as<size_t >(),
            _config["stage"]["width"].as<size_t >()};
}

size_t YamlParser::loadBoxSize() {
    return _config["box_side_length"].as<size_t>();
}

std::vector<RockBlockData> YamlParser::loadRockBlocks() {
    vector<RockBlockData> rock_block_vector;
    vector<map<string, string>> data_vector = _config["block_rock"]
            .as<vector<map<string, string>>>();

    for (auto it : data_vector) {
        RockBlockData data(stof(it["width"]), stof(it["height"]),
                stof(it["x"]), stof(it["y"]));
        rock_block_vector.push_back(data);
    }

    return std::move(rock_block_vector);
}

std::vector<MetalBlockData> YamlParser::loadMetalBlocks() {
    vector<MetalBlockData> metal_block_vector;
    vector<map<string, string>> data_vector = _config["block_metal"]
            .as<vector<map<string, string>>>();

    for (auto it : data_vector) {
        MetalBlockData data(stof(it["width"]), stof(it["height"]),
                                      stof(it["x"]), stof(it["y"]));
        metal_block_vector.push_back(data);
    }

    return std::move(metal_block_vector);
}

std::vector<MetalDiagonalBlockData> YamlParser::loadMetalDiagonalBlock() {
    vector<MetalDiagonalBlockData> metal_diagonal_block_vector;
    vector<map<string, string>> data_vector =
            _config["block_metal_diagonal"].as<vector<map<string,string>>>();

    for (auto it : data_vector) {
        MetalDiagonalBlockData data(stof(it["width"]), stof(it["height"]),
                stof(it["x"]), stof(it["y"]), it["orientation"]);
        metal_diagonal_block_vector.push_back(data);
    }

    return std::move(metal_diagonal_block_vector);
}

std::vector<RockData> YamlParser::loadRockData() {
    vector<RockData> rock_data_vector;
    vector<map<string, string>> data_vector = _config["rock"]
            .as<vector<map<string, string>>>();

    for (auto it : data_vector) {
        RockData data((size_t) stoi(it["id"]), stof(it["x"]), stof(it["y"]));
        rock_data_vector.push_back(data);
    }

    return std::move(rock_data_vector);
}

std::vector<AcidData> YamlParser::loadAcidData() {
    vector<AcidData> acid_data_vector;
    vector<map<string, string>> data_vector = _config["acid"]
            .as<vector<map<string, string>>>();

    for (auto it : data_vector) {
        AcidData data(stof(it["x"]), stof(it["y"]));
        acid_data_vector.push_back(data);
    }

    return std::move(acid_data_vector);
}

std::vector<ButtonData> YamlParser::loadButtonData() {
    vector<ButtonData> button_data_vector;
    vector<map<string, string>> data_vector = _config["button"]
            .as<vector<map<string, string>>>();

    for (auto it : data_vector) {
        ButtonData data((size_t) stoi(it["id"]), stof(it["x"]), stof(it["y"]));
        button_data_vector.push_back(data);
    }

    return std::move(button_data_vector);
}

std::vector<GateData> YamlParser::loadGateData() {
    vector<GateData> gate_data_vector;
    vector<map<string,string>> data_vector = _config["gate"]
            .as<vector<map<string, string>>>();

    for (auto it : data_vector) {
        GateData data((size_t) stoi(it["id"]), stof(it["x"]), stof(it["y"]));
//        std::cout << "botones: "<< it["buttones_needed"] << std::endl;
        gate_data_vector.push_back(data);
    }

    return gate_data_vector;
}
