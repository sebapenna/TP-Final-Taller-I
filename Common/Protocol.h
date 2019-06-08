#ifndef PORTAL_PROTOCOL_H
#define PORTAL_PROTOCOL_H

#include "Socket.h"
#include <string>
#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include <memory>

// El protocolo se encarga de enviar/recibir los distintos DTO o los vectores con los
// datos ordenados por el protocolo definido. Internamente realiza las traducciones
// necesarias.
class Protocol {
private:
    Socket _socket;

public:
    Protocol(const std::string& ip, const std::string& port);

    explicit Protocol(Socket &&other);

    // Envia un DTO
    void operator<<(const ProtocolDTO &dto);

    // Recibe DTO
    void operator>>(std::shared_ptr<ProtocolDTO>& dto);

    // Envia int16_t. Se encarga de cambiar el endianess antes de enviar
    void operator<<(const int16_t & data);

    // Recibe int16_t. Se encarga de cambiar el endianess despues de recibir
    void operator>>(int16_t &dest);
};


#endif //PORTAL_PROTOCOL_H
