#include <Common/Protocol.h>
#include "Common/exceptions.h"
#include "Event.h"
#include "Player.h"
#include <iostream>
#include <Common/AcceptSocket.h>
#include <Common/Socket.h>
#include <Common/ProtocolTranslator/ChellDTO.h>
#include <Common/ProtocolTranslator/MoveRightDTO.h>
#include <Common/ProtocolTranslator/protocol_macros.h>
#include <Common/ProtocolTranslator/ShootPortalDTO.h>
#include <Common/SafeQueue.h>

#define PORT_POS    1
#define N_ARGS  2
#define MAX_WAITING_QUEUE_SIZE  10
#define SUCCESS 0
#define ERROR   1

using std::cout;
using std::endl;
using std::move;
using std::shared_ptr;

int main(int argc, char const *argv[]) {
    if (argc != N_ARGS)
        cout << WrongArgumentException().what();
    try {
        SafeQueue<shared_ptr<Event>> queue;

        cout << "Abriendo socket aceptador..."<<endl;
        AcceptSocket accept_sckt(argv[PORT_POS], MAX_WAITING_QUEUE_SIZE);
        cout << "Disponible a conexiones..."<<endl;

        Player player(move(accept_sckt.acceptConnection()));
        player.setId(0);
        cout << "Conexion establecida"<<endl;


        shared_ptr<ProtocolDTO> dto_ptr;
        player.receiveDTO(dto_ptr);


        shared_ptr<Event> event = std::make_shared<Event>(player.id(), dto_ptr);
        queue.push(std::move(event));    // Encolo evento y id de player
        cout << "DTO recibido y encolado"<<endl;

        cout << "Enviando ChellDTO..."<<endl;
        shared_ptr<ProtocolDTO> send_dto(new ChellDTO(4, -2, 0, 4, 5, EAST, NOT_TILTED, NOT_MOVING,
                NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
        player.send(send_dto);
        cout << "Enviado"<<endl;

        player.receiveDTO(dto_ptr);
        event = std::make_shared<Event>(player.id(), dto_ptr);
        queue.push(std::move(event));    // Encolo evento y id de player

        for (auto e = queue.getTopAndPop(); e; e = queue.getTopAndPop()) {
            switch (e->getPtr()->getClassId()){
                case PROTOCOL_MOVE_RIGHT: {
                    auto dto = (MoveRightDTO *) e->getPtr().get();
                    cout << "Se recibio Protocolo de ID: " << dto->getClassId() << endl;
                    break;
                }
                case PROTOCOL_SHOOT_PORTAL: {
                    auto n_dto = (ShootPortalDTO *) e->getPtr().get();
                    cout << "Se recibio Protocolo de ID: " << n_dto->getClassId() << endl;
                    cout << "COLOR: " << n_dto->getColor() << endl;
                    cout << "X: " << n_dto->getX() << endl;
                    cout << "Y: " << n_dto->getY() << endl;
                    break;
                }
            }
        }
    } catch(const exception& e) {
        cout << e.what();
        return ERROR;
    } catch(...) {
        cout << UnknownException().what();
        return ERROR;
    }

}
