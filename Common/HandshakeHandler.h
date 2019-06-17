#ifndef PORTAL_HANDSHAKEHANDLER_H
#define PORTAL_HANDSHAKEHANDLER_H

#include <string>
#include <Common/Protocol.h>
#include <Server/Lobby.h>


// Handler para la conversacion entre servidor y cliente donde se define la eleccion del jugador
// a la hora de crear o unirse a una partida, asi como la configuracion en el caso de decidir
// iniciar un nuevo juego.
struct HandshakeHandler {
    // Retorna seleccion del jugador entre unirse a partida o crear una nueva
    static uint8_t getPlayerChoice(Protocol &connection);

    // Retorna par con cantidad maxima de jugadores y nombre del mapa
    static std::pair<size_t, std::string> createGame(Protocol &connection);

    // Brinda los datos para que jugador seleccione a que partida unirse y retorna el id de la
    // partida a la que el jugador desea unirse, La clase que utilize este metidi y intente
    // agregar el jugador mediante lobby debe notificar al cliente mediante un uint8_t si pudo o
    // no unirlo a la partida indicada (SUCCESS vs ERROR). En caso de no haber sido posible se
    // debe enviar tambien un string informando lo ocurrido, posterior al comando ERROR.
    static size_t joinGame(Protocol &connection, Lobby &lobby);

    // Metodo para el cliente (jugador). Se encarga de recibir y enviar todos los datos necesarios
    // para que un nuevo jugador cree o se una a una partida.
    // Retorna true si el jugador creo una partida y es el owner de la misma, false si se unio a
    // una partida existente y debe esperar al owner para comenzar.
    static bool getOptionsAndChoose(Protocol &connection);
};


#endif //PORTAL_HANDSHAKEHANDLER_H
