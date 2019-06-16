#ifndef PORTAL_PLAYER_H
#define PORTAL_PLAYER_H

#include <Common/Protocol.h>
#include <thread>
#include <memory>
#include <Common/SafeQueue.h>
#include "Event.h"

class Lobby;

class Player {
private:
    Protocol _connection;
    size_t _id; // 0 por default, pero es necesario utilizar el metodo setId para asignarlo
    std::thread _receiver_thread;
    bool _connected;

    void run(Lobby &lobby);

    SafeQueue<std::shared_ptr<Event>>& handshake(Lobby &lobby);

public:
    // Se brinda socket por movimiento ya que dentro de Player se hara un move de dicho socket,
    // por lo tanto de esta manera el usuario que utilize esta clase sabra que pierde ownership
    // del mismo
    explicit Player(Socket &&socket, Lobby &lobby, const size_t& id);

    void setId(size_t id);

    size_t id() const;

    void recv(std::shared_ptr<ProtocolDTO> &dto);

    void send(std::shared_ptr<ProtocolDTO> &dto);

    // Notifica al cliente con el mensaje indicado. Dentro se encarga de enviar el comando
    // adecuado para que el cliente sepa que debe recibir un string
    void notify(const uint8_t &command, const std::string &msg);

    // Necesario utilizar este metodo para desconectar y cerrar el jugador correctamente previo a
    // eliminarlo por completo del juego (borrarlo de memoria)
    // POST: el jugador ya no se encuentra conectado y su hilo receptor finalizo la ejecucion
    void disconnectAndJoin();
};


#endif //PORTAL_PLAYER_H