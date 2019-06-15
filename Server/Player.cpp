#include <Common/exceptions.h>
#include <string>
#include "Player.h"
#include "Lobby.h"
#include "Common/HandshakeHandler.h"

#define HOW_TO_BEGIN_MSG "Partida creada. Ingrese 0 cuando desee comenzar.\n"

#define HOW_TO_REFRESH_MSG "Ingrese l para actualizar listado de partidas abiertas.\n";

#define CREATE_GAME  (uint8_t) 0
#define JOIN_GAME    (uint8_t) 1

#define SUCCESS  (uint8_t) 1
#define ERROR   (uint8_t) 0

using std::move;
using std::shared_ptr;
using std::ref;

SafeQueue<shared_ptr<Event>>& Player::joinGame(Lobby &lobby) {
//    _connection << HOW_TO_REFRESH_MSG;
//    uint8_t refresh;
//    _connection >> refresh;
//    while (refresh != REFRESH)
//        errorLoop(refresh);


    // while events_que != nullptr
    // joinGameIfNotFull => catch FullGameException
}

SafeQueue<shared_ptr<Event>>& Player::createGame(Lobby &lobby) {
    auto pair = HandshakeHandler::createGame(ref(_connection));
    return ref(lobby.createGame(this, pair.first, std::move(pair.second)));
}

SafeQueue<shared_ptr<Event>>& Player::handshake(Lobby &lobby) {
    auto player_choice = HandshakeHandler::getPlayerChoice(ref(_connection));
    if (player_choice == CREATE_GAME) {
        auto queue = ref(createGame(ref(lobby)));
        _connection << HOW_TO_BEGIN_MSG;    // Envio mensaje con informacion para iniciar
        return ref(queue);
    } else {
        auto queue = ref(joinGame(ref(lobby)));
        _connection << HOW_TO_REFRESH_MSG;  // Envio mensaje con informacion para ver partidas
        return std::ref(joinGame(std::ref(lobby)));
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


