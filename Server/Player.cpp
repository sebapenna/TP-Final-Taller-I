#include "Player.h"

using std::move;

// todo: porque doble movimiento
Player::Player(Socket &&socket/*lobby*/) : _connection(move(socket)) {
// todo: receiver tread lo creo aca, atributo suyo
//loby.creategame
//loby.addgame
}

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
