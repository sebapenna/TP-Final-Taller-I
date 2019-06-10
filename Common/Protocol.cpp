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

Protocol::Protocol(const string& host, const string& port)
try : _socket(host, port) {
} catch(const std::exception& e) {
    throw;
}

Protocol::Protocol(Socket &&other) {
    _socket = std::move(other);
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
