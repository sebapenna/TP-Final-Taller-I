#include <string>
#include "socket.h"
#include "errorcreate.h"
#include "errorbind.h"
#include "errorlisten.h"

Socket::Socket() {
    int family_skt = AF_INET;
    int type_skt = SOCK_STREAM;
    int protocol_skt = 0;
    int s = ::socket(family_skt, type_skt, protocol_skt);

    if (s == -1)
        throw ErrorCreate();

    this->socket = s;
}

Socket::Socket(int skt): socket(skt) {}

Socket::~Socket() {
	if (this->socket!=-1) {
		shutdown(this->socket, SHUT_RDWR);
		close(this->socket);
	}
}

Socket& Socket::operator=(Socket&& origin) {
    this->socket = origin.socket;
    origin.socket = -1;
    return *this;
}

Socket::Socket(Socket&& origin): socket(origin.socket) {
    origin.socket = -1;
}


bool Socket::bindAndListen(const std::string& port, int amount) {
	struct addrinfo hints;
   	struct addrinfo *ptr;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, port.c_str(), &hints, &ptr) != 0) { 
		throw new ErrorBind();
	}

	int val = 1;
	if (setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR, &val,
	        sizeof(val)) == -1) {
		close(this->socket);
		freeaddrinfo(ptr);
        throw new ErrorBind();
	}

	if (bind(this->socket, ptr->ai_addr, ptr->ai_addrlen) == -1) {
		close(this->socket);
		freeaddrinfo(ptr);
        throw new ErrorBind();
	}

	freeaddrinfo(ptr);

	if (listen(this->socket, amount) == -1) {
		close(this->socket);
        throw new ErrorListen();
	}
	return true;
}

bool Socket::connect(const std::string& IP, const std::string& port) {
	struct addrinfo hints;
	struct addrinfo *result, *ptr;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0; 

	if (getaddrinfo(IP.c_str(), port.c_str(), &hints, &result) != 0) {
		return false;
	}

	bool are_we_connected = false;
	for (ptr = result; ptr != NULL && are_we_connected == false; 
		ptr = ptr->ai_next) {
		if (::connect(this->socket, ptr->ai_addr, ptr->ai_addrlen)) {
			are_we_connected = true;
		}
	}

	freeaddrinfo(result);
	return are_we_connected;
}

Socket Socket::accept(){
    int skt_result = ::accept(this->socket, NULL, NULL);
    if (skt_result == -1)
        return std::move(Socket(-1));
    return std::move(Socket(skt_result));
}

bool Socket::invalid(){
	return this->socket == -1;
}

int Socket::recvMessage(char* buf, int size) {
	int received = 0;
	int s = 0;

	while (received < size) {
    	s = recv(this->socket, &buf[received], size-received, MSG_NOSIGNAL);
      
	    if (s == 0) {
			return received;
	    } else if (s < 0) {
	    	return -1;
	    } else {
	    	received += s;
	    }
	}
	return received;
}

bool Socket::sendMessage(char* request, int bytes_to_send) {
	int bytes_sent = 0;
	bool are_we_connected = true;
	int s;
	while (bytes_sent < bytes_to_send && are_we_connected) {
		s = send(this->socket, &request[bytes_sent], 
		bytes_to_send - bytes_sent, MSG_NOSIGNAL);

		if (s < 0) {
			return false;
		} else if (s== 0) {
			are_we_connected = false;
		} else {
			bytes_sent += s;
		}
	}
	return true;
}

void Socket::closeWritingChannel() {
	shutdown(this->socket, SHUT_WR);
}

void Socket::closeReadingChannel() {
	shutdown(this->socket, SHUT_RD);
}
