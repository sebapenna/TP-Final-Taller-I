#ifndef PORTAL_YAMLPARSER_H
#define PORTAL_YAMLPARSER_H

#include <string>
#include "yaml-cpp/yaml.h"
#include "StageData.h"
#include "RockBlockData.h"
#include "MetalBlockData.h"
#include "MetalDiagonalBlockData.h"
#include "RockData.h"
#include "AcidData.h"
#include "ButtonData.h"
#include "GateData.h"

class YamlParser {
private:
    YAML::Node _config;

public:
    explicit YamlParser(const std::string& filename);

    StageData loadStage();

    size_t loadBoxSize();

    std::vector<RockBlockData> loadRockBlocks();

    std::vector<MetalBlockData> loadMetalBlocks();

    std::vector<MetalDiagonalBlockData> loadMetalDiagonalBlock();

    std::vector<RockData> loadRockData();

    std::vector<AcidData> loadAcidData();

    std::vector<ButtonData> loadButtonData();


    std::vector<GateData> loadGateData();
//
//    std::vector<EnergyTransmitterData> loadEnergyTransmitterData();
//
//    std::vector<EnergyReceiverData> loadEnergyReceiverData();
//
//    std::vector<EnergyBarrierData> loadEnergyBarrierData();
};


#endif //PORTAL_YAMLPARSER_H
