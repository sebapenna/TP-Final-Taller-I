#include "Server/Model/constants.h"
#include "YamlParser.h"
#include <yaml-cpp/yaml.h>
#include <vector>

using std::vector;
using std::map;
using std::string;
using std::stof;
using YAML::Node;
using std::make_shared;

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

void YamlParser::loadRockBlocksData(std::vector<std::shared_ptr<CollidableData>> &output) {
    for (auto &it : _config["block_rock"].as<vector<Node>>()) {
        auto data = make_shared<RockBlockData>(it["width"].as<float>(), it["height"].as<float>(),
                it["x"].as<float>(), it["y"].as<float>());
        output.push_back(data);
    }
}

void YamlParser::loadMetalBlocksData(std::vector<std::shared_ptr<CollidableData>> &output) {
    for (auto &it : _config["block_metal"].as<vector<Node>>()) {
        auto data = make_shared<MetalBlockData>(it["width"].as<float>(), it["height"].as<float>(),
                it["x"].as<float>(), it["y"].as<float>());
        output.push_back(data);
    }
}

void YamlParser::loadMetalDiagonalBlockData(vector<std::shared_ptr<CollidableData>> &output) {
    for (auto &it : _config["block_metal_diagonal"].as<vector<Node>>()) {
        auto data = make_shared<MetalDiagonalBlockData>(it["width"].as<float>(),
                it["height"].as<float>(), it["x"].as<float>(), it["y"].as<float>(),
                        it["orientation"].as<string>());
        output.push_back(data);
    }
}

void YamlParser::loadRockData(std::vector<std::shared_ptr<CollidableData>> &output) {
    for (auto &it : _config["rock"].as<vector<Node>>()) {
        auto data = make_shared<RockData>(it["x"].as<float>(), it["y"].as<float>());
        output.push_back(data);
    }
}

void YamlParser::loadAcidData(std::vector<std::shared_ptr<CollidableData>> &output) {
    for (auto &it : _config["acid"].as<vector<Node>>()) {
        auto data = make_shared<AcidData>(it["x"].as<float>(), it["y"].as<float>(),
                it["width"].as<float>());
        output.push_back(data);
    }
}

void YamlParser::loadButtonData(std::vector<std::shared_ptr<CollidableData>> &output) {
    for (auto &it : _config["button"].as<vector<Node>>()) {
        auto data = make_shared<ButtonData>(it["id"].as<size_t>(), it["x"].as<float>(),
                it["y"].as<float>());
        output.push_back(data);
    }
}

void YamlParser::loadGateData(std::vector<std::shared_ptr<CollidableData>> &output) {
    for (auto &it : _config["gate"].as<vector<Node>>()) {
        auto data = make_shared<GateData>(it["id"].as<size_t>(), it["x"].as<float>(),
                it["y"].as<float>());
        try {
            for (auto &sub_it : it["buttons_needed"].as<vector<Node>>())
                data->addButtonNeeded(sub_it["id"].as<size_t>());
        } catch(...) {} // No necesita botones
        try {
            for (auto &sub_it : it["energy_receiver_needed"].as<vector<Node>>())
                data->addEnergyReceiverNeeded(sub_it["id"].as<size_t>());
        } catch(...) {} // No necesita receptores

        output.push_back(data);
    }
}

void YamlParser::loadEnergyTransmitterData(vector<std::shared_ptr<CollidableData>> &output) {
    for (auto &it : _config["energy_transmitter"].as<vector<Node>>()) {
        auto data = make_shared<EnergyTransmitterData>(it["x"].as<float>(), it["y"].as<float>(),
                it["direction"].as<string>());
        output.push_back(data);
    }
}

void YamlParser::loadEnergyReceiverData(std::vector<std::shared_ptr<CollidableData>> &output) {
    for (auto &it : _config["energy_receiver"].as<vector<Node>>()) {
        auto data = make_shared<EnergyReceiverData>(it["id"].as<size_t>(), it["x"].as<float>(),
                it["y"].as<float>());
        output.push_back(data);
    }
}

void YamlParser::loadEnergyBarrierData(std::vector<std::shared_ptr<CollidableData>> &output) {
    for (auto &it :  _config["energy_barrier"].as<vector<Node>>()) {
        auto data = make_shared<EnergyBarrierData>(it["x"].as<float>(), it["y"].as<float>(),
                it["orientation"].as<string>());
        output.push_back(data);
    }
}

void YamlParser::loadCakeData(std::vector<std::shared_ptr<CollidableData>> &output) {
    auto data = make_shared<CakeData>(_config["cake"]["x"].as<float>(),
            _config["cake"]["y"].as<float>());
    output.push_back(data);
}

std::vector<std::shared_ptr<CollidableData>> YamlParser::parse() {
    vector<std::shared_ptr<CollidableData>> output;

    loadCakeData(output);

    try {
        loadRockBlocksData(output);
    } catch(...) { } // No hay bloques roca

    try {
        loadMetalBlocksData(output);
    } catch(...) { } // No hay bloques metal

    try {
        loadMetalDiagonalBlockData(output);
    } catch(...) { } // No hay bloques metal diagonal

    try {
        loadRockData(output);
    } catch(...) { } // No hay rocas

    try {
        loadButtonData(output);
    } catch(...) { } // No hay botones

    try {
        loadAcidData(output);
    } catch(...) {  } // No hay acido

    try {
        loadEnergyTransmitterData(output);
    } catch(...) { } // No hay emisores energia

    try {
        loadEnergyReceiverData(output);
    } catch(...) { } // No hay receptores energia

    // IMPORTANTE: gates agregadas luego de receivers y buttons porque necesita referencia a ellas
    try {
        loadGateData(output);
    } catch(...) { } // No hay compuertas

    try {
        loadEnergyBarrierData(output);
    } catch(...) { } // No hay barreras energia

    return std::move(output);
}

std::vector<std::shared_ptr<CollidableData>> YamlParser::loadChellData() {
    vector<std::shared_ptr<CollidableData>> chell_data_vector;
    for (auto &it : _config["chell"].as<vector<Node>>()) {
        auto data = make_shared<ChellData>(it["id"].as<size_t>(), it["x"].as<float>(),
                       it["y"].as<float>());
        chell_data_vector.push_back(data);
    }
    return std::move(chell_data_vector);
}
