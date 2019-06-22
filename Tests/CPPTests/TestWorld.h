#ifndef PORTAL_TESTWORLD_H
#define PORTAL_TESTWORLD_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"

using std::cout;
using std::endl;
using std::make_shared;

class TestWorld : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( TestWorld );
        CPPUNIT_TEST( testFixedWidthAndHeight );
    CPPUNIT_TEST_SUITE_END();

private:
    std::shared_ptr<Configuration> ptr;
    Configuration *config;
    World *world;
    size_t width = 20;
    size_t height = 30;

public:
    void setUp() {
        ptr = make_shared<Configuration>();
    config = ptr.get();
        world = new World(width, height, ptr);
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
};

#endif //PORTAL_TESTWORLD_H
