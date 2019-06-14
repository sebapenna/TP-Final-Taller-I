#include <Common/exceptions.h>
#include "Player.h"
#include "ReceiverThread.h"
#include "Lobby.h"

using std::move;
using std::shared_ptr;

void Player::run(Lobby &lobby) {
    try {
        shared_ptr<ProtocolDTO> dto_ptr;
        //events_queue = player.handshake()
        // if (x) joinGame/createGame
        // while events_que != nullptr
        // joinGame => catch FullGameException
// todo: file sale de player handshake, al igual que numero de players
        auto events_queue = ref(lobby.createGame(this, 1, move("filea.yaml")));
        while (_connected) {  // Loop finalizara cuando se corte conexion
            receiveDTO(dto_ptr); // Receive bloqueante
            shared_ptr<Event> p = std::make_shared<Event>(_id, dto_ptr);
            events_queue.get().push(std::move(p));    // Encolo evento y id de player
        }
    } catch (FailedRecvException& e) {         // Se podria cerrar la conexion voluntariamente
        _connected = false;
    } catch (const exception& e) {
        _connected = false;
        std::cout << e.what();
    }
}

Player::Player(Socket &&socket, Lobby &lobby, const size_t& id) : _id(id),_connected(true),
        _connection(move(socket)), _receiver_thread(&Player::run, this, std::ref(lobby)) { }

void Player::setId(size_t id) {
    _id = id;
}

size_t Player::id() const {
    return _id;
}

void Player::receiveDTO(std::shared_ptr<ProtocolDTO> &dto) {
    _connection >> dto;
}

void Player::send(std::shared_ptr<ProtocolDTO> &dto) {
    _connection << *dto.get();
}

void Player::disconnectAndJoin() {
        _connected = false;
    _connection.disconnect();
    _receiver_thread.join();
}
