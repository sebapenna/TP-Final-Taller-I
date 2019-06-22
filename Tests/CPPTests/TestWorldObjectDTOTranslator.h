#ifndef PORTAL_TESTWORLDOBJECTDTOTRANSLATOR_H
#define PORTAL_TESTWORLDOBJECTDTOTRANSLATOR_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/constants.h"
#include <string>
#include <Server/PositionTranslator.h>
#include <Server/Model/World.h>
#include <memory>
#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include <Server/WorldObjectDTOTranslator.h>
#include <Common/ProtocolTranslator/DataDTO/RockBlockDTO.h>

using std::cout;
using std::endl;
using std::make_shared;


class TestWorldObjectDTOTranslator : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestWorldObjectDTOTranslator);
        CPPUNIT_TEST(testTranslateRockBlock);
        CPPUNIT_TEST(testTranslateMetalBlock);
        CPPUNIT_TEST(testTranslateMetalDiagonalBlock);
        CPPUNIT_TEST(testTranslateEnergyTransmitter);
        CPPUNIT_TEST(testTranslateEnergyReceiver);
        CPPUNIT_TEST(testTranslateAcid);
        CPPUNIT_TEST(testTranslateButton);
        CPPUNIT_TEST(testTranslateGate);
        CPPUNIT_TEST(testTranslateEnergyBarrier);
        CPPUNIT_TEST(testTranslateRock);
        CPPUNIT_TEST(testTranslateChell);
        CPPUNIT_TEST(testTranslateEnergyBall);
        CPPUNIT_TEST(testTranslateEnergyTransmitterActivate);
        CPPUNIT_TEST(testTranslateEnergyReceiverActivate);
        CPPUNIT_TEST(testTranlateButtonChangeState);
        CPPUNIT_TEST(testTranslateGateChangeState);
        CPPUNIT_TEST(testTranslateChellDeleteDTO);
        CPPUNIT_TEST(testTranslateEnergyBallDeleteDTO);
        CPPUNIT_TEST(testTranslateRockDeleteDTO);
        CPPUNIT_TEST(testTranslatePortalDeleteDTO);
        CPPUNIT_TEST(testTranslatePinTOolDeleteDTO);
    CPPUNIT_TEST_SUITE_END();

private:
    std::shared_ptr<Configuration> ptrcon;
    Configuration *config;
    World *world;
    size_t width = 100;
    size_t height = 200;

