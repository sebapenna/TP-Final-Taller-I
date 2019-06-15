//
// Created by jonathanmedina on 15/06/19.
//

#include <iostream>
#include <Common/ProtocolTranslator/ConnectionDTO/QuitDTO.h>
#include "CommandSender.h"
#define START_GAME 0
#define QUIT_GAME 1
CommandSender::CommandSender(Protocol &protocol, bool &done, bool& user_quit) :
                protocol(protocol), done(done), user_quit(user_quit) {
}

void CommandSender::run() {
    char c;
    do {
        std::cin.get(c);
        if (c == START_GAME) {
            uint8_t code = 0;
            protocol << code;
        } else if (c == QUIT_GAME) {
            std::shared_ptr<ProtocolDTO> dto(new QuitDTO()); // Asi no hago el free
            protocol << *dto.get();
            user_quit = true;
        }
    } while (!done | !user_quit);

}
