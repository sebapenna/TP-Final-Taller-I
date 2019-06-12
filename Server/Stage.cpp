#include<vector>
#include "Stage.h"
#include "WorldObjectDTOTranslator.h"
#include "DTOProcessor.h"

using std::vector;
using std::shared_ptr;
using std::move;


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
    vector<RockBlockData> rock_blocks_data_vector;
    try {
        rock_blocks_data_vector = config.loadRockBlocksData();
    } catch(...) { } // No hay bloques roca

    // Configuracion bloques metal
    vector<MetalBlockData> metal_blocks_data_vector;
    try {
        metal_blocks_data_vector = config.loadMetalBlocksData();
    } catch(...) { } // No hay bloques metal

    // Configuracion bloques metal diagonal
    vector<MetalDiagonalBlockData> metal_diagonal_blocks_data_vector;
    try {
        metal_diagonal_blocks_data_vector = config.loadMetalDiagonalBlockData();
    } catch(...) { } // No hay bloques metal diagonal

    // Configuracion rocas
    vector<RockData> rocks_vector;
    try {
        rocks_vector = config.loadRockData();
    } catch(...) { } // No hay rocas

    // Configuracion botones
    vector<ButtonData> buttons_vector;
    try {
        buttons_vector = config.loadButtonData();
    } catch(...) { } // No hay botones

    // Configuracion acido
    vector<AcidData> acid_vector;
    try {
        acid_vector = config.loadAcidData();
    } catch(...) {  } // No hay acido

    // Configuracion compuertas
    vector<GateData> gates_vector;
    try {
        gates_vector = config.loadGateData();
    } catch(...) { } // No hay compuertas

    // Configuracion transmisores energia
    vector<EnergyTransmitterData> e_transm_vector;
    try {
        e_transm_vector = config.loadEnergyTransmitterData();
    } catch(...) { } // No hay emisores energia

    // Configuracion receptores energia
    vector<EnergyReceiverData> e_receiver_vector;
    try {
        e_receiver_vector = config.loadEnergyReceiverData();
    } catch(...) { } // No hay receptores energia

    // Configuracion barreras energia
    vector<EnergyBarrierData> e_barrier_vector;
    try {
        e_barrier_vector = config.loadEnergyBarrierData();
    } catch(...) { } // No hay barreras eergia

    // Configuracion chells
    try {
        _available_chells = config.loadChellData();
    } catch(...) { } // No hay chells


    /******************** Inicializo World *********************/
    _world = new World(world_data.getWidth(), world_data.getHeight());


    //todo: PASAR TODO A FOR EACH
    for (auto &it : rock_blocks_data_vector)
        _world->createRockBlock(it.getWidth(), it.getHeight(), it.getX(),
                it.getY());

    for (auto &it : metal_blocks_data_vector)
        _world->createMetalBlock(it.getWidth(), it.getHeight(), it.getX(),
                it.getY());

    for (auto &it : metal_diagonal_blocks_data_vector)
        _world->createMetalDiagonalBlock(it.getWidth(), it.getHeight(),
                it.getX(), it.getY(), it.getOrientation());

    for (auto &it : rocks_vector)
        _world->createRock(it.getX(), it.getY());

    for (auto &it : acid_vector)
        _world->createAcid(it.getX(), it.getY());

    for (auto &it : buttons_vector)
        _world->createButton(it.getX(), it.getY());


    for (auto &it : e_receiver_vector)
        _world->createEnergyReceiver(it.getX(), it.getY());

    // IMPORTANTE: gates creada luego de receivers y buttons porque necesita referencia a ellas
    for (auto &it : gates_vector) {
        _world->createGate(it.getX(), it.getY(),
                           it.getButtonsNeeded(), it.getEnergyReceiversNeeded());
    }

    for (auto &it : e_transm_vector)
        _world->createEnergyTransmitter(it.getX(), it.getY(),
                it.getDirection());

    for (auto &it : e_barrier_vector)
        _world->createEnergyBarrier(it.getX(), it.getY(), it.getOrientation());
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
