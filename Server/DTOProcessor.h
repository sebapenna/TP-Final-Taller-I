#ifndef PORTAL_DTOPROCESSOR_H
#define PORTAL_DTOPROCESSOR_H

#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include "World.h"
#include <vector>

class DTOProcessor {
private:
    World *_world;  // Sera utilizado para obtener los elementos a los cuales aplicar la accion

public:
    explicit DTOProcessor(World *world);

    // Procesa el dto recibido por el servidor para realizar una determinada accion
    void applyActionToChell(ProtocolDTO *dto, size_t chell_id);

//    void generateUpdatedObjectsDTO()
};


#endif //PORTAL_DTOPROCESSOR_H
