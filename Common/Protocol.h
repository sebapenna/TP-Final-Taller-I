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

    ~Protocol();

    void disconnect();

    // Send para string. Primero se envian el largo del mismo. No se envia '\0'
    void operator<<(const std::string& data);

    // Recv para string. Primero se recibe el largo del mismo.
    void operator>>(std::string &data);

    // Send para uint32_t. Se encarga de cambiar el endianess antes de enviar
    void operator<<(const uint32_t & data);

    // Recv para uint32_t. Se encarga de cambiar el endianess despues de recibir
    void operator>>(uint32_t & data);

    // Send para int16_t. Se encarga de cambiar el endianess antes de enviar
    void operator<<(const int16_t & data);

    // Recv para int16_t. Se encarga de cambiar el endianess despues de recibir
    void operator>>(int16_t &dest);

    // Send para DTO
    void operator<<(const ProtocolDTO &dto);

    // Recv para DTO
    void operator>>(std::shared_ptr<ProtocolDTO>& dto);

    // Send para uint8_t
    void operator<<(const uint8_t & data);
    // Recv para uint8_t
    void operator>>(uint8_t & data);
};


#endif //PORTAL_PROTOCOL_H
