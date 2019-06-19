#ifndef PORTAL_TESTPORTAL_H
#define PORTAL_TESTPORTAL_H


#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <Common/exceptions.h>
#include <string>

using std::cout;
using std::endl;

class TestPortal : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( TestPortal );
        CPPUNIT_TEST( testCreate );
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    Chell *chell;
    size_t width = 100;
    size_t height = 200;
    float chell_x = 0;
    float chell_y = 2;

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(1000, 4, 0, -2);  // Piso
        world->createChell(chell_x, chell_y);
        chell = world->getChell(0);
    }

    void tearDown() {
        delete world;
    }

    void testCreate() {
        cout << endl << endl << "TEST PORTAL";
        cout << endl << "TEST crear: ";
        world->createMetalDiagonalBlock(4, 4, 20, 0, O_NE);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        cout << "OK";
    }

};


#endif //PORTAL_TESTPORTAL_H
