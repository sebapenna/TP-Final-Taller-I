#include<vector>
#include "Stage.h"
#include "DTOProcessor.h"

using std::vector;
using std::shared_ptr;
using std::move;
using std::for_each;


Stage::~Stage() {
    delete _world;
}

Stage::Stage(std::string &map_file, shared_ptr<Configuration> configuration) {
    YamlParser config(map_file);
    // Configuracion world
    WorldData world_data = config.loadWorldData();

    auto data_vector = config.parse();

    // Configuracion chells
    try {
        _available_chells = config.loadChellData();
    } catch(...) { } // No hay chells

    /******************** Inicializo World *********************/
    _world = new World(world_data.getWidth(), world_data.getHeight(), configuration);

    for (auto &data : data_vector)
        _world->createCollidable(data);

}

void Stage::createChells(const size_t &n_players) {
    for (size_t i = 0; i < n_players; ++i)
        _world->createCollidable(_available_chells[i]);
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
    _processor.createDTO(_world->getCake(), output, true);
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
        output.push_back(_processor.createDeletedDTO(obj_delete.first, obj_delete.second));
    return std::move(output);
}

bool Stage::someoneWon() {
    return _world->allChellsInCake();
}

void Stage::deletePlayer(const size_t &player_id) {
    auto chell = _world->getChell(player_id);
    chell->kill();  // Mato chell de jugador que abandono partida
}
