#ifndef PORTAL_PROTOCOLTRANSLATOR_H
#define PORTAL_PROTOCOLTRANSLATOR_H

#include "ProtocolDTO.h"
#include <vector>

class ProtocolTranslator {
private:
    static void shootPortal(const ProtocolDTO *dto,
            std::vector<int16_t> &output);
    static void shootPinTool(const ProtocolDTO *dto,
            std::vector<int16_t> &output);
    static void liftRock(const ProtocolDTO *dto, std::vector<int16_t> &output);

    static ProtocolDTO* moveLeft(const std::vector<int16_t> &input);
    static ProtocolDTO* moveRight(const std::vector<int16_t> &input);
    static ProtocolDTO* jump(const std::vector<int16_t> &input);
    static ProtocolDTO* stop(const std::vector<int16_t> &input);
    static ProtocolDTO* portal(const std::vector<int16_t> &input);
    static ProtocolDTO* pinTool(const std::vector<int16_t> &input);
    static ProtocolDTO* liftRock(const std::vector<int16_t> &input);
    static ProtocolDTO* dropRock(const std::vector<int16_t> &input);

public:
    // PRE: output debe ser un vector vacio para almacenar correctamente los
    // datos contenidos en el dto y luego poder ser procesados correctamente.
    // POST: output contiene todos los datos contenidos en el dto, en el
    // orden establecido por el protocolo.
    // Retorna la cantidad de elementos agregados al vector, -1 en caso de error
    static int translate(const ProtocolDTO *dto, std::vector<int16_t> &output);

    // PRE: input debe contener todos los datos del dto que corresponda, en
    // el orden establecido por le protocolo.
    // POST: se creo el DTO que haya sido correspondiente con todos sus datos
    // Retorna un ProtocolDTO* conteniendo toda la informacion brindada en
    // input, nullptr en caso de error.
    static ProtocolDTO* translate(const std::vector<int16_t> &input);
};


#endif //PORTAL_PROTOCOLTRANSLATOR_H
