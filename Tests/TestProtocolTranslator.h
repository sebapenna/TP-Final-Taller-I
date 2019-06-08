#ifndef PORTAL_TESTPROTOCOLTRANSLATOR_H
#define PORTAL_TESTPROTOCOLTRANSLATOR_H

#include <string>
#include <vector>
#include <memory>
#include <cppunit/extensions/HelperMacros.h>
#include <Common/ProtocolTranslator/ProtocolTranslator.h>
#include <Common/ProtocolTranslator/MoveLeftDTO.h>
#include <Common/ProtocolTranslator/MoveRightDTO.h>
#include <Common/ProtocolTranslator/JumpDTO.h>
#include <Common/ProtocolTranslator/StopDTO.h>
#include <Common/ProtocolTranslator/ShootPortalDTO.h>
#include <Common/ProtocolTranslator/ShootPinToolDTO.h>
#include <Common/ProtocolTranslator/LiftRockDTO.h>
#include <Common/ProtocolTranslator/DropRockDTO.h>
#include <Common/ProtocolTranslator/PlayerChellIdDTO.h>
#include <Common/ProtocolTranslator/RockBlockDTO.h>
#include <Common/ProtocolTranslator/MetalBlockDTO.h>
#include <Common/ProtocolTranslator/MetalDiagonalBlockDTO.h>
#include <Common/ProtocolTranslator/EnergyTransmitterDTO.h>
#include <Common/ProtocolTranslator/EnergyReceiverDTO.h>
#include <Common/ProtocolTranslator/AcidDTO.h>
#include <Common/ProtocolTranslator/ButtonDTO.h>
#include <Common/ProtocolTranslator/GateDTO.h>
#include <Common/ProtocolTranslator/EnergyBarrierDTO.h>
#include <Common/ProtocolTranslator/RockDTO.h>
#include <Common/ProtocolTranslator/EnergyBallDTO.h>
#include <Common/ProtocolTranslator/PortalDTO.h>
#include <Common/ProtocolTranslator/PinToolDTO.h>
#include <Common/ProtocolTranslator/ChellDTO.h>
#include <Common/ProtocolTranslator/ButtonStateDTO.h>
#include <Common/ProtocolTranslator/EnergyTransmitterActivateDTO.h>
#include <Common/ProtocolTranslator/EnergyReceiverActivateDTO.h>
#include <Common/ProtocolTranslator/GateStateDTO.h>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

