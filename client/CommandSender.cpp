//
// Created by jonathanmedina on 15/06/19.
//

#include <iostream>
#include <Common/ProtocolTranslator/GameStateDTO/QuitDTO.h>
#include <Common/ProtocolTranslator/GameStateDTO/BeginDTO.h>
#include "CommandSender.h"
#define START_GAME 's'
#define QUIT_GAME 'q'
CommandSender::CommandSender(Protocol &protocol, bool &done, bool& user_quit) :
                protocol(protocol), done(done), user_quit(user_quit) {
}

void CommandSender::run() {
    char c;
    do {
        std::cin.get(c);
        if (c == START_GAME) {
            std::shared_ptr<ProtocolDTO> dto(new BeginDTO()); // Asi no hago el free
            protocol << *dto.get();
            done = true;
        } else if (c == QUIT_GAME) {
            std::shared_ptr<ProtocolDTO> dto(new QuitDTO()); // Asi no hago el free
            protocol << *dto.get();
            user_quit = true;
        }
    } while (!done && !user_quit);

}
