#include<vector>
#include "Stage.h"
#include "WorldObjectDTOTranslator.h"
#include "DTOProcessor.h"

using std::vector;
using std::shared_ptr;
using std::move;
using std::for_each;


Stage::~Stage() {
    delete _world;
}

Stage::Stage(std::string &&config_file) {
    YamlParser config(config_file);
    // Configuracion world
    WorldData world_data = config.loadWorldData();
    // Configuracion largo box
    size_t box_side_length = config.loadBoxSize();

    // Configuracion bloques roca
    vector<RockBlockData> rock_blocks_vec;
    try {
        rock_blocks_vec = config.loadRockBlocksData();
    } catch(...) { } // No hay bloques roca

    // Configuracion bloques metal
    vector<MetalBlockData> metal_blocks_vec;
    try {
        metal_blocks_vec = config.loadMetalBlocksData();
    } catch(...) { } // No hay bloques metal

    // Configuracion bloques metal diagonal
    vector<MetalDiagonalBlockData> metal_diag_blocks_vec;
    try {
        metal_diag_blocks_vec = config.loadMetalDiagonalBlockData();
    } catch(...) { } // No hay bloques metal diagonal

    // Configuracion rocas
    vector<RockData> rocks_vec;
    try {
        rocks_vec = config.loadRockData();
    } catch(...) { } // No hay rocas

    // Configuracion botones
    vector<ButtonData> buttons_vec;
    try {
        buttons_vec = config.loadButtonData();
    } catch(...) { } // No hay botones

    // Configuracion acido
    vector<AcidData> acid_vec;
    try {
        acid_vec = config.loadAcidData();
    } catch(...) {  } // No hay acido

    // Configuracion compuertas
    vector<GateData> gates_vec;
    try {
        gates_vec = config.loadGateData();
    } catch(...) { } // No hay compuertas

    // Configuracion transmisores energia
    vector<EnergyTransmitterData> e_transm_vec;
    try {
        e_transm_vec = config.loadEnergyTransmitterData();
    } catch(...) { } // No hay emisores energia

    // Configuracion receptores energia
    vector<EnergyReceiverData> e_receiver_vec;
    try {
        e_receiver_vec = config.loadEnergyReceiverData();
    } catch(...) { } // No hay receptores energia

    // Configuracion barreras energia
    vector<EnergyBarrierData> e_barrier_vec;
    try {
        e_barrier_vec = config.loadEnergyBarrierData();
    } catch(...) { } // No hay barreras eergia

    // Configuracion chells
    try {
        _available_chells = config.loadChellData();
    } catch(...) { } // No hay chells


    /******************** Inicializo World *********************/
    _world = new World(world_data.getWidth(), world_data.getHeight());

    for_each(rock_blocks_vec.begin(), rock_blocks_vec.end(), [this](RockBlockData &e) {
       _world->createRockBlock(e.getWidth(), e.getHeight(), e.getX(), e.getY());
    });

    for_each(metal_blocks_vec.begin(), metal_blocks_vec.end(), [this](MetalBlockData &e) {
        _world->createMetalBlock(e.getWidth(), e.getHeight(), e.getX(), e.getY());
    });

    for_each(metal_diag_blocks_vec.begin(), metal_diag_blocks_vec.end(),
            [this](MetalDiagonalBlockData &e) { _world->createMetalDiagonalBlock(e.getWidth(),
                    e.getHeight(), e.getX(), e.getY(), e.getOrientation());
    });

    for_each(rocks_vec.begin(), rocks_vec.end(), [this](RockData &e) {
        _world->createRock(e.getX(), e.getY());
    });

    for_each(acid_vec.begin(), acid_vec.end(), [this](AcidData &e) {
        _world->createAcid(e.getX(), e.getY());
    });

    for_each(buttons_vec.begin(), buttons_vec.end(), [this](ButtonData &e) {
        _world->createButton(e.getX(), e.getY());
    });

    for_each(e_receiver_vec.begin(), e_receiver_vec.end(), [this](EnergyReceiverData &e) {
        _world->createEnergyReceiver(e.getX(), e.getY());
    });

    // IMPORTANTE: gates creada luego de receivers y buttons porque necesea referencia a ellas
    for_each(gates_vec.begin(), gates_vec.end(), [this](GateData &e) {
        _world->createGate(e.getX(), e.getY(), e.getButtonsNeeded(), e.getEnergyReceiversNeeded());
    });

    for_each(e_transm_vec.begin(), e_transm_vec.end(), [this](EnergyTransmitterData &e) {
        _world->createEnergyTransmitter(e.getX(), e.getY(), e.getDirection());
    });

    for_each(e_barrier_vec.begin(), e_barrier_vec.end(), [this](EnergyBarrierData &e) {
        _world->createEnergyBarrier(e.getX(), e.getY(), e.getOrientation());
    });
}

void Stage::createChells(const size_t &n_players) {
    for (size_t i = 0; i < n_players; ++i) {
        auto chell = _available_chells[i];
        _world->createChell(chell.getX(), chell.getY());
    }
}

vector<shared_ptr<ProtocolDTO>> Stage::getInitialConfiguration() {
    vector<shared_ptr<ProtocolDTO>> output;
    _processor.createDTOs<RockBlock *>(_world->getRockBlocks(), output, true);
    _processor.createDTOs<MetalBlock *>(_world->getMetalBlocks(), output, true);
    _processor.createDTOs<MetalDiagonalBlock *>(_world->getMetalDiagonalBlocks(), output, true);
    _processor.createDTOs<EnergyTransmitter *>(_world->getEnergyTransmitters(), output, true);
    _processor.createDTOs<EnergyReceiver *>(_world->getEnergyReceivers(), output, true);
    _processor.createDTOs<Acid *>(_world->getAcids(), output, true);
    _processor.createDTOs<Button *>(_world->getButtons(), output, true);
    _processor.createDTOs<Gate *>(_world->getGates(), output, true);
    _processor.createDTOs<EnergyBarrier *>(_world->getEnergyBarriers(), output, true);
    _processor.createDTOs<Chell *>(_world->getChells(), output, true);
    _processor.createDTOs<Rock *>(_world->getRocks(), output, true);
    return move(output);
}

void Stage::apply(ProtocolDTO *dto, const size_t& player_id) {
    _processor.applyActionToChell(_world, dto, player_id);
}

void Stage::step() {
    _world->step();
}

std::vector<std::shared_ptr<ProtocolDTO>> Stage::getUpdatedDTO() {
    vector<shared_ptr<ProtocolDTO>> output;
    _processor.createDTOs<Collidable*>(_world->getObjectsToUpdate(), output);
    return move(output);
}

std::vector<std::shared_ptr<ProtocolDTO>> Stage::getDeletedDTO() {
    vector<shared_ptr<ProtocolDTO>> output;
    for (auto &obj_delete : _world->getObjectsToDelete())
        output.push_back(_processor.createDTO(obj_delete.first, obj_delete.second));
    return std::move(output);
}
