#include <Common/exceptions.h>
#include <string>
#include "Player.h"
#include "Lobby.h"
#include "Common/HandshakeHandler.h"

#define CREATE_GAME  (uint8_t) 0
#define JOIN_GAME    (uint8_t) 1

#define SUCCESS  (uint8_t) 1
#define ERROR   (uint8_t) 0

#define COULDNT_JOIN_MSG   "No puso ser agregado a la partida indicada, intentelo de nuevo\n"

using std::move;
using std::shared_ptr;
using std::ref;

SafeQueue<shared_ptr<Event>>& Player::handshake(Lobby &lobby) {
    auto player_choice = HandshakeHandler::getPlayerChoice(ref(_connection));
    if (player_choice == CREATE_GAME) {
        auto choices = HandshakeHandler::createGame(ref(_connection));
        auto queue = ref(lobby.createGame(this, choices.first, std::move(choices.second)));
        return ref(queue);
    } else {
        while (true) { // Loop finaliza cuando se pudo unir jugador a una partida
            try {
                auto game_to_join_id = HandshakeHandler::joinGame(ref(_connection), ref(lobby));
                auto queue = ref(lobby.joinGameIfOpenAndNotFull(this, game_to_join_id));
                _connection << SUCCESS; // Notifico al jugador que se lo unio
                return ref(queue);
            } catch (CantJoinGameException &e) {
                _connection << ERROR; // Notifico al jugador que no se lo unio
                _connection << COULDNT_JOIN_MSG;
            }
        }
    }
}

void Player::run(Lobby &lobby) {
    try {
        shared_ptr<ProtocolDTO> dto_ptr;

        auto events_queue = ref(handshake(ref(lobby)));

        while (_connected) {  // Loop finalizara cuando se corte conexion
            recv(dto_ptr); // Receive bloqueante
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

void Player::recv(std::shared_ptr<ProtocolDTO> &dto) {
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

void Player::notify(const uint8_t &command, const std::string &msg) {
    _connection << msg;
    _connection << command;
}


