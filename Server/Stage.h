#ifndef PORTAL_STAGE_H
#define PORTAL_STAGE_H

#include <string>
#include "Server/Model/World.h"

class Stage {
private:
    World *_world;

public:
    explicit Stage(const std::string &config_file);

};


#endif //PORTAL_STAGE_H
