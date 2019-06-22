#include <Common/Protocol.h>
#include "Common/exceptions.h"
#include "Common/HandshakeHandler.h"
#include <iostream>
#include <Common/Socket.h>
#include <Common/ProtocolTranslator/DataDTO/ChellDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/MoveRightDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/ShootPortalDTO.h>
#include <Common/ProtocolTranslator/protocol_macros.h>
#include <thread>
#include <chrono>
#include <Common/ProtocolTranslator/GameStateDTO/BeginDTO.h>
#include <Common/ProtocolTranslator/DataDTO/RockDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/StopDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/MoveLeftDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/JumpDTO.h>
#include <Common/ProtocolTranslator/GameStateDTO/QuitDTO.h>


#define IP_POS  1
#define PORT_POS    2
#define N_ARGS  3
#define SUCCESS 0
#define ERROR   1

using std::cerr;
using std::cout;
using std::endl;
using std::make_shared;
using std::move;
using std::shared_ptr;


void receiveData(Protocol &prot, shared_ptr<ProtocolDTO> &dto_ptr) {
    while (dto_ptr->getClassId() != PROTOCOL_BEGIN) { // uso begin para cortar loop recepcioon
        cout << "Recibiendo DTO..."<<endl;
        prot >> dto_ptr;
        switch (dto_ptr->getClassId()) {
            case PROTOCOL_ROCK_DATA: {
                cout << "Rock"<<endl;
                auto o = (RockDTO*) dto_ptr.get();
                cout << "x: "<<o->getX()<<" y: "<<o->getY()<<endl;
                break;
            }
            case PROTOCOL_CHELL_DATA: {
                cout << "chell"<<endl;
                auto o = (ChellDTO*) dto_ptr.get();
                cout << "x: "<<o->getX()<<" y: "<<o->getY()<<endl;
                break;
            }
        }
    }
    cout << "Se recibieron todos los datos del step"<<endl;
}

int main(int argc, char const *argv[]) {
    if (argc != N_ARGS)
        cerr << WrongArgumentException().what();

    try {
        cout << endl<<"Estableciendo conexion..."<<endl;

        Protocol prot(argv[IP_POS], argv[PORT_POS]);
        cout << "Conexion establecida"<<endl;

        HandshakeHandler::getOptionsAndChoose(std::ref(prot));
        std::string msg;
        uint8_t command = 1;

        std::thread input([&]() {    // Thread para cerrar servidor
            char c;
            do {
                std::cin.get(c);
            } while (c != 's');
            cout << "Enviando BeginDTO..."<<endl;
            shared_ptr<ProtocolDTO> pdto(new BeginDTO());
            prot << *pdto.get();
            cout << "Enviado"<<endl;
        });

        while (command != 0) {
            prot >> msg;
            std::cout << msg;
            prot >> command;
        }



        try {


            shared_ptr<ProtocolDTO> dto_ptr;
            prot >> dto_ptr;

            cout << "Recibiendo configuracion incial..." << endl;
            while (dto_ptr->getClassId() != PROTOCOL_BEGIN) {
                switch (dto_ptr->getClassId()) {
                    case PROTOCOL_ROCK_BLOCK_DATA:
                        cout << "ROCK BLOCK" << endl;
                        break;
                    case PROTOCOL_METAL_BLOCK_DATA:
                        cout << "METAL BLOCK" << endl;
                        break;
                    case PROTOCOL_METAL_DIAGONAL_BLOCK_DATA:
                        cout << "METAL_DIAGONAL BLOCK" << endl;
                        break;
                    case PROTOCOL_ENERGY_TRANSMITTER_DATA:
                        cout << "ENERGY TRANSMITTER" << endl;
                        break;
                    case PROTOCOL_ENERGY_RECEIVER_DATA:
                        cout << "ENERGY RECEIVER" << endl;
                        break;
                    case PROTOCOL_ACID_DATA:
                        cout << "ACID" << endl;
                        break;
                    case PROTOCOL_BUTTON_DATA:
                        cout << "BUTTON" << endl;
                        break;
                    case PROTOCOL_GATE_DATA:
                        cout << "GATE" << endl;
                        break;
                    case PROTOCOL_ENERGY_BARRIER_DATA:
                        cout << "ENERGY_BARRIER" << endl;
                        break;
                    case PROTOCOL_CHELL_DATA:
                        cout << "CHELL" << endl;
                        break;
                    case PROTOCOL_ROCK_DATA:
                        cout << "ROCK" << endl;
                        break;
                    case PROTOCOL_PLAYER_CHELL_ID:
                        cout << "PLAYER CHELL ID" << endl;
                        break;
                }
                prot >> dto_ptr;
            }
            cout << "Comienza partida" << endl;


            shared_ptr<ProtocolDTO> pdto = std::make_shared<MoveRightDTO>();
            cout << "Enviando MoveRightDTO..." << endl;
            prot << *pdto.get();
            cout << "Enviado" << endl;
            receiveData(prot, pdto);

            pdto = std::make_shared<StopDTO>();
            cout << "Enviando StopDTO..." << endl;
            prot << *pdto.get();
            cout << "Enviado" << endl;
            receiveData(prot, pdto);

            pdto = std::make_shared<MoveLeftDTO>();
            cout << "Enviando MoveLeftDTO..." << endl;
            prot << *pdto.get();
            cout << "Enviado" << endl;
            receiveData(prot, pdto);

            pdto = std::make_shared<StopDTO>();
            cout << "Enviando StopDTO..." << endl;
            prot << *pdto.get();
            cout << "Enviado" << endl;
            receiveData(prot, pdto);


            pdto = std::make_shared<JumpDTO>();
            cout << "Enviando JumpDTO..." << endl;
            prot << *pdto.get();
            cout << "Enviado" << endl;
            receiveData(prot, pdto);


            pdto = std::make_shared<QuitDTO>();
            cout << "Enviando QuitDTO para terminar partida..." << endl;
            prot << *pdto.get();
            cout << "Enviado" << endl;
        } catch (...) {input.join();}

        input.join();
    } catch(const exception& e) {
        cerr << e.what();
        return ERROR;
    } catch(...) {
        cerr << UnknownException().what();
        return ERROR;
    }
    return SUCCESS;
}
