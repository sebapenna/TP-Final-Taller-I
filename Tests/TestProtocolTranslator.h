#ifndef PORTAL_TESTPROTOCOLTRANSLATOR_H
#define PORTAL_TESTPROTOCOLTRANSLATOR_H

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
#include "../src/constants.h"
#include <string>
#include <vector>
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

using std::cout;
using std::endl;
using std::vector;

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
    CPPUNIT_TEST_SUITE_END();

private:
    vector<int16_t> output;
    
public:

    void testTranslateMoveLeftDTO() {
        cout << endl << endl << "TEST PROTOCOL TRANSLATOR";
        cout << endl << "TEST traducir MoveLeftDTO a datos: ";
        auto ml_dto = new MoveLeftDTO();
        int vec_size = ProtocolTranslator::translate(ml_dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_MOVE_LEFT, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(1, vec_size);
        delete ml_dto;
        cout << "OK";
    }

    void testTranslateMoveLeftData() {
        cout << endl << "TEST traducir datos MoveLeft a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_MOVE_LEFT);
        auto dto = ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_MOVE_LEFT, dto->getClassId());
        cout << "OK";
    }

    void testTranslateMoveRightDTO() {
        cout << endl << "TEST traducir MoveRightDTO a datos: ";
        auto mr_dto = new MoveRightDTO();
        int vec_size = ProtocolTranslator::translate(mr_dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_MOVE_RIGHT, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(1, vec_size);
        delete mr_dto;
        cout << "OK";
    }

    void testTranslateMoveRightData() {
        cout << endl << "TEST traducir datos MoveRight a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_MOVE_RIGHT);
        auto dto = ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_MOVE_RIGHT, dto->getClassId());
        cout << "OK";
    }

    void testTranslateJumpDTO() {
        cout << endl << "TEST traducir JumpDTO a datos: ";
        auto *j_dto = new JumpDTO();
        auto vec_size = ProtocolTranslator::translate(j_dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_JUMP, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(1, vec_size);
        delete j_dto;
        cout << "OK";
    }

    void testTranslateJumpData() {
        cout << endl << "TEST traducir datos Jump a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_JUMP);
        auto dto = ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_JUMP, dto->getClassId());
        cout << "OK";
    }

    void testTranslateStopDTO() {
        cout << endl << "TEST traducir StopDTO a datos: ";
        auto s_dto = new StopDTO();
        int vec_size = ProtocolTranslator::translate(s_dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_STOP, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(1, vec_size);
        delete s_dto;
        cout << "OK";
    }

    void testTranslateStopData() {
        cout << endl << "TEST traducir datos Stop a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_STOP);
        auto dto = ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_STOP, dto->getClassId());
        cout << "OK";
    }

    void testTranslateShootPortalDTO() {
        cout << endl << "TEST traducir ShootPortalDTO a datos: ";
        auto p_dto = new ShootPortalDTO(BLUE_PORTAL, -10, 50);
        int vec_size = ProtocolTranslator::translate(p_dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_SHOOT_PORTAL, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(BLUE_PORTAL, output.at(SHOOT_PORTAL_COLOR_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -10, output.at(SHOOT_PORTAL_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 50, output.at(SHOOT_PORTAL_Y_POS));
        CPPUNIT_ASSERT_EQUAL(4, vec_size);
        delete p_dto;
        cout << "OK";
    }

    void testTranslateShootPortalData() {
        cout << endl << "TEST traducir datos ShootPortal a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_SHOOT_PORTAL);
        v.push_back(ORANGE_PORTAL); // color
        v.push_back(50);    // x
        v.push_back(-5);    // y
        auto dto = (ShootPortalDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_SHOOT_PORTAL, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL(ORANGE_PORTAL, dto->getColor());
        CPPUNIT_ASSERT_EQUAL((int16_t) 50, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) -5, dto->getY());
        cout << "OK";
    }

    void testTranslateShootPinToolDTO() {
        cout << endl << "TEST traducir ShootPinToolDTO a datos: ";
        auto p_dto = new ShootPinToolDTO(-10, 50);
        int vec_size = ProtocolTranslator::translate(p_dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_SHOOT_PIN_TOOL, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t ) -10, output.at(SHOOT_PT_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 50, output.at(SHOOT_PT_Y_POS));
        CPPUNIT_ASSERT_EQUAL(3, vec_size);
        delete p_dto;
        cout << "OK";
    }

    void testTranslateShootPinToolData() {
        cout << endl << "TEST traducir datos ShootPinTool a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_SHOOT_PIN_TOOL);
        v.push_back(-10);    // x
        v.push_back(5);    // y
        auto dto = (ShootPinToolDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_SHOOT_PIN_TOOL, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t)-10, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t)5, dto->getY());
        cout << "OK";
    }

    void testTranslateLiftRockDTO() {
        cout << endl << "TEST traducir LiftRockDTO a datos: ";
        auto dto = new LiftRockDTO(2);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_LIFT_ROCK, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t)2, output.at(LIFT_ROCK_ID_POS));
        CPPUNIT_ASSERT_EQUAL(2, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateLiftRockData() {
        cout << endl << "TEST traducir datos LiftRock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_LIFT_ROCK);
        v.push_back(2);    // y
        auto dto = (LiftRockDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_LIFT_ROCK, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getRockId());
        cout << "OK";
    }

    void testTranslateDropRockDTO() {
        cout << endl << "TEST traducir DropRockDTO a datos: ";
        auto dto = new DropRockDTO();
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_DROP_ROCK, output.at(PROTOCOL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(1, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateDropRockData() {
        cout << endl << "TEST traducir datos DropRock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_DROP_ROCK);
        auto dto = ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_DROP_ROCK, dto->getClassId());
        delete dto;
        cout << "OK";
    }

    void testTranslatePlayerChellIdDTO() {
        cout << endl << "TEST traducir PlayerChellIdDTO a datos: ";
        auto dto = new PlayerChellIdDTO(2);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PLAYER_CHELL_ID, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, output.at(PLAYER_CHELL_ID_POS));
        CPPUNIT_ASSERT_EQUAL(2, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslatePlayerChellIdData() {
        cout << endl << "TEST traducir datos PlayerChellId a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_PLAYER_CHELL_ID);
        v.push_back(1);
        auto dto = (PlayerChellIdDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PLAYER_CHELL_ID, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 1, dto->getChellId());
        delete dto;        
        cout << "OK";
    }

    void testTranslateRockBlockDTO() {
        cout << endl << "TEST traducir RockBlockDTO a datos: ";
        auto dto = new RockBlockDTO(-2, 0, 10, 20);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_BLOCK_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ROCK_BLOCK_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ROCK_BLOCK_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, output.at(ROCK_BLOCK_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 20, output.at(ROCK_BLOCK_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(5, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateRockBlockData() {
        cout << endl << "TEST traducir datos RockBlock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ROCK_BLOCK_DATA);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto dto = (RockBlockDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_BLOCK_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        delete dto;
        cout << "OK";
    }

    void testTranslateMetalBlockDTO() {
        cout << endl << "TEST traducir MetalBlockDTO a datos: ";
        auto dto = new MetalBlockDTO(-2, 0, 10, 20);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_BLOCK_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(METAL_BLOCK_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(METAL_BLOCK_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, output.at(METAL_BLOCK_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 20, output.at(METAL_BLOCK_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(5, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateMetalBlockData() {
        cout << endl << "TEST traducir datos MetalBlock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_METAL_BLOCK_DATA);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto dto = (MetalBlockDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_BLOCK_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        delete dto;
        cout << "OK";
    }

    void testTranslateMetalDiagonalBlockDTO() {
        cout << endl << "TEST traducir MetalDiagonalBlockDTO a datos: ";
        auto dto = new MetalDiagonalBlockDTO(-2, 0, 4, O_NO);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_DIAGONAL_BLOCK_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(METAL_DIAG_BLOCK_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(METAL_DIAG_BLOCK_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(METAL_DIAG_BLOCK_SIDE_LEN_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) O_NO, output.at(METAL_DIAG_BLOCK_ORIENT_POS));
        CPPUNIT_ASSERT_EQUAL(5, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateMetalDiagonalBlockData() {
        cout << endl << "TEST traducir datos MetalDiagonalBlock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_METAL_DIAGONAL_BLOCK_DATA);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(O_NE);
        auto dto = (MetalDiagonalBlockDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_DIAGONAL_BLOCK_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL((int16_t) O_NE, dto->getOrientation());
        delete dto;
        cout << "OK";
    }

    void testTranslateEnergyTransmitterDTO() {
        cout << endl << "TEST traducir EnergyTransmitterDTO a datos: ";
        auto dto = new EnergyTransmitterDTO(0, -2, 0, 4, O_E);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_TRANSMITTER_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ENRG_TRANSM_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ENRG_TRANSM_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ENRG_TRANSM_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(ENRG_TRANSM_SIDE_LEN_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) O_E, output.at(ENRG_TRANSM_DIRECTION_POS));
        CPPUNIT_ASSERT_EQUAL(6, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateEnergyTransmitterData() {
        cout << endl << "TEST traducir datos EnergyTransmitter a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ENERGY_TRANSMITTER_DATA);
        v.push_back(2);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(O_NE);
        auto dto = (EnergyTransmitterDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_TRANSMITTER_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL((int16_t) O_NE, dto->getDirection());
        delete dto;
        cout << "OK";
    }

    void testTranslateEnergyReceiverDTO() {
        cout << endl << "TEST traducir EnergyReceiverDTO a datos: ";
        auto dto = new EnergyReceiverDTO(0, -2, 0, 4);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_RECEIVER_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ENRG_RECVR_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ENRG_RECVR_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ENRG_RECVR_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, output.at(ENRG_RECVR_SIDE_LEN_POS));
        CPPUNIT_ASSERT_EQUAL(5, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateEnergyReceiverData() {
        cout << endl << "TEST traducir datos EnergyReceiver a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ENERGY_RECEIVER_DATA);
        v.push_back(2);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        auto dto = (EnergyReceiverDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_RECEIVER_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getSideLength());
        delete dto;
        cout << "OK";
    }

    void testTranslateAcidDTO() {
        cout << endl << "TEST traducir AcidDTO a datos: ";
        auto dto = new AcidDTO(-2, 0, 2, 3);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ACID_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ACID_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ACID_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, output.at(ACID_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 3, output.at(ACID_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(5, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateAcidData() {
        cout << endl << "TEST traducir datos Acid a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ACID_DATA);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto dto = (AcidDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ACID_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        delete dto;
        cout << "OK";
    }

    void testTranslateButtonDTO() {
        cout << endl << "TEST traducir ButtonDTO a datos: ";
        auto dto = new ButtonDTO(0, -2, 0, 2, 3);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_BUTTON_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(BUTTON_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(BUTTON_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(BUTTON_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, output.at(BUTTON_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 3, output.at(BUTTON_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(6, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateButtonData() {
        cout << endl << "TEST traducir datos Button a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_BUTTON_DATA);
        v.push_back(4);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto dto = (ButtonDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_BUTTON_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        delete dto;
        cout << "OK";
    }

    void testTranslateGateDTO() {
        cout << endl << "TEST traducir GateDTO a datos: ";
        auto dto = new GateDTO(0, -2, 0, 2, 3);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_GATE_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(GATE_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(GATE_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(GATE_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, output.at(GATE_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 3, output.at(GATE_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(6, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateGateData() {
        cout << endl << "TEST traducir datos Gate a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_GATE_DATA);
        v.push_back(4);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto dto = (GateDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_GATE_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        delete dto;
        cout << "OK";
    }
    
    void testTranslateEnergyBarrierDTO() {
        cout << endl << "TEST traducir EnergyBarrierDTO a datos: ";
        auto dto = new EnergyBarrierDTO(-2, 0, 10, 20);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_BARRIER_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ENRG_BARRIER_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ENRG_BARRIER_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, output.at(ENRG_BARRIER_WIDTH_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 20, output.at(ENRG_BARRIER_HEIGHT_POS));
        CPPUNIT_ASSERT_EQUAL(5, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateEnergyBarrierData() {
        cout << endl << "TEST traducir datos EnergyBarrier a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ENERGY_BARRIER_DATA);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(2);
        auto dto = (EnergyBarrierDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_BARRIER_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) 2, dto->getHeight());
        delete dto;
        cout << "OK";
    }
    
    void testTranslateRockDTO() {
        cout << endl << "TEST traducir RockDTO a datos: ";
        auto dto = new RockDTO(10, -2, 0, 10, DELETE);
        int vec_size = ProtocolTranslator::translate(dto, output);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_DATA, output[PROTOCOL_ID_POS]);
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, output.at(ROCK_ID_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) -2, output.at(ROCK_X_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, output.at(ROCK_Y_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, output.at(ROCK_SIDE_LEN_POS));
        CPPUNIT_ASSERT_EQUAL((int16_t) DELETE, output.at(ROCK_DELETE_STATE_POS));
        CPPUNIT_ASSERT_EQUAL(6, vec_size);
        delete dto;
        cout << "OK";
    }

    void testTranslateRockData() {
        cout << endl << "TEST traducir datos Rock a DTO: ";
        vector<int16_t> v;
        v.push_back(PROTOCOL_ROCK_DATA);
        v.push_back(8);
        v.push_back(5);
        v.push_back(10);
        v.push_back(4);
        v.push_back(DONT_DELETE);
        auto dto = (RockDTO*) ProtocolTranslator::translate(v);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 8, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) 5, dto->getX());
        CPPUNIT_ASSERT_EQUAL((int16_t) 10, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 4, dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL(DONT_DELETE, dto->getDeleteState());
        delete dto;
        cout << "OK";
    }

};
    
#endif //PORTAL_TESTPROTOCOLTRANSLATOR_H
