#ifndef PORTAL_TESTENERGYBALL_H
#define PORTAL_TESTENERGYBALL_H

#include <cppunit/extensions/HelperMacros.h>
#include "src/World.h"
#include "src/constants.h"

using std::cout;
using std::endl;

class TestEnergyBall : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestEnergyBall);
        CPPUNIT_TEST(testCreateNorth);
        CPPUNIT_TEST(testCreateSouth);
        CPPUNIT_TEST(testCreateEast);
        CPPUNIT_TEST(testCreateWest);
        CPPUNIT_TEST(testCreateMoreThanOne);
        CPPUNIT_TEST(testMovesNorth);
        CPPUNIT_TEST(testMovesSouth);
        CPPUNIT_TEST(testMovesEast);
        CPPUNIT_TEST(testMovesWest);
        CPPUNIT_TEST(testMovesNorthWithFixedSpeed);
        CPPUNIT_TEST(testMovesSouthWithFixedSpeed);
        CPPUNIT_TEST(testMovesEastWithFixedSpeed);
        CPPUNIT_TEST(testMovesWestWithFixedSpeed);
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    size_t width = 100, height = 200;
    float e_transm_x = 0, e_transm_y = 2;

public:
    void setUp() {
        world = new World(width, height);
//        world->createRockBlock(100, 4, 0, -2); // Piso
    }

    void tearDown() {
        delete world;
    }

    void testCreateNorth() {
        cout << endl << endl << "TEST ENERGY BALL";
        cout << endl << "TEST crear correctamente en direccion Norte: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_N);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, vec.size());
        auto energy_ball = vec[0];
        CPPUNIT_ASSERT_EQUAL(e_transm_x, energy_ball->getPositionX());
        float new_y = e_transm_y + ENRG_TRANSM_HEIGHT + ENRG_BALL_RADIUS;
        CPPUNIT_ASSERT_EQUAL(new_y, energy_ball->getPositionY());
        cout << "OK";
    }

    void testCreateSouth() {
        cout << endl << "TEST crear correctamente en direccion Sur: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, vec.size());
        auto energy_ball = vec[0];
        CPPUNIT_ASSERT_EQUAL(e_transm_x, energy_ball->getPositionX());
        float new_y = e_transm_y - ENRG_TRANSM_HEIGHT - ENRG_BALL_RADIUS;
        CPPUNIT_ASSERT_EQUAL(new_y, energy_ball->getPositionY());
        cout << "OK";
    }

    void testCreateEast() {
        cout << endl << "TEST crear correctamente en direccion Este: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, vec.size());
        auto energy_ball = vec[0];
        CPPUNIT_ASSERT_EQUAL(e_transm_y, energy_ball->getPositionY());
        float new_x = e_transm_x + ENRG_TRANSM_WIDTH + ENRG_BALL_RADIUS;
        CPPUNIT_ASSERT_EQUAL(new_x, energy_ball->getPositionX());
        cout << "OK";
    }

    void testCreateWest() {
        cout << endl << "TEST crear correctamente en direccion Oeste: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_O);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, vec.size());
        auto energy_ball = vec[0];
        CPPUNIT_ASSERT_EQUAL(e_transm_y, energy_ball->getPositionY());
        float new_x = e_transm_x - ENRG_TRANSM_WIDTH - ENRG_BALL_RADIUS;
        CPPUNIT_ASSERT_EQUAL(new_x, energy_ball->getPositionX());
        cout << "OK";
    }

    void testCreateMoreThanOne() {
        cout << endl << "TEST crear mas de una bola de energia: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_O);
        for (int k = 0; k < 2; ++k) {
            for (int j = 1; j < TIME_TO_RELEASE; ++j)
                for (int i = 0; i < STEP_ITERATIONS; ++i) {
                    world->step();
                    auto vec = world->getEnergyBalls();
                }
            for (int i = 0; i < STEP_ITERATIONS; ++i)
                world->step(); // Step donde se crea EnergyBall
        }
        auto vec = world->getEnergyBalls();
        CPPUNIT_ASSERT_EQUAL((size_t) 2, vec.size());
        cout << "OK";
    }

    void testMovesNorth() {
        cout << endl << "TEST moverse en direccion Norte: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_N);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        auto energy_ball = vec[0];
        float previous_pos_y = energy_ball->getPositionY();
        float previous_pos_x = energy_ball->getPositionX();
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step();
        CPPUNIT_ASSERT_GREATER(previous_pos_y, energy_ball->getPositionY());
        CPPUNIT_ASSERT_EQUAL(previous_pos_x, energy_ball->getPositionX());
        cout << "OK";
    }

    void testMovesSouth() {
        cout << endl << "TEST moverse en direccion Sur: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        auto energy_ball = vec[0];
        float previous_pos_y = energy_ball->getPositionY();
        float previous_pos_x = energy_ball->getPositionX();
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step();
        CPPUNIT_ASSERT_LESS(previous_pos_y, energy_ball->getPositionY());
        CPPUNIT_ASSERT_EQUAL(previous_pos_x, energy_ball->getPositionX());
        cout << "OK";
    }

    void testMovesEast() {
        cout << endl << "TEST moverse en direccion Este: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        auto energy_ball = vec[0];
        float previous_pos_x = energy_ball->getPositionX();
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step();
        float diff_y = energy_ball->getPositionY() - e_transm_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        CPPUNIT_ASSERT_GREATER(previous_pos_x, energy_ball->getPositionX());
        cout << "OK";
    }

    void testMovesWest() {
        cout << endl << "TEST moverse en direccion Oeste: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_O);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        auto energy_ball = vec[0];
        float previous_pos_x = energy_ball->getPositionX();
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step();
        float diff_y = energy_ball->getPositionY() - e_transm_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        CPPUNIT_ASSERT_LESS(previous_pos_x, energy_ball->getPositionX());
        cout << "OK";
    }

    void testMovesNorthWithFixedSpeed() {
        cout << endl << "TEST moverse en direccion Norte con velocidad cte.: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_N);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        auto energy_ball = vec[0];
        float y_step = 0;
        float init_y = energy_ball->getPositionY();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if (y_step == 0)
                y_step = energy_ball->getPositionY() - init_y;
            float diff_y = abs(y_step * i) - abs(energy_ball->getPositionY());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        }
        cout << "OK";
    }

    void testMovesSouthWithFixedSpeed() {
        cout << endl << "TEST moverse en direccion Sur con velocidad cte.: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        auto energy_ball = vec[0];
        float y_step = 0;
        float init_y = energy_ball->getPositionY();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if (y_step == 0)
                y_step = energy_ball->getPositionY() - init_y;
            float diff_y = abs(y_step * i) - abs(energy_ball->getPositionY());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        }
        cout << "OK";
    }

    void testMovesEastWithFixedSpeed() {
        cout << endl << "TEST moverse en direccion Este con velocidad cte.: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        auto energy_ball = vec[0];
        float x_step = 0;
        float init_x = energy_ball->getPositionX();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if (x_step == 0)
                x_step = energy_ball->getPositionX() - init_x;
            float diff_x = abs(x_step * i) - abs(energy_ball->getPositionX());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
        }
        cout << "OK";
    }

    void testMovesWestWithFixedSpeed() {
        cout << endl << "TEST moverse en direccion Oeste con velocidad cte.: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
        auto vec = world->getEnergyBalls();
        auto energy_ball = vec[0];
        float x_step = 0;
        float init_x = energy_ball->getPositionX();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if (x_step == 0)
                x_step = energy_ball->getPositionX() - init_x;
            float diff_x = abs(x_step * i) - abs(energy_ball->getPositionX());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
        }
        cout << "OK";
    }



};
#endif //PORTAL_TESTENERGYBALL_H
