#ifndef TP3_SOCKET_H
#define TP3_SOCKET_H

#include <string>

//  Logica de sockets
class Socket {
private:
    int descriptor;

public:
    // Constructor que genera conexion (pensado para el cliente)
    Socket(const std::string& host, const std::string& port);

    explicit Socket(int descriptor);

    // Constructor sin generar conexion (pensado para el servidor)
    Socket() : descriptor(0){}

    // Constructor por movimiento
    Socket(Socket &&other);

    // Asignacion por movimiento
    Socket& operator=(Socket&& other);

    Socket& operator=(Socket& other) = delete;

    ~Socket();

    // Envia size_in_bytes bytes.
    void send(const void* src, int src_size);

    // Recibe size_in_bytes bytes. No cambia endianess
    void recv(void *dest, int recv_bytes);

    void shutdown();
};

#endif //TP3_SOCKET_H
