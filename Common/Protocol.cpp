#include "Protocol.h"
#include "ProtocolTranslator/ProtocolTranslator.h"
#include "exceptions.h"
#include <vector>
#include <string>
#include <exception>
#include <netinet/in.h>

using std::string;
using std::vector;

#define TWO_BYTES   2
#define FOUR_BYTES  4

Protocol::Protocol(const string& host, const string& port)
try : _socket(host, port) {
} catch(const std::exception& e) {
    throw;
}

Protocol::Protocol(Socket &&other) {
    _socket = std::move(other);
}

Protocol::~Protocol() {
    _socket.shutdown();
}

void Protocol::disconnect() {
    _socket.shutdown();
}

void Protocol::operator<<(const int16_t &data) {
    int16_t aux = htons(data);
    _socket.send(&aux, TWO_BYTES);
}

void Protocol::operator>>(int16_t &dest) {
    _socket.recv(&dest, TWO_BYTES);
    dest = ntohs(dest);
}

void Protocol::operator<<(const ProtocolDTO &dto) {
     vector<int16_t> data_vector;
     int res = ProtocolTranslator::translate(&dto, data_vector);
     if (res == -1)
         throw WrongProtocolException();
    for (auto &data : data_vector)
         *this << data;
}

void Protocol::operator>>(std::shared_ptr<ProtocolDTO>& ptr) {
    vector<int16_t> data_vector;
    int16_t command = 0, n_data_to_recv = 0;
    *this >> command;
    data_vector.push_back(command);
    *this >> n_data_to_recv;
    data_vector.push_back(n_data_to_recv);
    for (size_t i = 0; i < n_data_to_recv; ++i) {
        int16_t aux = 0;
        *this >> aux;
        data_vector.push_back(aux);
    }

    ptr = ProtocolTranslator::translate(data_vector);
    if (!ptr)
        throw WrongProtocolException();
}

void Protocol::operator<<(const string &data) {
    auto str_len = (uint32_t) data.length();
    *this << str_len;   // Envio el largo
    _socket.send(data.c_str(), str_len);
}

void Protocol::operator>>(std::string &dest) {
    uint32_t str_len;
    *this >> str_len;   // Recibo largo del string
    std::vector<char> buffer(str_len + 1, 0);   // + 1 => '\0'
    _socket.recv(buffer.data(), str_len);
    dest = std::string(buffer.data());
}

void Protocol::operator<<(const uint32_t &data) {
    uint32_t aux = htonl(data);
    _socket.send(&aux, FOUR_BYTES);
}

void Protocol::operator>>(uint32_t &dest) {
    _socket.recv(&dest, FOUR_BYTES);
    dest = ntohl(dest);
}
