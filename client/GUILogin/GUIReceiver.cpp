//
// Created by jonathanmedina on 24/06/19.
//

#include "GUIReceiver.h"
//#include <string>

GUIReceiver::GUIReceiver(QObject *parent) : QObject(parent) {}

GUIReceiver::~GUIReceiver() {}

void GUIReceiver::start(Protocol* protocol) {
    while (true) {
        std::string msg;
        *protocol >> msg;

        uint8_t server_command = -1;
        *protocol >> server_command;
        if (msg == std::string("Nuevo jugador agregado a la partida\n")) {
            emit messageToGUI(NEW_PLAYER_MESSAGE_ID);
        } else if (msg == std::string("Un jugador ha salido de la partida\n")) {
            emit messageToGUI(QUIT_PLAYER_MESSAGE_ID);
        } else if (msg == std::string("Ahora sos el owner de la partida, ingresa 's' para comenzar la partida\n")) {
            emit messageToGUI(NOW_YOU_ARE_THE_OWNER_MESSAGE_ID);
        }

        if (server_command == 0) {
            emit messageToGUI(START_THE_GAME_MESSAGE_ID);
            return;
        }

    }
}
void GUIReceiver::stop() {
    mSTop = true;
}

