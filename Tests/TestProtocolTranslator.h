#ifndef PORTAL_TESTPROTOCOLTRANSLATOR_H
#define PORTAL_TESTPROTOCOLTRANSLATOR_H

#include <cppunit/extensions/HelperMacros.h>
#include <src/ProtocolTranslator/ProtocolTranslator.h>
#include "../src/constants.h"
#include <string>
#include <src/ProtocolTranslator/MoveLeftDTO.h>
#include <src/ProtocolTranslator/MoveRightDTO.h>
#include <src/ProtocolTranslator/JumpDTO.h>
#include <src/ProtocolTranslator/StopDTO.h>
#include <src/ProtocolTranslator/PortalDTO.h>
#include <src/ProtocolTranslator/PinToolDTO.h>
#include <src/ProtocolTranslator/LiftRockDTO.h>
#include <src/ProtocolTranslator/DropRockDTO.h>

using std::cout;
using std::endl;
using std::vector;

class TestProtocolTranslator : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( TestProtocolTranslator );
    CPPUNIT_TEST(testTranslateMoveLeftDTO);
    CPPUNIT_TEST(testTranslateMoveRightDTO);
    CPPUNIT_TEST(testTranslateJumpDTO);
    CPPUNIT_TEST(testTranslateStopDTO);
    CPPUNIT_TEST(testTranslatePortalDTO);
    CPPUNIT_TEST(testTranslatePinToolDTO);
    CPPUNIT_TEST(testTranslateLiftRockDTO);
    CPPUNIT_TEST(testTranslateDropRockDTO);
    CPPUNIT_TEST_SUITE_END();

public:
    void testTranslateMoveLeftDTO() {
        cout << endl << endl << "TEST PROTOCOL TRANSLATOR";
        cout << endl << "TEST traducir MoveLeftDTO a datos: ";
        auto ml_dto = new MoveLeftDTO();
        auto msg_vec = ProtocolTranslator::translate(ml_dto);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_MOVE_LEFT, msg_vec.at(0));
        delete ml_dto;
        cout << "OK";
    }
    
    void testTranslateMoveRightDTO() {
        cout << endl << "TEST traducir MoveRightDTO a datos: ";
        auto mr_dto = new MoveRightDTO();
        auto msg_vec = ProtocolTranslator::translate(mr_dto);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_MOVE_RIGHT, msg_vec.at(0));
        delete mr_dto;
        cout << "OK";
    }
    
    void testTranslateJumpDTO() {
        cout << endl << "TEST traducir JumpDTO a datos: ";
        auto *j_dto = new JumpDTO();
        auto msg_vec = ProtocolTranslator::translate(j_dto);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_JUMP, msg_vec.at(0));
        delete j_dto;
        cout << "OK";
    }
    
    void testTranslateStopDTO() {
        cout << endl << "TEST traducir StopDTO a datos: ";
        auto s_dto = new StopDTO();
        auto msg_vec = ProtocolTranslator::translate(s_dto);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_STOP, msg_vec.at(0));
        delete s_dto;
        cout << "OK";
    }

    void testTranslatePortalDTO() {
        cout << endl << "TEST traducir PortalDTO a datos: ";
        auto p_dto = new PortalDTO(BLUE_PORTAL, -10, 50);
        auto msg_vec = ProtocolTranslator::translate(p_dto);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PORTAL, msg_vec.at(0));
        CPPUNIT_ASSERT_EQUAL(BLUE_PORTAL, msg_vec.at(1));
        CPPUNIT_ASSERT_EQUAL(-10, msg_vec.at(2));
        CPPUNIT_ASSERT_EQUAL(50, msg_vec.at(3));
        delete p_dto;
        cout << "OK";
    }

    void testTranslatePinToolDTO() {
        cout << endl << "TEST traducir PinToolDTO a datos: ";
        auto p_dto = new PinToolDTO(-10, 50);
        auto msg_vec = ProtocolTranslator::translate(p_dto);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PIN_TOOL, msg_vec.at(0));
        CPPUNIT_ASSERT_EQUAL(-10, msg_vec.at(1));
        CPPUNIT_ASSERT_EQUAL(50, msg_vec.at(2));
        delete p_dto;
        cout << "OK";
    }

    void testTranslateLiftRockDTO() {
        cout << endl << "TEST traducir LiftRockDTO a datos: ";
        auto dto = new LiftRockDTO(2);
        auto msg_vec = ProtocolTranslator::translate(dto);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_LIFT_ROCK, msg_vec.at(0));
        CPPUNIT_ASSERT_EQUAL(2, msg_vec.at(1));
        delete dto;
        cout << "OK";
    }

    void testTranslateDropRockDTO() {
        cout << endl << "TEST traducir DropRockDTO a datos: ";
        auto dto = new DropRockDTO();
        auto msg_vec = ProtocolTranslator::translate(dto);
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_DROP_ROCK, msg_vec.at(0));
        delete dto;
        cout << "OK";
    }
};
    
#endif //PORTAL_TESTPROTOCOLTRANSLATOR_H
