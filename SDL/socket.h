#ifndef __COMMON_SOCKET_H__
#define __COMMON_SOCKET_H__

#include <string>
#include <stdbool.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

// It sends and receives char*
// It represents the most basic connection between two different systems
class Socket {
private:
    // The file descriptor for sockets
	int socket;
	explicit Socket(int skt);
	// It doesn't make sense to be able to copy this.
	Socket(const Socket& origin) = delete;
	// and the assigment for copy too
	const Socket& operator=(const Socket& origin) = delete; 

public:
    // Creates the socket
    Socket();
    // Close the socket
    ~Socket();
    // Receives another socket through move semantics
    Socket(Socket&& origin);
	Socket& operator=(Socket&& origin);

	// Binds to a port and start listening
    bool bindAndListen(const std::string& port, int amount);

    // Connects to a port and host
	bool connect(const std::string& host_name, const std::string& port);

	// Accepts a new connection
	Socket accept();

	// Receives a message
	int recvMessage(char* buf, int size);

	// Sends a message
	bool sendMessage(char* request, int bytes_to_send);

	// Close writing channel of the socket
	void closeWritingChannel();

	// Close Reading channel of the socket
	void closeReadingChannel();

	// It shows whether a  socket is still valid.
	bool invalid();
};

#endif
