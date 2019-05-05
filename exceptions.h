#ifndef TP_FINAL_EXCEPTIONS_H
#define TP_FINAL_EXCEPTIONS_H

#include <iostream>
#include <exception>

using std::exception;

struct BloqueOcupadoException : public exception {
    const char * what() const throw() override {
        return "El bloque ya tiene un elemento sobre él.";
    }
};

struct BloqueNoPuedeTenerElementoSobreElException : public exception {
    const char * what() const throw() override {
        return "El bloque no puede tener un elemento sobre él.";
    }
};

struct BloqueNoPermitePortalException : public exception {
    const char * what() const throw() override {
        return "La superficie del bloque no permite la formación de un portal.";
    }
};



#endif //TP_FINAL_EXCEPTIONS_H
