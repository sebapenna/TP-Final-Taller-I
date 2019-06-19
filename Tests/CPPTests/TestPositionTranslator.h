#ifndef PORTAL_TESTPOSITIONTRANSLATOR_H
#define PORTAL_TESTPOSITIONTRANSLATOR_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/constants.h"
#include <string>
#include <Server/PositionTranslator.h>

using std::cout;
using std::endl;


class TestPositionTranslator : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestPositionTranslator);
    CPPUNIT_TEST(testTranslateCommonPosition);
    CPPUNIT_TEST(testTranslateEnergyBallPosition);
    CPPUNIT_TEST(testTranslateMetalDiagonalBlockPosition);
    CPPUNIT_TEST_SUITE_END();

private:
    float x = 10, y = 15, half_width = 2, half_height = 5;
    int16_t new_x = 8, new_y = 10;


public:
    void testTranslateCommonPosition() {
        cout << endl << endl << "TEST POSITION TRANSLATOR";

        cout << endl << "TEST traducir posicion de objeto comun: ";
        auto new_pos = PositionTranslator::translate(ENERGY_RECEIVER, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        new_pos = PositionTranslator::translate(ENERGY_TRANSMITTER, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        new_pos = PositionTranslator::translate(METAL_BLOCK, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        new_pos = PositionTranslator::translate(ROCK_BLOCK, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        new_pos = PositionTranslator::translate(BUTTON, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        new_pos = PositionTranslator::translate(GATE, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        new_pos = PositionTranslator::translate(ROCK, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        new_pos = PositionTranslator::translate(ACID, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        new_pos = PositionTranslator::translate(ENERGY_BARRIER, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        new_pos = PositionTranslator::translate(CHELL, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        new_pos = PositionTranslator::translate(PORTAL, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        new_pos = PositionTranslator::translate(PIN_TOOL, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL(new_x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL(new_y, new_pos.second);

        cout << "OK";
    }

    void testTranslateEnergyBallPosition() {
        cout << endl << "TEST traducir posicion de bola de energia: ";
        auto new_pos = PositionTranslator::translate(ENERGY_BALL, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL((int16_t) x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL((int16_t) y, new_pos.second);
        cout << "OK";
    }

    void testTranslateMetalDiagonalBlockPosition() {
        cout << endl << "TEST traducir posicion de bloque metal diagonal: ";
        auto new_pos = PositionTranslator::translate(METAL_DIAGONAL_BLOCK, x, y, half_width, half_height);
        CPPUNIT_ASSERT_EQUAL((int16_t) x, new_pos.first);
        CPPUNIT_ASSERT_EQUAL((int16_t) y, new_pos.second);
        cout << "OK";
    }
};


#endif //PORTAL_TESTPOSITIONTRANSLATOR_H
