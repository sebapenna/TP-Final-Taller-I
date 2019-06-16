#ifndef PORTAL_STAGE_H
#define PORTAL_STAGE_H

#include <string>
#include <vector>
#include <memory>
#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include "Server/Model/World.h"
#include "Event.h"
#include "DTOProcessor.h"
#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include <Server/YamlData/YamlParser.h>

class Stage {
private:
    World *_world;
    DTOProcessor _processor;
    std::vector<ChellData> _available_chells;

public:
    explicit Stage(std::string &config_file);

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

    void step();
};


#endif //PORTAL_STAGE_H
