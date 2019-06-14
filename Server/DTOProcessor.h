#ifndef PORTAL_PROCESSOR_H
#define PORTAL_PROCESSOR_H

#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include "Server/Model/World.h"
#include "WorldObjectDTOTranslator.h"
#include <vector>
#include <memory>

class DTOProcessor {
public:
    // Procesa el dto recibido por el servidor para realizar una determinada accion
    void applyActionToChell(World *world, ProtocolDTO *dto, size_t chell_id);

    // Procesa el vector de clase T (objetos que heredan de Collidable) y en base a sus datos
    // genera los DTO correspondientes, almacenandolos en el vector output. Retorna la cantidad de
    // elementos en output.
    // Se debe setear initial_data a true si se esta enviando la configuracion inicial de la partida
    template <class T>
    int createDTOs(const std::vector<T> &input, std::vector<std::shared_ptr<ProtocolDTO>> &output,
                          bool initial_data = false) {
        for (auto &collidable : input)
            output.push_back(std::move(WorldObjectDTOTranslator::translate(collidable, initial_data)));
        return output.size();
    }

    // Genera el DTO para enviar el id del player indicado
    static std::shared_ptr<ProtocolDTO> createDTO(const size_t& player_id);

    // Genera el DTO para los elementos eliminados en base al id de la clase y el id del objeto
    std::shared_ptr<ProtocolDTO> createDTO(const size_t& object_id, const uint8_t& object_class_id);

    // Genera el DTO para notificar el comienzo del juego
    static std::shared_ptr<ProtocolDTO> createBeginDTO();

};


#endif //PORTAL_PROCESSOR_H
