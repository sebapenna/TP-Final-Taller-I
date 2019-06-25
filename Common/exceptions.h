#ifndef TP_FINAL_EXCEPTIONS_H
#define TP_FINAL_EXCEPTIONS_H

#include <iostream>
#include <exception>

using std::exception;

struct BlockCantCreatePortalException : public exception {
    const char * what() const throw() override {
        return "La superficie del bloque no permite la formación de un portal.";
    }
};

struct ChellNotOnGroundException : public exception {
    const char *what() const throw() override {
        return "Chell no se encuentra sobre una superficie donde saltar.";
    }
};

struct CantConnectException : public exception {
    const char * what() const throw() override {
        return "No se pudo conectar el socket.\n";
    }
};

struct FileOpenException : public exception {
    const char * what() const throw() override {
        return "No se pudo abrir el archivo.\n";
    }
};

struct FailedSendException : public exception {
    const char * what() const throw() override {
        return "No se pudo enviar la informacion a traves del socket.\n";
    }
};

struct FailedRecvException : public exception {
    const char * what() const throw() override {
        return "No se pudo recibir la informacion a traves del socket.\n";
    }
};

struct CloseConnectionException : public exception {
    const char * what() const throw() override {
        return "El socket ha sido cerrado.\n";
    }
};

struct WrongArgumentException : public exception {
    const char * what() const throw() override {
        return "Error: argumentos invalidos.\n";
    }
};

struct UnknownException : public exception {
    const char * what() const throw() override {
        return "Error desconocido.\n";
    }
};

struct WrongProtocolException : public exception {
    const char * what() const throw() override {
        return "Protocolo enviado incorrecto.\n";
    }
};

struct CantJoinGameException : public exception {
    const char * what() const throw() override {
        return "No es posible unirse a la partida.\n";
    }
};

struct CouldntAllocateFrameException : public exception {
    const char * what() const throw() override {
        return "No se pudo reservar memoria para frame.\n";
    }
};

struct CouldntFindOutputFormatException : public exception {
    const char * what() const throw() override {
        return "No se encontró formato de salida.\n";
    }
};

struct CouldntFindEncoderException : public exception {
    const char * what() const throw() override {
        return "No se pudo instanciar codec.\n";
    }
};

struct SendFrameException : public exception {
    const char * what() const throw() override {
        return "Error al enviar frame.\n";
    }
};

struct EncodeErrorException : public exception {
    const char * what() const throw() override {
        return "Error al codificar.\n";
    }
};

#endif //TP_FINAL_EXCEPTIONS_H
