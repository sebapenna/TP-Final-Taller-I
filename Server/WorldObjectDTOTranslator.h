#ifndef PORTAL_WORLDOBJECTDTOTRANSLATOR_H
#define PORTAL_WORLDOBJECTDTOTRANSLATOR_H

#include <memory>
#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include <Server/Model/Collidable.h>

// Genera los DTO a enviar en base al estado del modelo
class WorldObjectDTOTranslator {
public:
    // Genera un DTO en base al estado actual del objeto collidable. Se debe setear
    // inital_data_ a true si se quiere enviar los datos de la configuracion inicial, de
    // esta manera al realizar las traducciones (si seteado a false) se verificara si los distintos
    // cuerpos actualizaron sus estados.
    // PRE: collidable no debe ser un cuerpo a eliminar, solo un cuerpo a actualizar.
    static std::shared_ptr<ProtocolDTO> translate(Collidable* collidable, bool initial_data = false);

    // Generado DTO para objeto a ser eliminado en base a su id y el id de la clase.
    static std::shared_ptr<ProtocolDTO> translate(const size_t &object_id,
                                                  const uint8_t &object_class_id);
};


#endif //PORTAL_WORLDOBJECTDTOTRANSLATOR_H
