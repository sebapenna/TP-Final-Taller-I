#ifndef PORTAL_PROTOCOLTRANSLATOR_H
#define PORTAL_PROTOCOLTRANSLATOR_H

#include "ProtocolDTO.h"
#include <vector>
#include <memory>

class ProtocolTranslator {
private:
    static void shootPortal(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void shootPinTool(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void liftRock(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void playerChellId(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void rockBlockData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void metalBlockData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void metalDiagonalBlockData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void energyTransmitterData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void energyReceiverData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void acidData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void buttonData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void gateData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void energyBarrierData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void rockData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void energyBallData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void portalData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void pinToolData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void chellData(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void buttonState(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void energyTransmitterActivate(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void energyReceiverActivate(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void gateState(const ProtocolDTO *dto, std::vector<int16_t> &output);
    static void cakeData(const ProtocolDTO *dto, std::vector<int16_t> &output);

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
    // input, nullptr en caso de error. Usuario es el encargado de liberar
    // memoria del puntero
    static std::shared_ptr<ProtocolDTO> translate(const std::vector<int16_t> &input);
};


#endif //PORTAL_PROTOCOLTRANSLATOR_H