class TestProtocolTranslator : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( TestProtocolTranslator );
        CPPUNIT_TEST(testTranslateMoveLeftDTO);
        CPPUNIT_TEST(testTranslateMoveLeftData);
        CPPUNIT_TEST(testTranslateMoveRightDTO);
        CPPUNIT_TEST(testTranslateMoveRightData);
        CPPUNIT_TEST(testTranslateJumpDTO);
        CPPUNIT_TEST(testTranslateJumpData);
        CPPUNIT_TEST(testTranslateStopDTO);
        CPPUNIT_TEST(testTranslateStopData);
        CPPUNIT_TEST(testTranslateShootPortalDTO);
        CPPUNIT_TEST(testTranslateShootPortalData);
        CPPUNIT_TEST(testTranslateShootPinToolDTO);
        CPPUNIT_TEST(testTranslateShootPinToolData);
        CPPUNIT_TEST(testTranslateLiftRockDTO);
        CPPUNIT_TEST(testTranslateLiftRockData);
        CPPUNIT_TEST(testTranslateDropRockDTO);
        CPPUNIT_TEST(testTranslateDropRockData);
        CPPUNIT_TEST(testTranslatePlayerChellIdDTO);
        CPPUNIT_TEST(testTranslatePlayerChellIdData);
        CPPUNIT_TEST(testTranslateRockBlockDTO);
        CPPUNIT_TEST(testTranslateRockBlockData);
        CPPUNIT_TEST(testTranslateMetalBlockDTO);
        CPPUNIT_TEST(testTranslateMetalBlockData);
        CPPUNIT_TEST(testTranslateMetalDiagonalBlockDTO);
        CPPUNIT_TEST(testTranslateMetalDiagonalBlockData);
        CPPUNIT_TEST(testTranslateEnergyTransmitterDTO);
        CPPUNIT_TEST(testTranslateEnergyTransmitterData);
        CPPUNIT_TEST(testTranslateEnergyReceiverDTO);
        CPPUNIT_TEST(testTranslateEnergyReceiverData);
        CPPUNIT_TEST(testTranslateAcidDTO);
        CPPUNIT_TEST(testTranslateAcidData);
        CPPUNIT_TEST(testTranslateButtonDTO);
        CPPUNIT_TEST(testTranslateButtonData);
        CPPUNIT_TEST(testTranslateGateDTO);
        CPPUNIT_TEST(testTranslateGateData);
        CPPUNIT_TEST(testTranslateEnergyBarrierDTO);
        CPPUNIT_TEST(testTranslateEnergyBarrierData);
        CPPUNIT_TEST(testTranslateRockDTO);
        CPPUNIT_TEST(testTranslateRockData);
        CPPUNIT_TEST(testTranslateEnergyBallDTO);
        CPPUNIT_TEST(testTranslateEnergyBallData);
        CPPUNIT_TEST(testTranslatePortalDTO);
        CPPUNIT_TEST(testTranslatePortalData);
        CPPUNIT_TEST(testTranslatePinToolDTO);
        CPPUNIT_TEST(testTranslatePinToolData);
        CPPUNIT_TEST(testTranslateChellDTO);
        CPPUNIT_TEST(testTranslateChellData);
        CPPUNIT_TEST(testTranslateButtonStateDTO);
        CPPUNIT_TEST(testTranslateButtonStateData);
        CPPUNIT_TEST(testTranslateEnergyTransmitterActivateDTO);
        CPPUNIT_TEST(testTranslateEnergyTransmitterActivateData);
        CPPUNIT_TEST(testTranslateEnergyReceiverActivateDTO);
        CPPUNIT_TEST(testTranslateEnergyReceiverActivateData);
        CPPUNIT_TEST(testTranslateGateStateDTO);
        CPPUNIT_TEST(testTranslateGateStateData);
    CPPUNIT_TEST_SUITE_END();

private:
    vector<int16_t> output;
    int extra_data = 2; // Datos obligatorios a enviar en protocolo
    
