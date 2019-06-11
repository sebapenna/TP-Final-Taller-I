#include <Common/exceptions.h>
#include "ReceiverThread.h"
#include <memory>

using std::shared_ptr;
using std::ref;

void ReceiverThread::run(Player &player, SafeQueue<shared_ptr<Event>> &events_queue) {
    try {
        std::cout << std::endl << "ReceiverThread: Comienza ejecucion receive thread..." <<
        std::endl;
        shared_ptr<ProtocolDTO> dto_ptr;
        while (true) {  // Loop finalizara cuando se corte conexion
            std::cout << "ReceiverThread: Esperando DTO..." << std::endl;

            player.receiveDTO(dto_ptr); // Receive bloqueante

            std::cout << std::endl<<"ReceiverThread: DTO Recibido" << std::endl;

            shared_ptr<Event> p = std::make_shared<Event>(player.id(), dto_ptr);
            events_queue.push(std::move(p));    // Encolo evento y id de player
            std::cout << std::endl<<"ReceiverThread: DTO Encolado" << std::endl;
        }
    } catch (FailedRecvException& e) {
        // Catch de exception ya que se puede terminar conexion voluntariamente
        // en medio de recepcion de datos
        _dead = true;
    } catch (const exception& e) {
        _dead = true;
        throw;
    }

}

ReceiverThread::ReceiverThread(Player &player, SafeQueue<shared_ptr<Event>> &events_queue) :
_player(ref(player)), _thread(&ReceiverThread::run, this, ref(player), ref(events_queue))
{ }

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
