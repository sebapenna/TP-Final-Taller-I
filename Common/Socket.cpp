#include "Socket.h"
#include "exceptions.h"
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <string>

Socket::Socket(int descriptor) : descriptor(descriptor) { }

Socket::Socket(const std::string &host, const std::string &port) {
    struct addrinfo hints;
    struct addrinfo *ai_results, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo)); // 0 en cada atributo de hints
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = 0;
    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &ai_results) != 0)
        throw CantConnectException();
    bool connected = false;
    for (ptr = ai_results; (ptr) && (! connected); ptr = ptr->ai_next) {
        descriptor = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (descriptor == -1)
            break;
        connected = ::connect(descriptor, ptr->ai_addr, ptr->ai_addrlen) == 0;
    }
    freeaddrinfo(ai_results);
    if (! connected)
        throw CantConnectException();
}

Socket::Socket(Socket &&other) : descriptor(other.descriptor) {
    other.descriptor = -1;
}

Socket &Socket::operator=(Socket &&other) {
    this->descriptor = std::move(other.descriptor);
    other.descriptor = -1;
    return  *this;
}

Socket::~Socket() {
    if (descriptor != -1) {
        ::shutdown(descriptor, SHUT_RDWR);
        ::close(descriptor);
    }
}

void Socket::shutdown() {
    if (descriptor != -1) {
        ::shutdown(descriptor, SHUT_RDWR);
        ::close(descriptor);
        descriptor = -1;
    }
}

void Socket::send(const void *src, int src_size) {
    int bytes_tot = 0;
    char *aux = (char *) src;
    while (bytes_tot < src_size) {
        int bytes_act = ::send(descriptor, &aux[bytes_tot], src_size, MSG_NOSIGNAL);
        (bytes_act > 0) ? bytes_tot += bytes_act : throw FailedSendException();
    }
}

void Socket::recv(void *dest, int recv_bytes) {
    int bytes_recvd = 0;
    while (bytes_recvd < recv_bytes) {
        bytes_recvd = ::recv(descriptor, dest, recv_bytes, MSG_NOSIGNAL);
        if (bytes_recvd <= 0)
            throw FailedRecvException();
    }
}

