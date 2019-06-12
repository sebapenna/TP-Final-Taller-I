#include <Common/exceptions.h>
#include "ReceiverThread.h"
#include "Player.h"
#include "Lobby.h"
#include <memory>

using std::shared_ptr;
using std::ref;
//
//void ReceiverThread::run(Lobby &lobby/*shared_ptr<Player> player*/) {
//    try {
//        shared_ptr<ProtocolDTO> dto_ptr;
//        //events_queue = player.handshake()
//        // while events_que != nullptr
//        std::string fname("filea.yaml");
//        auto events_queue = lobby.createGame(_player, 1, move(fname));  // todo: HARCODEADO - SACAR !!!!!
//
//
//        while (!_dead) {  // Loop finalizara cuando se corte conexion
//            _player->receiveDTO(dto_ptr); // Receive bloqueante
//            shared_ptr<Event> p = std::make_shared<Event>(_player->id(), dto_ptr);
//            events_queue->push(std::move(p));    // Encolo evento y id de player
//        }
//    } catch (FailedRecvException& e) {
//        // Catch de exception ya que se puede terminar conexion voluntariamente
//        // en medio de recepcion de datos
//        _dead = true;
//    } catch (const exception& e) {
//        _dead = true;
//        std::cout << e.what();
//    }
//}
//
//ReceiverThread::ReceiverThread(std::shared_ptr<Player> player, Lobby &lobby) :
//_player(player), _thread(&ReceiverThread::run, this, ref(lobby)) { }
//
//void ReceiverThread::join() {
//    _dead = true;   // En primer lugar para finalizar llop receiver
//    _player->disconnect();
//    _thread.join();
//}
//
//size_t ReceiverThread::getPlayerId() {
//    return _player->id();
//}
//
//bool ReceiverThread::isDead() const {
//    return _dead;
//}
