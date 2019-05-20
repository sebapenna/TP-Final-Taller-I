#ifndef TP_FINAL_EXCEPTIONS_H
#define TP_FINAL_EXCEPTIONS_H

#include <iostream>
#include <exception>

using std::exception;

struct BloqueNoPermitePortalException : public exception {
    const char * what() const throw() override {
        return "La superficie del bloque no permite la formación de un portal.";
    }
};



#endif //TP_FINAL_EXCEPTIONS_H
