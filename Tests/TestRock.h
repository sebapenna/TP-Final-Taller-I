#ifndef PORTAL_TESTROCK_H
#define PORTAL_TESTROCK_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/World.h"
#include "../Server/constants.h"
#include <Common/exceptions.h>

using std::cout;
using std::endl;

class TestRock : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestRock);
        CPPUNIT_TEST( testCreate );
        CPPUNIT_TEST( testFallsWithGravity );
        CPPUNIT_TEST( testRemainsStillOnGround );
        CPPUNIT_TEST( testContactWithBarrier );
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    Rock *rock1;
    Rock *rock2;
    size_t width = 100;
    size_t height = 200;
    float rock1_x = 0, rock1_y = 2, rock2_x = 6, rock2_y = 4;
    int init_n_bodies;

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(100, 4, 0, -2); // Piso
        world->createRock(rock1_x, rock1_y);
        world->createRock(rock2_x, rock2_y);
        init_n_bodies = 3;  // Cantidad de bodies que creo al inicio
        rock1 = world->getRock(0);
        rock2 = world->getRock(1);
    }

    void tearDown() {
        delete world;
    }

    void testCreate() {
        cout << endl << endl << "TEST ROCK";
        cout << endl << "TEST crear correctamente: ";
        CPPUNIT_ASSERT_EQUAL(init_n_bodies, world->getWorld()->GetBodyCount());
        CPPUNIT_ASSERT_EQUAL(rock1_x, rock1->getPositionX());
        CPPUNIT_ASSERT_EQUAL(rock1_y, rock1->getPositionY());
        CPPUNIT_ASSERT_EQUAL(rock2_x, rock2->getPositionX());
        CPPUNIT_ASSERT_EQUAL(rock2_y, rock2->getPositionY());
        cout << "OK";
    }

    void testFallsWithGravity() {
        cout << endl << "TEST cae con gravedad: ";
        for (int i = 0; i < 200; i++)
            world->step();
        float y_diff = rock2->getPositionY() - ROCK_HALF_LEN;
        float x_diff = rock2->getPositionX() - rock2_x;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, x_diff);
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, y_diff);
        cout << "OK";
    }

    void testRemainsStillOnGround() {
        cout << endl << "TEST queda quieta sobre una superficie: ";
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        float y_diff = rock1->getPositionY() - rock1_y;
        float x_diff = rock1->getPositionX() - rock1_x;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, x_diff);
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, y_diff);
        cout << "OK";
    }

    void testContactWithBarrier() {
        cout << endl << "TEST eliminar ante contacto con barrera energia: ";
        float barrier_x = 10, barrier_y = BARRIER_HALF_LENGTH;
        world->createEnergyBarrier(barrier_x, barrier_y, O_V);
        auto n_bodies = world->getWorld()->GetBodyCount();
        rock1->teletransport(barrier_x, barrier_y);
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT_EQUAL(n_bodies - 1, world->getWorld()->GetBodyCount());
        CPPUNIT_ASSERT_EQUAL((Rock*)nullptr, world->getRock(0));
        cout << "OK";
    }
};
#endif //PORTAL_TESTROCK_H
