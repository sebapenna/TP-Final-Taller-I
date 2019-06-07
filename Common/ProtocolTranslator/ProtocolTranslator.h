#ifndef PORTAL_PROTOCOLTRANSLATOR_H
#define PORTAL_PROTOCOLTRANSLATOR_H

#include "ProtocolDTO.h"
#include <vector>

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

    static ProtocolDTO* moveLeft(const std::vector<int16_t> &input);
    static ProtocolDTO* moveRight(const std::vector<int16_t> &input);
    static ProtocolDTO* jump(const std::vector<int16_t> &input);
    static ProtocolDTO* stop(const std::vector<int16_t> &input);
    static ProtocolDTO* shootPortal(const std::vector<int16_t> &input);
    static ProtocolDTO* shootPinTool(const std::vector<int16_t> &input);
    static ProtocolDTO* liftRock(const std::vector<int16_t> &input);
    static ProtocolDTO* dropRock(const std::vector<int16_t> &input);
    static ProtocolDTO* playerChellId(const std::vector<int16_t> &input);
    static ProtocolDTO* rockBlockData(const std::vector<int16_t> &input);
    static ProtocolDTO* metalBlockData(const std::vector<int16_t> &input);
    static ProtocolDTO* metalDiagonalBlockData(const std::vector<int16_t> &input);
    static ProtocolDTO* energyTransmitterData(const std::vector<int16_t> &input);
    static ProtocolDTO* energyReceiverData(const std::vector<int16_t> &input);
    static ProtocolDTO* acidData(const std::vector<int16_t> &input);
    static ProtocolDTO* buttonData(const std::vector<int16_t> &input);
    static ProtocolDTO* gateData(const std::vector<int16_t> &input);
    static ProtocolDTO* energyBarrierData(const std::vector<int16_t> &input);
    static ProtocolDTO* rockData(const std::vector<int16_t> &input);
    static ProtocolDTO* energyBallData(const std::vector<int16_t> &input);
    static ProtocolDTO* portalData(const std::vector<int16_t> &input);
    static ProtocolDTO* pinToolData(const std::vector<int16_t> &input);
    static ProtocolDTO* chellData(const std::vector<int16_t> &input);
    static ProtocolDTO* buttonState(const std::vector<int16_t> &input);
    static ProtocolDTO* energyTransmitterActivate(const std::vector<int16_t> &input);
    static ProtocolDTO* energyReceiverActivate(const std::vector<int16_t> &input);
    static ProtocolDTO* gateState(const std::vector<int16_t> &input);

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
    static ProtocolDTO* translate(const std::vector<int16_t> &input);
};


#endif //PORTAL_PROTOCOLTRANSLATOR_H
