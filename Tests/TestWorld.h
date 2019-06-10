#ifndef PORTAL_TESTWORLD_H
#define PORTAL_TESTWORLD_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"

using std::cout;
using std::endl;

class TestWorld : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( TestWorld );
        CPPUNIT_TEST( testFixedWidthAndHeight );
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    size_t width = 20;
    size_t height = 30;

public:
    void setUp() {
        world = new World(width, height);
    }

    void tearDown() {
        delete world;
    }

    void testFixedWidthAndHeight() {
        cout << endl << endl << "TEST WORLD";
        cout << endl << "TEST ancho y alto de escenario fijo: ";
        world->step();
        CPPUNIT_ASSERT_EQUAL(world->getHeight(), height);
        CPPUNIT_ASSERT_EQUAL(world->getWidth(), width);
        cout << "OK";
    }

    // todo: TEST DETECTEDUPDATES VECTOR
};

#endif //PORTAL_TESTWORLD_H
