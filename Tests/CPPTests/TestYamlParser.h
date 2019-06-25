#ifndef PORTAL_TESTYAMLPARSER_H
#define PORTAL_TESTYAMLPARSER_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/CollidableData/YamlParser.h"
#include "Server/Model/constants.h"
#include <string>

using std::cout;
using std::endl;
using std::make_shared;

class TestYamlParser : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( TestYamlParser );
        CPPUNIT_TEST( testParseWorld );
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
#ifdef DEBUG_MODE
        parser = new YamlParser("Config/test.yaml");
#else
        parser = new YamlParser("/etc/Portal/Serever/Config/test.yaml");
#endif
    }

    void tearDown() {
        delete parser;
    }

    void testParseWorld() {
        cout << endl << endl << "TESTS YAML PARSER";
        cout << endl << "TEST datos world: ";
        WorldData stage_data = parser->loadWorldData();
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
        std::vector<std::shared_ptr<CollidableData>> data_vector;
        parser->loadRockBlocksData(data_vector);
        auto data = (RockBlockData*) data_vector[0].get();
        CPPUNIT_ASSERT_EQUAL(_width, data->getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data->getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 0, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) -1, data->getY());

        data = (RockBlockData*) data_vector[1].get();
        CPPUNIT_ASSERT_EQUAL(_width, data->getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data->getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 0, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 61, data->getY());

        data = (RockBlockData*) data_vector[2].get();
        CPPUNIT_ASSERT_EQUAL(_length, data->getWidth());
        CPPUNIT_ASSERT_EQUAL(_height, data->getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 101, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 0, data->getY());

        data = (RockBlockData*) data_vector[3].get();
        CPPUNIT_ASSERT_EQUAL(_length, data->getWidth());
        CPPUNIT_ASSERT_EQUAL(_height, data->getHeight());
        CPPUNIT_ASSERT_EQUAL((float) -1, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 0, data->getY());
        cout << "OK";
    }

    void testParseMetalBlocks() {
        cout << endl << "TEST datos bloques metal: ";
        std::vector<std::shared_ptr<CollidableData>> data_vector;
        parser->loadMetalBlocksData(data_vector);
        auto data = (MetalBlockData*) data_vector[0].get();
        CPPUNIT_ASSERT_EQUAL(_length, data->getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data->getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 5, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());

        data = (MetalBlockData*) data_vector[1].get();
        CPPUNIT_ASSERT_EQUAL(_length, data->getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data->getHeight());
        CPPUNIT_ASSERT_EQUAL((float) -5, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        cout << "OK";
    }

    void testParseMetalDiagonalBlocks() {
        cout << endl << "TEST datos bloques metal diagonal: ";
        std::vector<std::shared_ptr<CollidableData>> data_vector;
        parser->loadMetalDiagonalBlockData(data_vector);
        
        auto data = (MetalDiagonalBlockData*) data_vector[0].get();
        CPPUNIT_ASSERT_EQUAL(_length, data->getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data->getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 10, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        CPPUNIT_ASSERT_EQUAL(O_NE, data->getOrientation());

        data = (MetalDiagonalBlockData*) data_vector[1].get();
        CPPUNIT_ASSERT_EQUAL(_length, data->getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data->getHeight());
        CPPUNIT_ASSERT_EQUAL((float) -10, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        CPPUNIT_ASSERT_EQUAL(O_NO, data->getOrientation());

        data = (MetalDiagonalBlockData*) data_vector[2].get();
        CPPUNIT_ASSERT_EQUAL(_length, data->getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data->getHeight());
        CPPUNIT_ASSERT_EQUAL((float) 20, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        CPPUNIT_ASSERT_EQUAL(O_SE, data->getOrientation());

        data = (MetalDiagonalBlockData*) data_vector[3].get();
        CPPUNIT_ASSERT_EQUAL(_length, data->getWidth());
        CPPUNIT_ASSERT_EQUAL(_length, data->getHeight());
        CPPUNIT_ASSERT_EQUAL((float) -20, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        CPPUNIT_ASSERT_EQUAL(O_SO, data->getOrientation());
        cout << "OK";
    }

    void testParseRock() {
        cout << endl << "TEST datos rocas: ";
        std::vector<std::shared_ptr<CollidableData>> data_vector;
        parser->loadRockData(data_vector);
        auto data = (RockData*) data_vector[0].get();
        CPPUNIT_ASSERT_EQUAL((float) 30, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());

        data = (RockData*) data_vector[1].get();
        CPPUNIT_ASSERT_EQUAL((float) -30, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        cout << "OK";
    }

    void testParseAcid() {
        cout << endl << "TEST datos acido: ";
        std::vector<std::shared_ptr<CollidableData>> data_vector;
        parser->loadAcidData(data_vector);
        auto data = (AcidData*) data_vector[0].get();
        CPPUNIT_ASSERT_EQUAL((float) 40, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());

        data = (AcidData*) data_vector[1].get();
        CPPUNIT_ASSERT_EQUAL((float) -40, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        cout << "OK";
    }

    void testParseButton() {
        cout << endl << "TEST datos botones: ";
        std::vector<std::shared_ptr<CollidableData>> data_vector;
        parser->loadButtonData(data_vector);
        auto data = (ButtonData*) data_vector[0].get();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, data->getId());
        CPPUNIT_ASSERT_EQUAL((float) 50, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());

        data = (ButtonData*) data_vector[1].get();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, data->getId());
        CPPUNIT_ASSERT_EQUAL((float) -50, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        cout << "OK";
    }

    void testParseGate() {
        cout << endl << "TEST datos compuertas: ";
        std::vector<std::shared_ptr<CollidableData>> data_vector;
        parser->loadGateData(data_vector);
        auto data = (GateData*) data_vector[0].get();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, data->getId());
        CPPUNIT_ASSERT_EQUAL((float) 60, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        auto buttons_needed = data->getButtonsNeeded();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, buttons_needed[0]);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, buttons_needed[1]);
        CPPUNIT_ASSERT_EQUAL((size_t) 2, buttons_needed.size());
        auto e_receiver_needed = data->getEnergyReceiversNeeded();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, e_receiver_needed[0]);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, e_receiver_needed.size());

        data = (GateData*) data_vector[1].get();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, data->getId());
        CPPUNIT_ASSERT_EQUAL((float) -60, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        buttons_needed = data->getButtonsNeeded();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, buttons_needed[0]);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, buttons_needed.size());
        e_receiver_needed = data->getEnergyReceiversNeeded();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, e_receiver_needed[0]);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, e_receiver_needed[1]);
        CPPUNIT_ASSERT_EQUAL((size_t) 2, e_receiver_needed.size());
        cout << "OK";
    }

    void testParseEnergyTransmitter() {
        cout << endl << "TEST datos transmisor energia: ";
        std::vector<std::shared_ptr<CollidableData>> data_vector;
        parser->loadEnergyTransmitterData(data_vector);
        auto data = (EnergyTransmitterData*) data_vector[0].get();
        CPPUNIT_ASSERT_EQUAL((float) 70, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        CPPUNIT_ASSERT_EQUAL(O_N, data->getDirection());

        data = (EnergyTransmitterData*) data_vector[1].get();
        CPPUNIT_ASSERT_EQUAL((float) -70, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        CPPUNIT_ASSERT_EQUAL(O_S, data->getDirection());

        data = (EnergyTransmitterData*) data_vector[2].get();
        CPPUNIT_ASSERT_EQUAL((float) 0, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        CPPUNIT_ASSERT_EQUAL(O_E, data->getDirection());

        data = (EnergyTransmitterData*) data_vector[3].get();
        CPPUNIT_ASSERT_EQUAL((float) 0, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        CPPUNIT_ASSERT_EQUAL(O_O, data->getDirection());
        cout << "OK";
    }

    void testParseEnergyReceiver() {
        cout << endl << "TEST datos receptor energia: ";
        std::vector<std::shared_ptr<CollidableData>> data_vector;
        parser->loadEnergyReceiverData(data_vector);
        auto data = (EnergyReceiverData*) data_vector[0].get();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, data->getId());
        CPPUNIT_ASSERT_EQUAL((float) 80, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());

        data = (EnergyReceiverData*) data_vector[1].get();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, data->getId());
        CPPUNIT_ASSERT_EQUAL((float) -80, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        cout << "OK";
    }

    void testParseEnergyBarrier() {
        cout << endl << "TEST datos barrera energia: ";
        std::vector<std::shared_ptr<CollidableData>> data_vector;
        parser->loadEnergyBarrierData(data_vector);
        auto data = (EnergyBarrierData*) data_vector[0].get();
        CPPUNIT_ASSERT_EQUAL((float) 90, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        CPPUNIT_ASSERT_EQUAL(O_V, data->getOrientation());

        data = (EnergyBarrierData*) data_vector[1].get();
        CPPUNIT_ASSERT_EQUAL((float) -90, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        CPPUNIT_ASSERT_EQUAL(O_H, data->getOrientation());
        cout << "OK";
    }

    void testParseChell() {
        cout << endl << "TEST datos chell: ";
        auto data_vector = parser->loadChellData();
        auto data = (ChellData*) data_vector[0].get();
        CPPUNIT_ASSERT_EQUAL((size_t) 0, data->getId());
        CPPUNIT_ASSERT_EQUAL((float) 0, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());

        data = (ChellData*) data_vector[1].get();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, data->getId());
        CPPUNIT_ASSERT_EQUAL((float) 10, data->getX());
        CPPUNIT_ASSERT_EQUAL((float) 1, data->getY());
        cout << "OK";
    }
};

#endif //PORTAL_TESTYAMLPARSER_H
