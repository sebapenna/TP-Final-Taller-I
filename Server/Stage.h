#ifndef PORTAL_STAGE_H
#define PORTAL_STAGE_H

#include <string>
#include <vector>
#include <memory>
#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include "Server/Model/World.h"
#include "Event.h"
#include "DTOProcessor.h"
#include "Configuration.h"
#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include <Server/Model/CollidableData/YamlParser.h>

class Stage {
private:
    World *_world;
    DTOProcessor _processor;
    std::vector<std::shared_ptr<CollidableData>> _available_chells;

public:
    explicit Stage(std::string &map_file, std::shared_ptr<Configuration> configuration);

    ~Stage();

    // Agrego al mapa la cantidad indicada de chells, determinada por la cantidad de jugadores
    // que tiene la partida.
    // PRE: se debe haber establecido la cantidad de jugadores, ya que los chells creados
    // formaran parte del juego
    void createChells(const size_t& n_players);

    // Retorna vector con todos los DTOs respectivos a los objetos del mapa creados mediante el
    // archivo de configuracion
    // PRE: haber utilizado metodo createChells para agregarlas al juego, de lo contrario no se
    // enviaran sus datos
    std::vector<std::shared_ptr<ProtocolDTO>> getInitialConfiguration();

    // Retorna vector con los DTO de aquellos objetos que tuvieron alguna actualizacion en su
    // estado durante step
    // PRE: haber utilizado el metodo step() para actualizar el vector
    std::vector<std::shared_ptr<ProtocolDTO>> getUpdatedDTO();

    // Retorna vector con los DTO de aquellos objetos que fueron eliminados del mapa durante step
    // PRE: haber utilizado el metodo step() para actualizar el vector
    std::vector<std::shared_ptr<ProtocolDTO>> getDeletedDTO();

    // Aplica los distintos DTOs que llegan al servidor sobre el chel de id player_id
    void apply(ProtocolDTO *dto, const size_t& player_id);

    void deletePlayer(const size_t& player_id);

    void step();

    // Retorna true en caso de que todas las chells (podria ser solo una) hayan llegado a la cake
    bool someoneWon();
};


#endif //PORTAL_STAGE_H
