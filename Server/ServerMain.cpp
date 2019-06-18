#include <iostream>
#include <Common/exceptions.h>
#include <thread>
#include "Lobby.h"

#define PORT_POS    1
#define N_ARGS  2
#define SUCCESS 0
#define ERROR   1
#define QUIT    'q'

using std::cout;
using std::endl;
using std::cerr;

int main(int argc, char const *argv[]) {
    if (argc != N_ARGS) {
        cerr << WrongArgumentException().what();
        return ERROR;
    }
    try {
        Lobby lobby(argv[PORT_POS]);

        cout << "Lobby creado, disponible a conexiones..."<<endl;

        std::thread exit([&]() {    // Thread para cerrar servidor
            char c;
            do {
                std::cin.get(c);
            } while (c != QUIT);
            lobby.shutdown();
        });

        lobby.run();

        exit.join();
    } catch(const exception& e) {
        cerr << "Server Main: " << e.what();
        return ERROR;
    } catch(...) {
        cerr << "Server Main: "  << UnknownException().what();
        return ERROR;
    }
    return SUCCESS;
}