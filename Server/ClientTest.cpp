#include <Common/Protocol.h>
#include "Common/exceptions.h"
#include <iostream>
#include <Common/Socket.h>
#include <Common/ProtocolTranslator/ChellDTO.h>
#include <Common/ProtocolTranslator/MoveRightDTO.h>
#include <Common/ProtocolTranslator/ShootPortalDTO.h>
#include <Common/ProtocolTranslator/protocol_macros.h>


#define IP_POS  1
#define PORT_POS    2
#define N_ARGS  3
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
        cout << endl<<"Estableciendo conexion..."<<endl;

        Protocol prot(argv[IP_POS], argv[PORT_POS]);
        cout << "Conexion establecida"<<endl;

        cout << "Enviando MoveRightDTO..."<<endl;
        shared_ptr<ProtocolDTO> pdto(new MoveRightDTO());
        prot << *pdto.get();
        cout << "Enviado"<<endl;

        shared_ptr<ProtocolDTO> p;
        prot >> p;
        auto dto = (ChellDTO*) p.get();
        cout << endl<<"Se recibio Protocolo de ID: " << dto->getClassId();
        cout << endl<<"ID: "<<dto->getId();
        cout << endl<<"X: "<<dto->getX();
        cout << endl<<"Y: "<<dto->getY();
        cout << endl<<"WIDTH: "<<dto->getWidth();
        cout << endl<<"HEIGHT: "<<dto->getHeight();
        cout << endl<<"DIRECTION: "<<dto->getDirection();
        cout << endl<<"TILTED: "<<dto->getTilted();
        cout << endl<<"MOVING: "<<dto->getMoving();
        cout << endl<<"JUMPING: "<<dto->getJumping();
        cout << endl<<"SHOOTING: "<<dto->getShooting();
        cout << endl<<"CARRYING: "<<dto->getCarryingRock();
        cout << endl<<"DELETE: "<<dto->getDeleteState()<<endl;

//        pdto.reset();   // Limpio shared_ptr
        pdto = std::make_shared<ShootPortalDTO>(BLUE_PORTAL, 5, 15);
        cout << "Enviando ShootPortalDTO..."<<endl;
        prot << *pdto.get();
        cout << "Enviado"<<endl;
    } catch(const exception& e) {
        cout << e.what();
        return ERROR;
    } catch(...) {
        cout << UnknownException().what();
        return ERROR;
    }
    return SUCCESS;
}
