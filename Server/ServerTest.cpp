#include <Common/Protocol.h>
#include "Common/exceptions.h"
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
        SafeQueue<std::shared_ptr<ProtocolDTO>> queue;

        cout << "Abriendo socket aceptador..."<<endl;
        AcceptSocket accept_sckt(argv[PORT_POS], MAX_WAITING_QUEUE_SIZE);
        cout << "Disponible a conexiones..."<<endl;
        Socket sckt = accept_sckt.acceptConnection();
        cout << "Conexion establecida"<<endl;
        Protocol prot(move(sckt));

        shared_ptr<ProtocolDTO> p;
        prot >> p;
        queue.push(p);
        cout << "DTO recibido y encolado"<<endl;

//        auto dto = (MoveRightDTO *) p.get();
//        cout << "Se recibio Protocolo de ID: " << dto->getClassId() << endl;

        cout << "Enviando ChellDTO..."<<endl;
        shared_ptr<ProtocolDTO> p2(new ChellDTO(4, -2, 0, 4, 5, EAST, NOT_TILTED, NOT_MOVING,
                NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
        prot << *p2.get();
        cout << "Enviado"<<endl;

        prot >> p;
        queue.push(p);

//        auto n_dto = (ShootPortalDTO*) p.get();
//        cout << "Se recibio Protocolo de ID: " << n_dto->getClassId() << endl;
//        cout << "COLOR: "<<n_dto->getColor()<<endl;
//        cout << "X: "<<n_dto->getX()<<endl;
//        cout << "Y: "<<n_dto->getY()<<endl;

        for (p = queue.getTopAndPop(); p; p = queue.getTopAndPop()) {
            switch (p->getClassId()){
                case PROTOCOL_MOVE_RIGHT: {
                    auto dto = (MoveRightDTO *) p.get();
                    cout << "Se recibio Protocolo de ID: " << dto->getClassId() << endl;
                    break;
                }
                case PROTOCOL_SHOOT_PORTAL: {
                    auto n_dto = (ShootPortalDTO *) p.get();
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
