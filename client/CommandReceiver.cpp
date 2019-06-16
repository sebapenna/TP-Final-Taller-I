//
// Created by jonathanmedina on 15/06/19.
//

#include <iostream>
#include "CommandReceiver.h"

CommandReceiver::CommandReceiver(Protocol &protocol, bool &done, bool& user_quit) :
                protocol(protocol), done(done), user_quit(user_quit) {
}

void CommandReceiver::run() {
    while (!done && !user_quit) {
        std::string msg;
        protocol >> msg;
        uint8_t server_command = -1;
        protocol >> server_command;
        if (server_command == 0)
            done = true;
        std::cout << msg;
    }
}
