#ifndef PORTAL_YAMLPARSER_H
#define PORTAL_YAMLPARSER_H

#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"
#include "WorldData.h"
#include "RockBlockData.h"
#include "MetalBlockData.h"
#include "MetalDiagonalBlockData.h"
#include "RockData.h"
#include "AcidData.h"
#include "ButtonData.h"
#include "GateData.h"
#include "EnergyTransmitterData.h"
#include "EnergyReceiverData.h"
#include "EnergyBarrierData.h"
#include "ChellData.h"
#include "CakeData.h"

class YamlParser {
private:
    YAML::Node _config;

public:
    explicit YamlParser(const std::string& filename);

    WorldData loadWorldData();

    size_t loadBoxSize();

    std::vector<RockBlockData> loadRockBlocksData();

    std::vector<MetalBlockData> loadMetalBlocksData();

    std::vector<MetalDiagonalBlockData> loadMetalDiagonalBlockData();

    std::vector<RockData> loadRockData();

    std::vector<AcidData> loadAcidData();

    std::vector<ButtonData> loadButtonData();

    std::vector<GateData> loadGateData();

    std::vector<EnergyTransmitterData> loadEnergyTransmitterData();

    std::vector<EnergyReceiverData> loadEnergyReceiverData();

    std::vector<EnergyBarrierData> loadEnergyBarrierData();

    std::vector<ChellData> loadChellData();

    CakeData loadCakeData();
};


#endif //PORTAL_YAMLPARSER_H
