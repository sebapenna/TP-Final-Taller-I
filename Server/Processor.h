#ifndef PORTAL_PROCESSOR_H
#define PORTAL_PROCESSOR_H

#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include "Server/Model/World.h"
#include <vector>

// TODO: QUE TENGA MUTEX PARA QUE DISTINTA CHELL NO SE CRUZEN HACIENDO ACCIONES ?
class Processor {
private:
    World *_world;  // Sera utilizado para obtener los elementos a los cuales aplicar la accion

public:
    explicit Processor(World *world);

    // Procesa el dto recibido por el servidor para realizar una determinada accion
    void applyActionToChell(ProtocolDTO *dto, size_t chell_id);

//    void generateUpdatedObjectsDTO()
};


#endif //PORTAL_PROCESSOR_H
