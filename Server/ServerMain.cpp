#include <iostream>
#include <Common/exceptions.h>
#include <thread>
#include "Lobby.h"

#define PORT_POS    1
#define N_ARGS  2
#define MAX_WAITING_QUEUE_SIZE  10
#define SUCCESS 0
#define ERROR   1
#define QUIT    'q'

using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {
    if (argc != N_ARGS)
        throw WrongArgumentException();
    try {
        Lobby lobby(argv[PORT_POS]);

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
        cout << e.what();
        return ERROR;
    } catch(...) {
        cout << UnknownException().what();
        return ERROR;
    }
    return SUCCESS;
}