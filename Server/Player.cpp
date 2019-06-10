#include "Player.h"

using std::move;

Player::Player(Socket &&socket) : _connection(move(socket)) { }

void Player::setId(size_t id) {
    _id = id;
}

size_t Player::id() const {
    return _id;
}

void Player::receiveDTO(std::shared_ptr<ProtocolDTO> &dto) {
    _connection >> dto;
}
