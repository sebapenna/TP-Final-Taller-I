#ifndef PORTAL_TESTYAMLPARSER_H
#define PORTAL_TESTYAMLPARSER_H

#include <cppunit/extensions/HelperMacros.h>
#include "../src/YamlData/YamlParser.h"
#include "../src/constants.h"
#include <string>

using std::cout;
using std::endl;

class TestYamlParser : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( TestYamlParser );
        CPPUNIT_TEST( testParseStage );
        CPPUNIT_TEST( testParseBoxLength );
        CPPUNIT_TEST( testParseRockBlocks );
        CPPUNIT_TEST( testParseMetalBlocks );
        CPPUNIT_TEST( testParseMetalDiagonalBlocks );
        CPPUNIT_TEST( testParseRock );
        CPPUNIT_TEST( testParseAcid );
        CPPUNIT_TEST( testParseButton );
        CPPUNIT_TEST( testParseGate );
        CPPUNIT_TEST( testParseEnergyTransmitter );
        CPPUNIT_TEST( testParseEnergyReceiver );
        CPPUNIT_TEST( testParseEnergyBarrier );
        CPPUNIT_TEST( testParseChell );
    CPPUNIT_TEST_SUITE_END();

private:
    YamlParser *parser;
    float _width = 100;
    float _height = 60;
    float _length = 2;

