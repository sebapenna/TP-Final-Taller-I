#ifndef PORTAL_HANDSHAKEHANDLER_H
#define PORTAL_HANDSHAKEHANDLER_H

#include <string>
#include <Common/Protocol.h>

// Handler para la conversacion entre servidor y cliente donde se define la eleccion del jugador
// a la hora de crear o unirse a una partida, asi como la configuracion en el caso de decidir
// iniciar un nuevo juego.
struct HandshakeHandler {
    // Retorna seleccion del jugador entre unirse a partida o crear una nueva
    static uint8_t getPlayerChoice(Protocol &connection);

    // Retorna par con cantidad maxima de jugadores y nombre del mapa
    static std::pair<size_t, std::string> createGame(Protocol &connection);

    static size_t joinGame(Protocol &connection);

    static void getOptionsAndChoose(Protocol &connection);
};


#endif //PORTAL_HANDSHAKEHANDLER_H
