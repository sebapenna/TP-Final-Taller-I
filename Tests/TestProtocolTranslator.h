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
        cout << endl << "TEST traducir PlayerChellId a datos: ";
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
        delete dto;        cout << "OK";
    }
};
    
#endif //PORTAL_TESTPROTOCOLTRANSLATOR_H
