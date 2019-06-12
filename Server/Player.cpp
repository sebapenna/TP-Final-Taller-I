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
        // while events_que != nullptr
        std::cout << "Sin falla"<<std::endl;

        auto events_queue = ref(lobby.createGame(/*getSharedPtr()*/this, 1, move("filea.yaml")));
        // todo: HARCODEADO - SACAR
        while (_connected) {  // Loop finalizara cuando se corte conexion
            receiveDTO(dto_ptr); // Receive bloqueante
            shared_ptr<Event> p = std::make_shared<Event>(_id, dto_ptr);
            events_queue.get().push(std::move(p));    // Encolo evento y id de player
        }
    } catch (FailedRecvException& e) {
        // Catch de exception ya que se puede terminar conexion voluntariamente
        // en medio de recepcion de datos
        _connected = false;
    } catch (const exception& e) {
        _connected = false;
        std::cout << e.what();
    }
}

// todo: porque doble movimiento
Player::Player(Socket &&socket, Lobby &lobby) : _connected(true), _connection(move(socket)),
_receiver_thread(&Player::run, this, std::ref(lobby)) { }

void Player::setId(size_t id) {
    _id = id;
}

size_t Player::id() const {
    return _id;
}

void Player::receiveDTO(std::shared_ptr<ProtocolDTO> &dto) {
    _connection >> dto;
}

void Player::send(ProtocolDTO &dto) {
    _connection << dto;
}

void Player::send(std::shared_ptr<ProtocolDTO> &dto) {
    _connection << *dto.get();
}

void Player::join() {
    _receiver_thread.join();
}

void Player::disconnect() {
    this->~Player(); // Cierro player
}

Player::~Player() {
    _connected = false;
    _connection.disconnect();
    _receiver_thread.join();
}
