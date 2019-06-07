#ifndef PORTAL_PROTOCOL_H
#define PORTAL_PROTOCOL_H

#include "Socket.h"
#include <string>
#include <Common/ProtocolTranslator/ProtocolDTO.h>

// El protocolo se encarga de enviar/recibir los distintos DTO o los vectores con los
// datos ordenados por el protocolo definido. Internamente realiza las traducciones
// necesarias.
class Protocol {
private:
    Socket socket;

public:
    Protocol(const std::string& host, const std::string& port);

    explicit Protocol(Socket &&other);

    // Envia un DTO, internamente se encarga de
    void operator<<(ProtocolDTO *dto);
};


#endif //PORTAL_PROTOCOL_H
