#include "Protocol.h"
#include "ProtocolTranslator/ProtocolTranslator.h"
#include <string>
#include <exception>

using std::string;

Protocol::Protocol(const string& host, const string& port)
try : socket(host, port) {
} catch(const std::exception& e) {
    throw;
}

Protocol::Protocol(Socket &&other) {
    socket = std::move(other);
}

void Protocol::operator<<(ProtocolDTO *dto) {

}
