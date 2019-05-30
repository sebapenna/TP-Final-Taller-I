#ifndef PORTAL_TESTROCK_H
#define PORTAL_TESTROCK_H

#include <cppunit/extensions/HelperMacros.h>
#include "src/World.h"
#include "../src/constants.h"
#include "../src/exceptions.h"

using std::cout;
using std::endl;

class TestRock : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestRock);
        CPPUNIT_TEST( testCreate );
        CPPUNIT_TEST( testFallsWithGravity );
        CPPUNIT_TEST( testRemainsStillOnGround );
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    Rock *rock1;
    Rock *rock2;
    size_t width = 100;
    size_t height = 200;
    float rock1_x = 0, rock1_y = 2, rock2_x = 6, rock2_y = 4;

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(100, 4, 0, -2); // Piso
        world->createRock(rock1_x, rock1_y);
        world->createRock(rock2_x, rock2_y);
        auto rock_vector = world->getRocks();
        rock1 = rock_vector[0];
        rock2 = rock_vector[1];
    }

    void tearDown() {
        delete world;
    }

    void testCreate() {
        cout << endl << endl << "TEST ROCK";
        cout << endl << "TEST crear correctamente: ";
        auto rock_vector = world->getRocks();
        CPPUNIT_ASSERT_EQUAL((size_t) 2, rock_vector.size());
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
        float y_diff = rock2->getPositionY() - ROCK_HEIGHT;
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



};
#endif //PORTAL_TESTROCK_H
