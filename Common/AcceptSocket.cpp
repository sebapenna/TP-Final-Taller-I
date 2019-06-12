#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <string>
#include "AcceptSocket.h"
#include "exceptions.h"

AcceptSocket::AcceptSocket(const string& port, int max_size_waiting_queue) {
    struct addrinfo hints;
    struct addrinfo *ai_results, *ptr;
    /* 0 en cada atributo de hints */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;  // IPv4
    hints.ai_socktype = SOCK_STREAM;    // TCP
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(nullptr, port.c_str(), &hints, &ai_results) != 0)
        throw CantConnectException();
    bool connected = false;
    for (ptr = ai_results; (ptr) && (! connected); ptr = ptr->ai_next) {
        descriptor = socket(ptr->ai_family,
                                  ptr->ai_socktype, ptr->ai_protocol);
        if (descriptor == -1)
            break;
        // todo: ADDRESS ALREADY IN USE => FUNCION SETSOCKOPT
        connected = bind(descriptor, ptr->ai_addr, ptr->ai_addrlen) == 0;
        if (connected)
            connected = listen(descriptor, max_size_waiting_queue) == 0;
    }
    freeaddrinfo(ai_results);
    if (! connected)
        throw CantConnectException();
}

AcceptSocket::~AcceptSocket() {
    ::shutdown(descriptor, SHUT_RDWR);
    close(descriptor);
}

Socket AcceptSocket::acceptConnection() {
    int peer_descriptor = accept(descriptor, nullptr, nullptr);
    if (peer_descriptor == -1)
        throw CantConnectException();
    return std::move(Socket(peer_descriptor));
}

void AcceptSocket::shutdown() {
    ::shutdown(descriptor, SHUT_RDWR);
    close(descriptor);
}
