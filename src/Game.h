#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H

#include <string>
#include "Stage.h"

class Game {
private:
    Stage *_stage;

public:
    explicit Game(const std::string &config_file);

    // run
    // addPlayer
    // deletePlayer
    // send/recv data
    // atributo: cola protocol
    // translateProtocol
    // => llamar metodo stage
};


#endif //PORTAL_GAME_H
