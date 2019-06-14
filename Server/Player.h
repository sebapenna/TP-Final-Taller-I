#ifndef PORTAL_PLAYER_H
#define PORTAL_PLAYER_H

#include <Common/Protocol.h>
#include <memory>
#include "ReceiverThread.h"

class Lobby;

class Player {
private:
    Protocol _connection;
    size_t _id = 0; // 0 por default, pero es necesario utilizar el metodo setId para asignarlo
    std::thread _receiver_thread;
    bool _connected;


    void run(Lobby &lobby);

public:
    // Se brinda socket por movimiento ya que dentro de Player se hara un move de dicho socket,
    // por lo tanto de esta manera el usuario que utilize esta clase sabra que pierde ownership
    // del mismo
    explicit Player(Socket &&socket, Lobby &lobby, const size_t& id);

    void setId(size_t id);

    size_t id() const;

    void receiveDTO(std::shared_ptr<ProtocolDTO> &dto);

    void send(std::shared_ptr<ProtocolDTO> &dto);

    // Necesario utilizar este metodo para desconectar y cerrar el jugador correctamente previo a
    // eliminarlo por completo del juego
    // POST: el jugador ya no se encuentra conectado y su hilo receptor finalizo la ejecucion
    void disconnectAndJoin();
};


#endif //PORTAL_PLAYER_H