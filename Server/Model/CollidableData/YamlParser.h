#ifndef PORTAL_YAMLPARSER_H
#define PORTAL_YAMLPARSER_H

#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"
#include "Server/Model/CollidableData/Data/WorldData.h"
#include "Server/Model/CollidableData/Data/RockBlockData.h"
#include "Server/Model/CollidableData/Data/MetalBlockData.h"
#include "Server/Model/CollidableData/Data/MetalDiagonalBlockData.h"
#include "Server/Model/CollidableData/Data/RockData.h"
#include "Server/Model/CollidableData/Data/AcidData.h"
#include "Server/Model/CollidableData/Data/ButtonData.h"
#include "Server/Model/CollidableData/Data/GateData.h"
#include "Server/Model/CollidableData/Data/EnergyTransmitterData.h"
#include "Server/Model/CollidableData/Data/EnergyReceiverData.h"
#include "Server/Model/CollidableData/Data/EnergyBarrierData.h"
#include "Server/Model/CollidableData/Data/ChellData.h"
#include "Server/Model/CollidableData/Data/CakeData.h"

class YamlParser {
private:
    YAML::Node _config;

public:
    explicit YamlParser(const std::string& filename);

    WorldData loadWorldData();

    size_t loadBoxSize();

    void loadRockBlocksData(std::vector<std::shared_ptr<CollidableData>> &output);

    void loadMetalBlocksData(std::vector<std::shared_ptr<CollidableData>> &output);

    void loadMetalDiagonalBlockData(std::vector<std::shared_ptr<CollidableData>> &output);

    void loadRockData(std::vector<std::shared_ptr<CollidableData>> &output);

    void loadAcidData(std::vector<std::shared_ptr<CollidableData>> &output);

    void loadButtonData(std::vector<std::shared_ptr<CollidableData>> &output);

    void loadGateData(std::vector<std::shared_ptr<CollidableData>> &output);

    void loadEnergyTransmitterData(std::vector<std::shared_ptr<CollidableData>> &output);

    void loadEnergyReceiverData(std::vector<std::shared_ptr<CollidableData>> &output);

    void loadEnergyBarrierData(std::vector<std::shared_ptr<CollidableData>> &output);

    void loadCakeData(std::vector<std::shared_ptr<CollidableData>> &output);

    // Genera un vector de todos los CollidableData presentes en el archivo yaml
    std::vector<std::shared_ptr<CollidableData>> parse();

    // Chells se cargan por separado, ya que quizas no todas las chells presentes en el archivo
    // yaml seran utilizadas
    std::vector<std::shared_ptr<CollidableData>> loadChellData();
};


#endif //PORTAL_YAMLPARSER_H
