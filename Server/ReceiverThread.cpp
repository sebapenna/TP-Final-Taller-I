#include <Common/exceptions.h>
#include "ReceiverThread.h"
#include <memory>

using std::shared_ptr;
using std::ref;
using std::pair;

void ReceiverThread::run(Player &player, SafeQueue<pair<size_t, shared_ptr<ProtocolDTO>>>
        &events_queue) {
    try {
        shared_ptr<ProtocolDTO> dto_ptr;
        player.receiveDTO(dto_ptr); // Receive bloqueante
        events_queue.push(std::make_pair(player.id(), dto_ptr));    // Encolo evento y id de player
    } catch (FailedRecvException& e) {
        // Catch de exception ya que se puede terminar conexion voluntariamente
        // en medio de recepcion de datos
        _dead = true;
    } catch (const exception& e) {
        _dead = true;
        throw;
    }

}

ReceiverThread::ReceiverThread(Player &player,
        SafeQueue<pair<size_t, shared_ptr<ProtocolDTO>>> &events_queue) : _player(player),
_thread(&ReceiverThread::run, this, ref(player), ref(events_queue)) {
}

void ReceiverThread::join() {
    _thread.join();
    _dead = true;
}

size_t ReceiverThread::getPlayerId() {
    return _player.id();
}

bool ReceiverThread::isDead() const {
    return _dead;
}
