#ifndef TP3_ACCEPT_SOCKET_H
#define TP3_ACCEPT_SOCKET_H

#include <string>
#include "Socket.h"

using std::string;

// Clase realcionada al socket aceptador a utilizar por el servidor
class AcceptSocket {
private:
    int descriptor;

public:
    // Crea un socket asociado al port indicado con una cola de espera de
    // tamaño maximo max_size_waiting_queue
    AcceptSocket(const string& port, int max_size_waiting_queue);

    ~AcceptSocket();

    // Acepta una conexion y retorna el socket
    Socket acceptConnection();

    // Ciera el socket
    void shutdown();
};


#endif //TP3_ACCEPT_SOCKET_H