public:
    void testTranslateMoveLeftDTO() {
        cout << endl << endl << "TEST PROTOCOL TRANSLATOR";
        cout << endl << "TEST traducir MoveLeftDTO a datos: ";
        shared_ptr<ProtocolDTO> pdto(new MoveLeftDTO());
        int vec_size = ProtocolTranslator::translate(pdto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_MOVE_LEFT, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(MOVE_LEFT_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateMoveLeftData() {
        cout << endl << "TEST traducir datos MoveLeft a DTO: ";
        vector<int16_t> v;
        v.push_back(MOVE_LEFT_ARGS);
        v.push_back(PROTOCOL_MOVE_LEFT);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (MoveLeftDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_MOVE_LEFT, dto->getClassId());
        cout << "OK";
    }
    void testTranslateMoveRightDTO() {
        cout << endl << "TEST traducir MoveRightDTO a datos: ";
        shared_ptr<ProtocolDTO> pdto(new MoveRightDTO());
        int vec_size = ProtocolTranslator::translate(pdto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_MOVE_RIGHT, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(MOVE_RIGHT_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateMoveRightData() {
        cout << endl << "TEST traducir datos MoveRight a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_MOVE_RIGHT);
        v.push_back(MOVE_RIGHT_ARGS);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (MoveRightDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_MOVE_RIGHT, dto->getClassId());
        cout << "OK";
    }

    void testTranslateJumpDTO() {
        cout << endl << "TEST traducir JumpDTO a datos: ";
        shared_ptr<ProtocolDTO> pdto(new JumpDTO());
        auto vec_size = ProtocolTranslator::translate(pdto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_JUMP, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(JUMP_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateJumpData() {
        cout << endl << "TEST traducir datos Jump a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_JUMP);
        v.push_back(JUMP_ARGS);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (JumpDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_JUMP, dto->getClassId());
        cout << "OK";
    }

    void testTranslateStopDTO() {
        cout << endl << "TEST traducir StopDTO a datos: ";
        shared_ptr<ProtocolDTO> s_dto(new StopDTO());
        int vec_size = ProtocolTranslator::translate(s_dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_STOP, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(STOP_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateStopData() {
        cout << endl << "TEST traducir datos Stop a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_STOP);
        v.push_back(STOP_ARGS);
        auto p = ProtocolTranslator::translate(v);
        auto dto = p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_STOP, dto->getClassId());
        cout << "OK";
    }

    void testTranslateShootPortalDTO() {
        cout << endl << "TEST traducir ShootPortalDTO a datos: ";
        shared_ptr<ProtocolDTO> p_dto(new ShootPortalDTO(BLUE_PORTAL, -10, 50));
        int vec_size = ProtocolTranslator::translate(p_dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_SHOOT_PORTAL, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(BLUE_PORTAL, output.at(SHOOT_PORTAL_COLOUR_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -10, output.at(SHOOT_PORTAL_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 50, output.at(SHOOT_PORTAL_Y_POS));
        CPPUNIT_ASSERT_EQUAL(SHOOT_PORTAL_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateShootPortalData() {
        cout << endl << "TEST traducir datos ShootPortal a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_SHOOT_PORTAL);
        v.push_back(SHOOT_PORTAL_ARGS);
        v.push_back(ORANGE_PORTAL); // color
        v.push_back(50);    // x
        v.push_back(-5);    // y
        auto p = ProtocolTranslator::translate(v);
        auto dto = (ShootPortalDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_SHOOT_PORTAL, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL(ORANGE_PORTAL, dto->getColor());
        CPPUNIT_ASSERT_EQUAL((int16_t) 50, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) -5, dto->getY());
        cout << "OK";
    }

    void testTranslateShootPinToolDTO() {
        cout << endl << "TEST traducir ShootPinToolDTO a datos: ";
        shared_ptr<ProtocolDTO> p_dto(new ShootPinToolDTO(-10, 50));
        int vec_size = ProtocolTranslator::translate(p_dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_SHOOT_PIN_TOOL, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t ) -10, output.at(SHOOT_PT_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 50, output.at(SHOOT_PT_Y_POS));
        CPPUNIT_ASSERT_EQUAL(SHOOT_PT_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateShootPinToolData() {
        cout << endl << "TEST traducir datos ShootPinTool a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_SHOOT_PIN_TOOL);
        v.push_back(SHOOT_PT_ARGS);
        v.push_back(-10);    // x
        v.push_back(5);    // y
        auto p = ProtocolTranslator::translate(v);
        auto dto = (ShootPinToolDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_SHOOT_PIN_TOOL, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t)-10, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t)5, dto->getY());
        cout << "OK";
    }

    void testTranslateLiftRockDTO() {
        cout << endl << "TEST traducir LiftRockDTO a datos: ";
        shared_ptr<ProtocolDTO>  dto(new LiftRockDTO(2));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_LIFT_ROCK, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t)2, output.at(LIFT_ROCK_ID_POS));
        CPPUNIT_ASSERT_EQUAL(LIFT_ROCK_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateLiftRockData() {
        cout << endl << "TEST traducir datos LiftRock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_LIFT_ROCK);
        v.push_back(LIFT_ROCK_ARGS);
        v.push_back(2);    // y
        auto p = ProtocolTranslator::translate(v);
        auto dto = (LiftRockDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_LIFT_ROCK, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getRockId());
        cout << "OK";
    }

    void testTranslateDropRockDTO() {
        cout << endl << "TEST traducir DropRockDTO a datos: ";
        shared_ptr<ProtocolDTO>  dto(new DropRockDTO());
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_DROP_ROCK, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(DROP_ROCK_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateDropRockData() {
        cout << endl << "TEST traducir datos DropRock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_DROP_ROCK);
        v.push_back(DROP_ROCK_ARGS);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (RockDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_DROP_ROCK, dto->getClassId());
        cout << "OK";
    }

    void testTranslatePlayerChellIdDTO() {
        cout << endl << "TEST traducir PlayerChellIdDTO a datos: ";
        shared_ptr<ProtocolDTO>  dto(new PlayerChellIdDTO(2));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PLAYER_CHELL_ID, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, output.at(PLAYER_CHELL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(PLAYER_CHELL_ID_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslatePlayerChellIdData() {
        cout << endl << "TEST traducir datos PlayerChellId a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_PLAYER_CHELL_ID);
        v.push_back(PLAYER_CHELL_ID_ARGS);
        v.push_back(1);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (PlayerChellIdDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PLAYER_CHELL_ID, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 1, dto->getChellId());
        cout << "OK";
    }

    void testTranslateRockBlockDTO() {
        cout << endl << "TEST traducir RockBlockDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new RockBlockDTO(-2, 0, 10, 20));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_BLOCK_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ROCK_BLOCK_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ROCK_BLOCK_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, output.at(ROCK_BLOCK_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 20, output.at(ROCK_BLOCK_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(ROCK_BLOCK_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateRockBlockData() {
        cout << endl << "TEST traducir datos RockBlock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ROCK_BLOCK_DATA);
        v.push_back(ROCK_BLOCK_ARGS);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (RockBlockDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_BLOCK_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        cout << "OK";
    }

    void testTranslateMetalBlockDTO() {
        cout << endl << "TEST traducir MetalBlockDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new MetalBlockDTO(-2, 0, 10, 20));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_BLOCK_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(METAL_BLOCK_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(METAL_BLOCK_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, output.at(METAL_BLOCK_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 20, output.at(METAL_BLOCK_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(METAL_BLOCK_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateMetalBlockData() {
        cout << endl << "TEST traducir datos MetalBlock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_METAL_BLOCK_DATA);
        v.push_back(METAL_BLOCK_ARGS);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (MetalBlockDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_BLOCK_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        cout << "OK";
    }

    void testTranslateMetalDiagonalBlockDTO() {
        cout << endl << "TEST traducir MetalDiagonalBlockDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new MetalDiagonalBlockDTO(-2, 0, 4, O_NO));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_DIAGONAL_BLOCK_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(METAL_DIAG_BLOCK_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(METAL_DIAG_BLOCK_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(METAL_DIAG_BLOCK_SIDE_LEN_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) O_NO, output.at(METAL_DIAG_BLOCK_ORIENT_POS));
        CPPUNIT_ASSERT_EQUAL(METAL_DIAG_BLOCK_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateMetalDiagonalBlockData() {
        cout << endl << "TEST traducir datos MetalDiagonalBlock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_METAL_DIAGONAL_BLOCK_DATA);
        v.push_back(METAL_DIAG_BLOCK_ARGS);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(O_NE);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (MetalDiagonalBlockDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_DIAGONAL_BLOCK_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL((int16_t) O_NE, dto->getOrientation());
        cout << "OK";
    }

    void testTranslateEnergyTransmitterDTO() {
        cout << endl << "TEST traducir EnergyTransmitterDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new EnergyTransmitterDTO(0, -2, 0, 4, O_E));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_TRANSMITTER_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ENRG_TRANSM_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ENRG_TRANSM_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ENRG_TRANSM_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(ENRG_TRANSM_SIDE_LEN_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) O_E, output.at(ENRG_TRANSM_DIRECTION_POS));
        CPPUNIT_ASSERT_EQUAL(ENRG_TRANSM_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateEnergyTransmitterData() {
        cout << endl << "TEST traducir datos EnergyTransmitter a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ENERGY_TRANSMITTER_DATA);
        v.push_back(ENRG_TRANSM_ARGS);
        v.push_back(2);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(O_NE);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (EnergyTransmitterDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_TRANSMITTER_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL((int16_t) O_NE, dto->getDirection());
        cout << "OK";
    }

    void testTranslateEnergyReceiverDTO() {
        cout << endl << "TEST traducir EnergyReceiverDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new EnergyReceiverDTO(0, -2, 0, 4));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_RECEIVER_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ENRG_RECVR_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ENRG_RECVR_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ENRG_RECVR_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(ENRG_RECVR_SIDE_LEN_POS));
        CPPUNIT_ASSERT_EQUAL(ENRG_RECVR_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateEnergyReceiverData() {
        cout << endl << "TEST traducir datos EnergyReceiver a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ENERGY_RECEIVER_DATA);
        v.push_back(ENRG_RECVR_ARGS);
        v.push_back(2);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (EnergyReceiverDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_RECEIVER_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getSideLength());
        cout << "OK";
    }

    void testTranslateAcidDTO() {
        cout << endl << "TEST traducir AcidDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new AcidDTO(-2, 0, 2, 3));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ACID_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ACID_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ACID_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, output.at(ACID_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 3, output.at(ACID_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(ACID_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateAcidData() {
        cout << endl << "TEST traducir datos Acid a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ACID_DATA);
        v.push_back(ACID_ARGS);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (AcidDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ACID_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        cout << "OK";
    }

    void testTranslateButtonDTO() {
        cout << endl << "TEST traducir ButtonDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new ButtonDTO(0, -2, 0, 2, 3));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_BUTTON_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(BUTTON_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(BUTTON_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(BUTTON_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, output.at(BUTTON_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 3, output.at(BUTTON_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(BUTTON_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateButtonData() {
        cout << endl << "TEST traducir datos Button a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_BUTTON_DATA);
        v.push_back(BUTTON_ARGS);
        v.push_back(4);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (ButtonDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_BUTTON_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        cout << "OK";
    }

    void testTranslateGateDTO() {
        cout << endl << "TEST traducir GateDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new GateDTO(0, -2, 0, 2, 3));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_GATE_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(GATE_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(GATE_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(GATE_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, output.at(GATE_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 3, output.at(GATE_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(GATE_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateGateData() {
        cout << endl << "TEST traducir datos Gate a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_GATE_DATA);
        v.push_back(GATE_ARGS);
        v.push_back(4);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (GateDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_GATE_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        cout << "OK";
    }
    
    void testTranslateEnergyBarrierDTO() {
        cout << endl << "TEST traducir EnergyBarrierDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new EnergyBarrierDTO(-2, 0, 10, 20));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_BARRIER_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ENRG_BARRIER_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ENRG_BARRIER_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, output.at(ENRG_BARRIER_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 20, output.at(ENRG_BARRIER_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(ENRG_BARRIER_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateEnergyBarrierData() {
        cout << endl << "TEST traducir datos EnergyBarrier a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ENERGY_BARRIER_DATA);
        v.push_back(ENRG_BARRIER_ARGS);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (EnergyBarrierDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_BARRIER_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        cout << "OK";
    }
    
    void testTranslateRockDTO() {
        cout << endl << "TEST traducir RockDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new RockDTO(10, -2, 0, 10, DELETE));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, output.at(ROCK_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ROCK_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ROCK_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, output.at(ROCK_SIDE_LEN_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) DELETE, output.at(ROCK_DELETE_STATE_POS));
        CPPUNIT_ASSERT_EQUAL(ROCK_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateRockData() {
        cout << endl << "TEST traducir datos Rock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ROCK_DATA);
        v.push_back(ROCK_ARGS);
        v.push_back(8);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(DONT_DELETE);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (RockDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 8, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL(DONT_DELETE, dto->getDeleteState());
        cout << "OK";
    }
    
    void testTranslateEnergyBallDTO() {
        cout << endl << "TEST traducir EnergyBallDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new EnergyBallDTO(10, -2, 0, 4, DELETE));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_BALL_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, output.at(ENRG_BALL_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ENRG_BALL_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ENRG_BALL_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(ENRG_BALL_RADIUS_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) DELETE, output.at(ENRG_BALL_DELETE_STATE_POS));
        CPPUNIT_ASSERT_EQUAL(ENRG_BALL_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateEnergyBallData() {
        cout << endl << "TEST traducir datos EnergyBall a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ENERGY_BALL_DATA);
        v.push_back(ENRG_BALL_ARGS);
        v.push_back(8);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(DONT_DELETE);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (EnergyBallDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_BALL_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 8, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getRadius());
        CPPUNIT_ASSERT_EQUAL(DONT_DELETE, dto->getDeleteState());
        cout << "OK";
    }
    
    void testTranslatePortalDTO() {
        cout << endl << "TEST traducir PortalDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new PortalDTO(4, -2, 0, 4, 5, ORANGE_PORTAL, DELETE));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PORTAL_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(PORTAL_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(PORTAL_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(PORTAL_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(PORTAL_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, output.at(PORTAL_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) ORANGE_PORTAL, output.at(PORTAL_COLOUR_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) DELETE, output.at(PORTAL_DELETE_STATE_POS));
        CPPUNIT_ASSERT_EQUAL(PORTAL_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslatePortalData() {
        cout << endl << "TEST traducir datos Portal a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_PORTAL_DATA);
        v.push_back(PORTAL_ARGS);
        v.push_back(8);
        v.push_back(5);
        v.push_back(10);
        v.push_back(2);
        v.push_back(3);
        v.push_back(BLUE_PORTAL);
        v.push_back(DONT_DELETE);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (PortalDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PORTAL_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 8, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 3, dto->getHeight());
        CPPUNIT_ASSERT_EQUAL((int16_t) BLUE_PORTAL, dto->getColour());
        CPPUNIT_ASSERT_EQUAL(DONT_DELETE, dto->getDeleteState());
        cout << "OK";
    }
    
    void testTranslatePinToolDTO() {
        cout << endl << "TEST traducir PinToolDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new PinToolDTO(4, -2, 0, 4, 5, DELETE));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PIN_TOOL_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(PIN_TOOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(PIN_TOOL_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(PIN_TOOL_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(PIN_TOOL_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, output.at(PIN_TOOL_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) DELETE, output.at(PIN_TOOL_DELETE_STATE_POS));
        CPPUNIT_ASSERT_EQUAL(PIN_TOOL_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslatePinToolData() {
        cout << endl << "TEST traducir datos PinTool a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_PIN_TOOL_DATA);
        v.push_back(PIN_TOOL_ARGS);
        v.push_back(8);
        v.push_back(5);
        v.push_back(10);
        v.push_back(2);
        v.push_back(3);
        v.push_back(DONT_DELETE);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (PinToolDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PIN_TOOL_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 8, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 3, dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(DONT_DELETE, dto->getDeleteState());
        cout << "OK";
    }
    
    void testTranslateChellDTO() {
        cout << endl << "TEST traducir ChellDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new ChellDTO(4, -2, 0, 4, 5, EAST, NOT_TILTED, NOT_MOVING, NOT_JUMPING,
                NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_CHELL_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(CHELL_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(CHELL_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(CHELL_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(CHELL_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, output.at(CHELL_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(EAST, output.at(CHELL_DIRECTION_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) NOT_TILTED, output.at(CHELL_TILTED_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) NOT_MOVING, output.at(CHELL_MOVING_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) NOT_JUMPING, output.at(CHELL_JUMPING_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) NOT_SHOOTING, output.at(CHELL_SHOOTING_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) NOT_CARRYING, output.at(CHELL_CARRYING_ROCK_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) DONT_DELETE, output.at(CHELL_DELETE_STATE_POS));
        CPPUNIT_ASSERT_EQUAL(CHELL_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateChellData() {
        cout << endl << "TEST traducir datos Chell a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_CHELL_DATA);
        v.push_back(CHELL_ARGS);
        v.push_back(1);
        v.push_back(5);
        v.push_back(10);
        v.push_back(2);
        v.push_back(3);
        v.push_back(WEST);
        v.push_back(NORTH_EAST);
        v.push_back(MOVING);
        v.push_back(JUMPING);
        v.push_back(SHOOTING);
        v.push_back(CARRYING);
        v.push_back(DELETE);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (ChellDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_CHELL_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 1, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 3, dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(WEST, dto->getDirection());
        CPPUNIT_ASSERT_EQUAL(NORTH_EAST, dto->getTilted());
        CPPUNIT_ASSERT_EQUAL(MOVING, dto->getMoving());
        CPPUNIT_ASSERT_EQUAL(JUMPING, dto->getJumping());
        CPPUNIT_ASSERT_EQUAL(SHOOTING, dto->getShooting());
        CPPUNIT_ASSERT_EQUAL(CARRYING, dto->getCarryingRock());
        CPPUNIT_ASSERT_EQUAL(DELETE, dto->getDeleteState());
        cout << "OK";
    }

    void testTranslateButtonStateDTO() {
        cout << endl << "TEST traducir ButtonStateDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new ButtonStateDTO(4, PRESSED));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_BUTTON_CHANGE_STATE, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(BUTTON_CHANGE_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) PRESSED, output.at(BUTTON_CHANGE_STATE_POS));
        CPPUNIT_ASSERT_EQUAL(BUTTON_CHANGE_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateButtonStateData() {
        cout << endl << "TEST traducir datos ButtonState a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_BUTTON_CHANGE_STATE);
        v.push_back(BUTTON_CHANGE_ARGS);
        v.push_back(2);
        v.push_back(NOT_PRESSED);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (ButtonStateDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_BUTTON_CHANGE_STATE, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) NOT_PRESSED, dto->getState());
        cout << "OK";
    }

    void testTranslateEnergyTransmitterActivateDTO() {
        cout << endl << "TEST traducir EnergyTransmitterActivateDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new EnergyTransmitterActivateDTO(4));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_TRANSMITTER_ACTIVATE, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(ENRG_TRANSM_ACTV_ID_POS));
        CPPUNIT_ASSERT_EQUAL(ENRG_TRANSM_ACTV_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateEnergyTransmitterActivateData() {
        cout << endl << "TEST traducir datos EnergyTransmitterActivate a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ENERGY_TRANSMITTER_ACTIVATE);
        v.push_back(ENRG_TRANSM_ACTV_ARGS);
        v.push_back(2);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (EnergyTransmitterActivateDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_TRANSMITTER_ACTIVATE, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getId());
        cout << "OK";
    }

    void testTranslateEnergyReceiverActivateDTO() {
        cout << endl << "TEST traducir EnergyReceiverActivateDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new EnergyReceiverActivateDTO(4));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_RECEIVER_ACTIVATE, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(ENRG_RECVR_ACTV_ID_POS));
        CPPUNIT_ASSERT_EQUAL(ENRG_RECVR_ACTV_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateEnergyReceiverActivateData() {
        cout << endl << "TEST traducir datos EnergyReceiverActivate a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ENERGY_RECEIVER_ACTIVATE);
        v.push_back(ENRG_RECVR_ACTV_ARGS);
        v.push_back(2);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (EnergyReceiverActivateDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_RECEIVER_ACTIVATE, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getId());
        cout << "OK";
    }

    void testTranslateGateStateDTO() {
        cout << endl << "TEST traducir GateStateDTO a datos: ";
        shared_ptr<ProtocolDTO> dto(new GateStateDTO(4, OPEN));
        int vec_size = ProtocolTranslator::translate(dto.get(), output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_GATE_CHANGE_STATE, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(GATE_CHANGE_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) OPEN, output.at(GATE_CHANGE_STATE_POS));
        CPPUNIT_ASSERT_EQUAL(GATE_CHANGE_ARGS + extra_data, vec_size);
        cout << "OK";
    }

    void testTranslateGateStateData() {
        cout << endl << "TEST traducir datos GateState a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_GATE_CHANGE_STATE);
        v.push_back(GATE_CHANGE_ARGS);
        v.push_back(2);
        v.push_back(CLOSED);
        auto p = ProtocolTranslator::translate(v);
        auto dto = (GateStateDTO*) p.get();
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_GATE_CHANGE_STATE, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) CLOSED, dto->getState());
        cout << "OK";
    }
};
    
#endif //PORTAL_TESTPROTOCOLTRANSLATOR_H
