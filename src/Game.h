#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H

#include <string>
#include "Stage.h"

class Game {
private:
    Stage *_stage;

public:
    explicit Game(const std::string &config_file);
};


#endif //PORTAL_GAME_H