public:
    void setUp() {
        ptrcon = make_shared<Configuration>();
        config = ptrcon.get();
        world = new World(width, height, ptrcon);
    }

    void tearDown() {
        delete world;
    }

    void testTranslateRockBlock() {
        cout << endl << endl << "TEST WORLD OBJECT DTO TRANSLATOR";
        cout << endl << "TEST crear DTO rock block: ";
        int16_t w1 = 100, h1 = 4, x1 = 0, y1 = -2;
        int16_t w2 = 30, h2 = 10, x2 = 20, y2 = 20;
        auto new_pos = PositionTranslator::translate(ROCK_BLOCK, x1, y1, w1/2, h1/2);
        auto data1 = make_shared<RockBlockData>(w1, h1, x1, y1);
        world->createCollidable(data1);
        auto data2 = make_shared<RockBlockData>(w2, h2, x2, y2);
        world->createCollidable(data2);
        auto iter = world->getRockBlocks().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        auto dto = (RockBlockDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL(w1, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL(h1, dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_BLOCK_DATA, dto->getClassId());

        new_pos = PositionTranslator::translate(ROCK_BLOCK, x2, y2, w2/2, h2/2);
        iter = world->getRockBlocks().at(1);
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        dto = (RockBlockDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL(w2, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL(h2, dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_BLOCK_DATA, dto->getClassId());
        cout << "OK";
    }

    void testTranslateMetalBlock() {
        cout << endl << "TEST crear DTO metal block: ";
        int16_t w1 = 100, h1 = 4, x1 = 0, y1 = -2;
        int16_t w2 = 30, h2 = 10, x2 = 20, y2 = 20;
        auto new_pos = PositionTranslator::translate(METAL_BLOCK, x1, y1, w1/2, h1/2);

        auto data1 = make_shared<MetalBlockData>(w1, h1, x1, y1);
        world->createCollidable(data1);
        auto data2 = make_shared<MetalBlockData>(w2, h2, x2, y2);
        world->createCollidable(data2);

        auto iter = world->getMetalBlocks().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        auto dto = (MetalBlockDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL(w1, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL(h1, dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_BLOCK_DATA, dto->getClassId());

        new_pos = PositionTranslator::translate(METAL_BLOCK, x2, y2, w2/2, h2/2);
        iter = world->getMetalBlocks().at(1);
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        dto = (MetalBlockDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL(w2, dto->getWidth());
        CPPUNIT_ASSERT_EQUAL(h2, dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_BLOCK_DATA, dto->getClassId());
        cout << "OK";
    }

    void testTranslateMetalDiagonalBlock() {
        cout << endl << "TEST crear DTO metal diagonal block: ";
        int16_t side1 = 100, x1 = 0, y1 = -2;
        int16_t side2 = 30, x2 = 20, y2 = 20;
        auto data1 = make_shared<MetalDiagonalBlockData>(side1, side1, x1, y1, "NE");
        world->createCollidable(data1);
        auto data2 = make_shared<MetalDiagonalBlockData>(side2, side2, x2, y2, "NO");
        world->createCollidable(data2);
        auto iter = world->getMetalDiagonalBlocks().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        auto dto = (MetalDiagonalBlockDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(x1, dto->getX());
        CPPUNIT_ASSERT_EQUAL(y1, dto->getY());
        CPPUNIT_ASSERT_EQUAL(NORTH_EAST, dto->getOrientation());
        CPPUNIT_ASSERT_EQUAL(side1, dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_DIAGONAL_BLOCK_DATA, dto->getClassId());

        iter = world->getMetalDiagonalBlocks().at(1);
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        dto = (MetalDiagonalBlockDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(x2, dto->getX());
        CPPUNIT_ASSERT_EQUAL(y2, dto->getY());
        CPPUNIT_ASSERT_EQUAL(side2, dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL(NORTH_WEST, dto->getOrientation());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_METAL_DIAGONAL_BLOCK_DATA, dto->getClassId());
        cout << "OK";
    }

    void testTranslateEnergyTransmitter() {
        cout << endl << "TEST crear DTO energy transmitter: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;
        auto new_pos = PositionTranslator::translate(ENERGY_TRANSMITTER, x1, y1, ENRG_BLOCK_HALF_LEN);

        auto data1 = make_shared<EnergyTransmitterData>(x1, y1, "E");
        world->createCollidable(data1);
        auto data2 = make_shared<EnergyTransmitterData>(x2, y2, "O");
        world->createCollidable(data2);

        auto iter = world->getEnergyTransmitters().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        auto dto = (EnergyTransmitterDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL(EAST, dto->getDirection());
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) (ENRG_BLOCK_HALF_LEN * 2), dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_TRANSMITTER_DATA, dto->getClassId());

        new_pos = PositionTranslator::translate(ENERGY_TRANSMITTER, x2, y2, ENRG_BLOCK_HALF_LEN);
        iter = world->getEnergyTransmitters().at(1);
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        dto = (EnergyTransmitterDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) (ENRG_BLOCK_HALF_LEN * 2), dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL((int16_t) 1, dto->getId());
        CPPUNIT_ASSERT_EQUAL(WEST, dto->getDirection());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_TRANSMITTER_DATA, dto->getClassId());
        cout << "OK";
    }

    void testTranslateEnergyReceiver() {
        cout << endl << "TEST crear DTO energy receiver: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;
        auto new_pos = PositionTranslator::translate(ENERGY_RECEIVER, x1, y1, ENRG_BLOCK_HALF_LEN);


        auto data1 = make_shared<EnergyReceiverData>(0, x1, y1);
        world->createCollidable(data1);
        auto data2 = make_shared<EnergyReceiverData>(1, x2, y2);
        world->createCollidable(data2);

        auto iter = world->getEnergyReceivers().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        auto dto = (EnergyReceiverDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) (ENRG_BLOCK_HALF_LEN * 2), dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_RECEIVER_DATA, dto->getClassId());

        new_pos = PositionTranslator::translate(ENERGY_RECEIVER, x2, y2, ENRG_BLOCK_HALF_LEN);
        iter = world->getEnergyReceivers().at(1);
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        dto = (EnergyReceiverDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) (ENRG_BLOCK_HALF_LEN * 2), dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL((int16_t) 1, dto->getId());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_RECEIVER_DATA, dto->getClassId());
        cout << "OK";
    }

    void testTranslateAcid() {
        cout << endl << "TEST crear DTO acid: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;
        int w = 4;
        auto new_pos = PositionTranslator::translate(ACID, x1, y1, w / 2,
                config->getAcidHalfHeight());


        auto data1 = make_shared<AcidData>(x1, y1, w);
        world->createCollidable(data1);
        auto data2 = make_shared<AcidData>(x2, y2, w);
        world->createCollidable(data2);

        auto iter = world->getAcids().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        auto dto = (AcidDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * ACID_HALF_WIDTH), dto->getWidth());
        // Redondeo porque altura acido podria ser menor a 1
        CPPUNIT_ASSERT_EQUAL((int16_t) round(2 * ACID_HALF_HEIGHT), dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ACID_DATA, dto->getClassId());

        new_pos = PositionTranslator::translate(ACID, x2, y2, w / 2, config->getAcidHalfHeight());
        iter = world->getAcids().at(1);
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        dto = (AcidDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * ACID_HALF_WIDTH), dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) round(2 * ACID_HALF_HEIGHT), dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ACID_DATA, dto->getClassId());
        cout << "OK";
    }

    void testTranslateButton() {
        cout << endl << "TEST crear DTO button: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;
        auto new_pos = PositionTranslator::translate(BUTTON, x1, y1, BUTTON_HALF_WIDTH, BUTTON_HALF_HEIGHT);

        auto data1 = make_shared<ButtonData>(0, x1, y1);
        world->createCollidable(data1);
        auto data2 = make_shared<ButtonData>(1, x2, y2);
        world->createCollidable(data2);

        auto iter = world->getButtons().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        auto dto = (ButtonDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * BUTTON_HALF_WIDTH), dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) round(2 * BUTTON_HALF_HEIGHT), dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_BUTTON_DATA, dto->getClassId());

        new_pos = PositionTranslator::translate(BUTTON, x2, y2, BUTTON_HALF_WIDTH, BUTTON_HALF_HEIGHT);
        iter = world->getButtons().at(1);
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        dto = (ButtonDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 1, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * BUTTON_HALF_WIDTH), dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) round(2 * BUTTON_HALF_HEIGHT), dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_BUTTON_DATA, dto->getClassId());
        cout << "OK";
    }

    void testTranslateGate() {
        cout << endl << "TEST crear DTO gate: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;
        auto new_pos = PositionTranslator::translate(GATE, x1, y1, GATE_HALF_WIDTH, GATE_HALF_HEIGHT);

        auto data1 = make_shared<GateData>(0, x1, y1);
        world->createCollidable(data1);
        auto data2 = make_shared<GateData>(1, x2, y2);
        world->createCollidable(data2);

        auto iter = world->getGates().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        auto dto = (GateDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * GATE_HALF_WIDTH), dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * GATE_HALF_HEIGHT), dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_GATE_DATA, dto->getClassId());

        new_pos = PositionTranslator::translate(GATE, x2, y2, GATE_HALF_WIDTH, GATE_HALF_HEIGHT);
        iter = world->getGates().at(1);
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        dto = (GateDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * GATE_HALF_WIDTH), dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * GATE_HALF_HEIGHT), dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_GATE_DATA, dto->getClassId());
        cout << "OK";
    }

    void testTranslateEnergyBarrier() {
        cout << endl << "TEST crear DTO acid: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;
        auto new_pos = PositionTranslator::translate(ENERGY_BARRIER, x1, y1, BARRIER_HALF_WIDTH,
                BARRIER_HALF_LENGTH);

        auto data1 = make_shared<EnergyBarrierData>(x1, y1, "V");
        world->createCollidable(data1);
        auto data2 = make_shared<EnergyBarrierData>(x2, y2, "H");
        world->createCollidable(data2);
        auto iter = world->getEnergyBarriers().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        auto dto = (EnergyBarrierDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * BARRIER_HALF_WIDTH), dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * BARRIER_HALF_LENGTH), dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_BARRIER_DATA, dto->getClassId());

        new_pos = PositionTranslator::translate(ENERGY_BARRIER, x2, y2, BARRIER_HALF_LENGTH, BARRIER_HALF_WIDTH);
        iter = world->getEnergyBarriers().at(1);
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        dto = (EnergyBarrierDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * BARRIER_HALF_LENGTH), dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * BARRIER_HALF_WIDTH), dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_BARRIER_DATA, dto->getClassId());
        cout << "OK";
    }

    void testTranslateRock() {
        cout << endl << "TEST crear DTO rock: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;
        auto new_pos = PositionTranslator::translate(ROCK, x1, y1, ROCK_HALF_LEN);

        auto data1 = make_shared<RockData>(x1, y1);
        world->createCollidable(data1);
        auto data2 = make_shared<RockData>(x2, y2);
        world->createCollidable(data2);
        
        auto iter = world->getRocks().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        auto dto = (RockDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) DONT_DELETE, dto->getDeleteState());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * ROCK_HALF_LEN), dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_DATA, dto->getClassId());

        new_pos = PositionTranslator::translate(ROCK, x2, y2, ROCK_HALF_LEN);
        iter = world->getRocks().at(1);
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        dto = (RockDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 1, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) DONT_DELETE, dto->getDeleteState());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * ROCK_HALF_LEN), dto->getSideLength());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_DATA, dto->getClassId());
        cout << "OK";
    }

    void testTranslateChell() {
        cout << endl << "TEST crear DTO chell: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;
        auto new_pos = PositionTranslator::translate(CHELL, x1, y1, CHELL_HALF_WIDTH, CHELL_HALF_HEIGHT);

        auto data1 = make_shared<ChellData>(0, x1, y1);
        world->createCollidable(data1);
        auto data2 = make_shared<ChellData>(0, x2, y2);
        world->createCollidable(data2);
        
        auto iter = world->getChells().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        auto dto = (ChellDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL(DONT_DELETE, dto->getDeleteState());
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * CHELL_HALF_WIDTH), dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * CHELL_HALF_HEIGHT), dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_CHELL_DATA, dto->getClassId());

        new_pos = PositionTranslator::translate(CHELL, x2, y2, CHELL_HALF_WIDTH, CHELL_HALF_HEIGHT);
        iter = world->getChells().at(1);
        ptr = WorldObjectDTOTranslator::translate(iter, true);
        dto = (ChellDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL((int16_t) 1, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * CHELL_HALF_WIDTH), dto->getWidth());
        CPPUNIT_ASSERT_EQUAL((int16_t) (2 * CHELL_HALF_HEIGHT), dto->getHeight());
        CPPUNIT_ASSERT_EQUAL(DONT_DELETE, dto->getDeleteState());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_CHELL_DATA, dto->getClassId());
        cout << "OK";
    }

    void testTranslateEnergyBall() {
        cout << endl << "TEST crear DTO energy ball: ";
        int16_t x1 = 0, y1 = -2;

        auto data1 = make_shared<EnergyTransmitterData>(x1, y1, "E");
        world->createCollidable(data1);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < config->getFps(); ++i)
                world->step();
        for (int i = 0; i < config->getFps(); ++i)
            world->step(); // Step donde se crea EnergyBall
        auto energy_ball = world->getEnergyBall(0);

        auto new_pos = PositionTranslator::translate(ENERGY_BALL, energy_ball->x(),
                energy_ball->y(), ENRG_BALL_RADIUS);


        auto iter = world->getEnergyBall(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter);
        auto dto = (EnergyBallDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL(new_pos.first, dto->getX());
        CPPUNIT_ASSERT_EQUAL(new_pos.second, dto->getY());
        CPPUNIT_ASSERT_EQUAL(DONT_DELETE, dto->getDeleteState());
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL((int16_t) ENRG_BALL_RADIUS, dto->getRadius());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_BALL_DATA, dto->getClassId());

        cout << "OK";
    }

    void testTranslateEnergyTransmitterActivate() {
        cout << endl << "TEST crear DTO energy transmitter activate: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;

        auto data1 = make_shared<EnergyTransmitterData>(x1, y1, "E");
        world->createCollidable(data1);
        auto data2 = make_shared<EnergyTransmitterData>(x2, y2, "O");
        world->createCollidable(data2);
        auto iter = world->getEnergyTransmitters().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        // En caso real solo se utilizara este DTO cuando se active el transmisor
        ptr = WorldObjectDTOTranslator::translate(iter);
        auto dto = (EnergyTransmitterActivateDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL((int16_t ) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_TRANSMITTER_ACTIVATE, dto->getClassId());

        cout << "OK";
    }

    void testTranslateEnergyReceiverActivate() {
        cout << endl << "TEST crear DTO energy receiver activate: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;

        auto data1 = make_shared<EnergyReceiverData>(0, x1, y1);
        world->createCollidable(data1);
        auto data2 = make_shared<EnergyReceiverData>(1, x2, y2);
        world->createCollidable(data2);
        auto iter = world->getEnergyReceivers().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        // En caso real solo se utilizara este DTO cuando se active el receptor
        ptr = WorldObjectDTOTranslator::translate(iter);
        auto dto = (EnergyReceiverActivateDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL((int16_t ) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_RECEIVER_ACTIVATE, dto->getClassId());

        cout << "OK";
    }

    void testTranlateButtonChangeState() {
        cout << endl << "TEST crear DTO boton cambio estado: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;

        auto data1 = make_shared<ButtonData>(0, x1, y1);
        world->createCollidable(data1);
        auto data2 = make_shared<ButtonData>(0, x2, y2);
        world->createCollidable(data2);

        auto iter = world->getButtons().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter);
        auto dto = (ButtonStateDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL((int16_t ) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL(NOT_PRESSED, dto->getState());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_BUTTON_CHANGE_STATE, dto->getClassId());


        iter = world->getButtons().at(1);
        iter->activate();   // activo boton
        iter->updateState();    // Fuerzo que se setee el estado para testear
        ptr = WorldObjectDTOTranslator::translate(iter);
        dto = (ButtonStateDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL((int16_t) 1, dto->getId());
        CPPUNIT_ASSERT_EQUAL(PRESSED, dto->getState());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_BUTTON_CHANGE_STATE, dto->getClassId());

        cout << "OK";
    }

    void testTranslateGateChangeState() {
        cout << endl << "TEST crear DTO compuerta cambio de estado: ";
        int16_t x1 = 0, y1 = -2;
        int16_t x2 = 20, y2 = 20;

        auto data1 = make_shared<ButtonData>(0, x1, y1);
        world->createCollidable(data1);
        auto data2 = make_shared<GateData>(0, x2, y2);
        data2->addButtonNeeded(0);
        world->createCollidable(data2);
        auto button = world->getButton(0);


        auto iter = world->getGates().at(0);
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(iter);
        auto dto = (GateStateDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL((int16_t ) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL(CLOSED, dto->getState());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_GATE_CHANGE_STATE, dto->getClassId());

        button->activate();
        button->updateState();  // Activo para abrir compuerta

        iter = world->getGates().at(0);
        iter->updateState(); // Abro compuerta

        ptr = WorldObjectDTOTranslator::translate(iter);
        dto = (GateStateDTO*) ptr.get();
        CPPUNIT_ASSERT_EQUAL((int16_t ) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL(OPEN, dto->getState());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_GATE_CHANGE_STATE, dto->getClassId());

        cout << "OK";
    }
    
    void testTranslateChellDeleteDTO() {
        cout << endl << "TEST crear DTO delete chell: ";
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(0, CHELL);
        auto dto = (ChellDTO*) ptr.get();
        
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_CHELL_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL(DELETE, dto->getDeleteState());
        cout << "OK";
    }
    
    void testTranslateEnergyBallDeleteDTO() {
        cout << endl << "TEST crear DTO delete energy ball: ";
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(0, ENERGY_BALL);
        auto dto = (EnergyBallDTO*) ptr.get();
        
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ENERGY_BALL_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL(DELETE, dto->getDeleteState());
        cout << "OK";
    }
    
    void testTranslateRockDeleteDTO() {
        cout << endl << "TEST crear DTO delete rock: ";
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(0, ROCK);
        auto dto = (RockDTO*) ptr.get();
        
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_ROCK_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL(DELETE, dto->getDeleteState());
        cout << "OK";
    }
    
    void testTranslatePortalDeleteDTO() {
        cout << endl << "TEST crear DTO delete portal: ";
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(0, PORTAL);
        auto dto = (PortalDTO*) ptr.get();
        
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PORTAL_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL(DELETE, dto->getDeleteState());
        cout << "OK";
    }
    
    void testTranslatePinTOolDeleteDTO() {
        cout << endl << "TEST crear DTO delete pin tool: ";
        std::shared_ptr<ProtocolDTO> ptr;
        ptr = WorldObjectDTOTranslator::translate(0, PIN_TOOL);
        auto dto = (PinToolDTO*) ptr.get();
        
        CPPUNIT_ASSERT_EQUAL((int16_t) 0, dto->getId());
        CPPUNIT_ASSERT_EQUAL(PROTOCOL_PIN_TOOL_DATA, dto->getClassId());
        CPPUNIT_ASSERT_EQUAL(DELETE, dto->getDeleteState());
        cout << "OK";
    }

};

// todo: test portal comun y ¿delete?
// todo: test pin tool comun y delete

#endif //PORTAL_TESTWORLDOBJECTDTOTRANSLATOR_H
