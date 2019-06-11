#ifndef PORTAL_STAGE_H
#define PORTAL_STAGE_H

#include <string>
#include <vector>
#include <memory>
#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include "Server/Model/World.h"
#include "Event.h"
#include <Common/ProtocolTranslator/ProtocolDTO.h>

class Stage {
private:
    World _world;

public:
    explicit Stage(std::string &&config_file);

    std::vector<std::shared_ptr<ProtocolDTO>> getInitialConfiguration();


    std::vector<std::shared_ptr<ProtocolDTO>> getUpdatedDTO();

    std::vector<std::shared_ptr<ProtocolDTO>> getDeletedDTO();

    void apply(ProtocolDTO *dto, const size_t& player_id);

    void step();
};


#endif //PORTAL_STAGE_H
