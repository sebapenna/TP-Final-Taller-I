#ifndef PORTAL_STAGE_H
#define PORTAL_STAGE_H

#include <string>
#include "World.h"

class Stage {
private:
    World *_world;

public:
    explicit Stage(const std::string &config_file);

    // run
    // addPlayer
    // deletePlayer
    // send/recv data
    // atributo: cola protocol
    // translateProtocol
    // => llamar metodo world
};


#endif //PORTAL_STAGE_H