public:
    void setUp() {
        std::string filename(YAML_TEST_PATH);
        filename.append("test.yaml");
        parser = new YamlParser(filename);
    }

    void tearDown() {
        delete parser;
    }

    void testParseStage() {
        cout << endl << endl << "TESTS YAML PARSER";
        cout << endl << "TEST datos stage: ";
        StageData stage_data = parser->loadStage();
        CPPUNIT_ASSERT_EQUAL((size_t) _width, stage_data.getWidth());
        CPPUNIT_ASSERT_EQUAL((size_t) _height, stage_data.getHeight());
        cout << "OK";
    }

    void testParseBoxLength() {
        cout << endl << "TEST dato tamaño box: ";
        auto box__length = parser->loadBoxSize();
        CPPUNIT_ASSERT_EQUAL((size_t) 2, box__length);
        cout << "OK";
    }

    void testParseRockBlocks() {
        cout << endl << "TEST datos bloques roca: ";
        auto data_vector = parser->loadRockBlocksData();
        CPPUNIT_ASSERT_EQUAL(_width, data_vector[0].getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data_vector[0].getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 0, data_vector[0].getX());
        CPPUNIT_ASSERT_EQUAL((float) -1, data_vector[0].getY());

        CPPUNIT_ASSERT_EQUAL(_width, data_vector[1].getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data_vector[1].getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 0, data_vector[1].getX());
        CPPUNIT_ASSERT_EQUAL((float) 61, data_vector[1].getY());

        CPPUNIT_ASSERT_EQUAL(_length, data_vector[2].getWidth());
        CPPUNIT_ASSERT_EQUAL(_height, data_vector[2].getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 101, data_vector[2].getX());
        CPPUNIT_ASSERT_EQUAL((float) 0, data_vector[2].getY());

        CPPUNIT_ASSERT_EQUAL(_length, data_vector[3].getWidth());
        CPPUNIT_ASSERT_EQUAL(_height, data_vector[3].getHeight());
        CPPUNIT_ASSERT_EQUAL((float) -1, data_vector[3].getX());
        CPPUNIT_ASSERT_EQUAL((float) 0, data_vector[3].getY());
        cout << "OK";
    }

    void testParseMetalBlocks() {
        cout << endl << "TEST datos bloques metal: ";
        auto data_vector = parser->loadMetalBlocksData();
        CPPUNIT_ASSERT_EQUAL(_length, data_vector[0].getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data_vector[0].getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 5, data_vector[0].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[0].getY());

        CPPUNIT_ASSERT_EQUAL(_length, data_vector[1].getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data_vector[1].getHeight());
        CPPUNIT_ASSERT_EQUAL((float) -5, data_vector[1].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[1].getY());
        cout << "OK";
    }

    void testParseMetalDiagonalBlocks() {
        cout << endl << "TEST datos bloques metal diagonal: ";
        auto data_vector = parser->loadMetalDiagonalBlockData();
        CPPUNIT_ASSERT_EQUAL(_length, data_vector[0].getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data_vector[0].getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 10, data_vector[0].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[0].getY());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[0].getY());
        CPPUNIT_ASSERT_EQUAL(O_NE, data_vector[0].getOrientation());

        CPPUNIT_ASSERT_EQUAL(_length, data_vector[1].getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data_vector[1].getHeight());
        CPPUNIT_ASSERT_EQUAL((float) -10, data_vector[1].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[1].getY());
        CPPUNIT_ASSERT_EQUAL(O_NO, data_vector[1].getOrientation());

        CPPUNIT_ASSERT_EQUAL(_length, data_vector[2].getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data_vector[2].getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 20, data_vector[2].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[2].getY());
        CPPUNIT_ASSERT_EQUAL(O_SE, data_vector[2].getOrientation());

        CPPUNIT_ASSERT_EQUAL(_length, data_vector[3].getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data_vector[3].getHeight());
        CPPUNIT_ASSERT_EQUAL((float) -20, data_vector[3].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[3].getY());
        CPPUNIT_ASSERT_EQUAL(O_SO, data_vector[3].getOrientation());
        cout << "OK";
    }

    void testParseRock() {
        cout << endl << "TEST datos rocas: ";
        auto data_vector = parser->loadRockData();
        CPPUNIT_ASSERT_EQUAL((float) 30, data_vector[0].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[0].getY());

        CPPUNIT_ASSERT_EQUAL((float) -30, data_vector[1].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[1].getY());
        cout << "OK";
    }

    void testParseAcid() {
        cout << endl << "TEST datos acido: ";
        auto data_vector = parser->loadAcidData();
        CPPUNIT_ASSERT_EQUAL((float) 40, data_vector[0].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[0].getY());

        CPPUNIT_ASSERT_EQUAL((float) -40, data_vector[1].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[1].getY());
        cout << "OK";
    }

    void testParseButton() {
        cout << endl << "TEST datos botones: ";
        auto data_vector = parser->loadButtonData();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, data_vector[0].getId());
        CPPUNIT_ASSERT_EQUAL((float) 50, data_vector[0].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[0].getY());

        CPPUNIT_ASSERT_EQUAL((size_t) 1, data_vector[1].getId());
        CPPUNIT_ASSERT_EQUAL((float) -50, data_vector[1].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[1].getY());
        cout << "OK";
    }

    void testParseGate() {
        cout << endl << "TEST datos compuertas: ";
        auto data_vector = parser->loadGateData();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, data_vector[0].getId());
        CPPUNIT_ASSERT_EQUAL((float) 60, data_vector[0].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[0].getY());
        auto buttons_needed = data_vector[0].getButtonsNeeded();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, buttons_needed[0]);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, buttons_needed[1]);
        CPPUNIT_ASSERT_EQUAL((size_t) 2, buttons_needed.size());
        auto e_receiver_needed = data_vector[0].getEnergyReceiversNeeded();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, e_receiver_needed[0]);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, e_receiver_needed.size());

        CPPUNIT_ASSERT_EQUAL((size_t) 1, data_vector[1].getId());
        CPPUNIT_ASSERT_EQUAL((float) -60, data_vector[1].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[1].getY());
        buttons_needed = data_vector[1].getButtonsNeeded();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, buttons_needed[0]);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, buttons_needed.size());
        e_receiver_needed = data_vector[1].getEnergyReceiversNeeded();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, e_receiver_needed[0]);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, e_receiver_needed[1]);
        CPPUNIT_ASSERT_EQUAL((size_t) 2, e_receiver_needed.size());
        cout << "OK";
    }

    void testParseEnergyTransmitter() {
        cout << endl << "TEST datos transmisor energia: ";
        auto data_vector = parser->loadEnergyTransmitterData();
        CPPUNIT_ASSERT_EQUAL((float) 70, data_vector[0].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[0].getY());

        CPPUNIT_ASSERT_EQUAL((float) -70, data_vector[1].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[1].getY());
        cout << "OK";
    }

    void testParseEnergyReceiver() {
        cout << endl << "TEST datos receptor energia: ";
        auto data_vector = parser->loadEnergyReceiverData();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, data_vector[0].getId());
        CPPUNIT_ASSERT_EQUAL((float) 80, data_vector[0].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[0].getY());

        CPPUNIT_ASSERT_EQUAL((size_t) 1, data_vector[1].getId());
        CPPUNIT_ASSERT_EQUAL((float) -80, data_vector[1].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[1].getY());
        cout << "OK";
    }

    void testParseEnergyBarrier() {
        cout << endl << "TEST datos barrera energia: ";
        auto data_vector = parser->loadEnergyBarrierData();
        CPPUNIT_ASSERT_EQUAL((float) 90, data_vector[0].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[0].getY());
        CPPUNIT_ASSERT_EQUAL(O_V, data_vector[0].getOrientation());

        CPPUNIT_ASSERT_EQUAL((float) -90, data_vector[1].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[1].getY());
        CPPUNIT_ASSERT_EQUAL(O_H, data_vector[1].getOrientation());
        cout << "OK";
    }

    void testParseChell() {
        cout << endl << "TEST datos chell: ";
        auto data_vector = parser->loadChellData();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, data_vector[0].getId());
        CPPUNIT_ASSERT_EQUAL((float) 0, data_vector[0].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[0].getY());

        CPPUNIT_ASSERT_EQUAL((size_t) 1, data_vector[1].getId());
        CPPUNIT_ASSERT_EQUAL((float) 10, data_vector[1].getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data_vector[1].getY());
        cout << "OK";
    }
};

#endif //PORTAL_TESTYAMLPARSER_H
