#ifndef PORTAL_EVENT_H
#define PORTAL_EVENT_H

#include <cstdio>
#include <memory>
#include <Common/ProtocolTranslator/ProtocolDTO.h>

// Elemento a agregar a la cola de eventos
class Event {
private:
    const size_t _id;
    std::shared_ptr<ProtocolDTO> _ptr;

public:
    Event(const size_t& id, std::shared_ptr<ProtocolDTO> ptr);

    const size_t getPlayerId() const;

    const std::shared_ptr<ProtocolDTO> &getPtr() const;

    // Retorna el id del protocolo del evento
    const int16_t getProtocolId() const;
};


#endif //PORTAL_EVENT_H
