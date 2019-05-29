#include "../constants.h"
#include "YamlParser.h"
#include <yaml-cpp/yaml.h>
#include <vector>

using std::vector;
using std::map;
using std::string;
using std::stof;
using YAML::Node;

YamlParser::YamlParser(const string& filename) {
    _config = YAML::LoadFile(filename);
}

WorldData YamlParser::loadWorldData() {
    return {_config["world"]["height"].as<size_t >(),
            _config["world"]["width"].as<size_t >()};
}

size_t YamlParser::loadBoxSize() {
    return _config["box_side_length"].as<size_t>();
}

vector<RockBlockData> YamlParser::loadRockBlocksData() {
    vector<RockBlockData> rock_block_vector;
    for (auto &it : _config["block_rock"].as<vector<Node>>()) {
        RockBlockData data(it["width"].as<float>(),
                it["height"].as<float>(),
                it["x"].as<float>(),
                it["y"].as<float>());
        rock_block_vector.push_back(data);
    }
    return std::move(rock_block_vector);
}

vector<MetalBlockData> YamlParser::loadMetalBlocksData() {
    vector<MetalBlockData> metal_block_vector;
    for (auto &it : _config["block_metal"].as<vector<Node>>()) {
        MetalBlockData data(it["width"].as<float>(),
                it["height"].as<float>(),
                it["x"].as<float>(),
                it["y"].as<float>());
        metal_block_vector.push_back(data);
    }
    return std::move(metal_block_vector);
}

vector<MetalDiagonalBlockData> YamlParser::loadMetalDiagonalBlockData() {
    vector<MetalDiagonalBlockData> metal_diagonal_block_vector;
    for (auto &it : _config["block_metal_diagonal"].as<vector<Node>>()) {
        MetalDiagonalBlockData data(it["width"].as<float>(),
                it["height"].as<float>(),
                it["x"].as<float>(),
                it["y"].as<float>(),
                it["orientation"].as<string>());
        metal_diagonal_block_vector.push_back(data);
    }
    return std::move(metal_diagonal_block_vector);
}

vector<RockData> YamlParser::loadRockData() {
    vector<RockData> rock_data_vector;
    for (auto &it : _config["rock"].as<vector<Node>>()) {
        RockData data(it["x"].as<float>(), it["y"].as<float>());
        rock_data_vector.push_back(data);
    }
    return std::move(rock_data_vector);
}

vector<AcidData> YamlParser::loadAcidData() {
    vector<AcidData> acid_data_vector;
    for (auto &it : _config["acid"].as<vector<Node>>()) {
        AcidData data(it["x"].as<float>(), it["y"].as<float>());
        acid_data_vector.push_back(data);
    }
    return std::move(acid_data_vector);
}

vector<ButtonData> YamlParser::loadButtonData() {
    vector<ButtonData> button_data_vector;
    for (auto &it : _config["button"].as<vector<Node>>()) {
        ButtonData data(it["id"].as<size_t>(),
                it["x"].as<float>(),
                it["y"].as<float>());
        button_data_vector.push_back(data);
    }
    return std::move(button_data_vector);
}

vector<GateData> YamlParser::loadGateData() {
    vector<GateData> gate_data_vector;
    for (auto &it : _config["gate"].as<vector<Node>>()) {
        GateData data(it["id"].as<size_t>(),
                      it["x"].as<float>(),
                      it["y"].as<float>());
        for (auto &sub_it : it["buttons_needed"].as<vector<Node>>())
            data.addButtonNeeded(sub_it["id"].as<size_t>());
        for (auto &sub_it : it["energy_receiver_needed"].as<vector<Node>>())
            data.addEnergyReceiverNeeded(sub_it["id"].as<size_t>());
        gate_data_vector.push_back(data);
    }
    return std::move(gate_data_vector);
}

vector<EnergyTransmitterData> YamlParser::loadEnergyTransmitterData() {
    vector<EnergyTransmitterData> e_transm_data_vector;
    for (auto &it : _config["energy_transmitter"].as<vector<Node>>()) {
        EnergyTransmitterData data(it["x"].as<float>(), it["y"].as<float>());
        e_transm_data_vector.push_back(data);
    }
    return std::move(e_transm_data_vector);
}

vector<EnergyReceiverData> YamlParser::loadEnergyReceiverData() {
    vector<EnergyReceiverData> e_receiver_data_vector;
    for (auto &it : _config["energy_receiver"].as<vector<Node>>()) {
        EnergyReceiverData data(it["id"].as<size_t>(),
                    it["x"].as<float>(),
                    it["y"].as<float>());
        e_receiver_data_vector.push_back(data);
    }
    return std::move(e_receiver_data_vector);
}

vector<EnergyBarrierData> YamlParser::loadEnergyBarrierData() {
    vector<EnergyBarrierData> e_barrier_data_vector;
    for (auto &it :  _config["energy_barrier"].as<vector<Node>>()) {
        EnergyBarrierData data(it["x"].as<float>(),
                    it["y"].as<float>(),
                    it["orientation"].as<string>());
        e_barrier_data_vector.push_back(data);
    }
    return std::move(e_barrier_data_vector);
}

vector<ChellData> YamlParser::loadChellData() {
    vector<ChellData> chell_data_vector;
    for (auto &it : _config["chell"].as<vector<Node>>()) {
        ChellData data(it["id"].as<size_t>(),
                       it["x"].as<float>(),
                       it["y"].as<float>());
        chell_data_vector.push_back(data);
    }
    return std::move(chell_data_vector);
}
