#ifndef PORTAL_PLAYER_H
#define PORTAL_PLAYER_H

#include <Common/Protocol.h>

class Player {
private:
    Protocol _connection;
    size_t _id = 0; // 0 por default, pero es necesario utilizar el metodo setId para asignarlo

public:
    explicit Player(Socket &&socket);

    void setId(size_t id);

    size_t id() const;

    void receiveDTO(std::shared_ptr<ProtocolDTO> &dto);
};


#endif //PORTAL_PLAYER_H
