#ifndef TP_FINAL_TEST_1_H
#define TP_FINAL_TEST_1_H

#include <cppunit/extensions/HelperMacros.h>
#include "../Box2D/Box2D.h"
//#include "../GroundBlocks/bloque_metal.h"
//#include "../Obstacles/boton.h"

class TestRockBlock : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( TestRockBlock );
        CPPUNIT_TEST( testFixedWidthAndHeight );

    CPPUNIT_TEST_SUITE_END();
private:
    b2World *world;
public:
    void setUp() {
        b2Vec2 gravity(0.0f, -10.0f);
        world = new b2World(gravity);
        b2BodyDef b;
        b.position.Set(0.0f, -10.0f);
        b.type = b2_staticBody;
    }

    void tearDown() {
        delete world;
    }

    void testFixedWidthAndHeight() {
//        std::cout << "Test OK" << std::endl;
//        CPPUNIT_ASSERT(  e->getFive() == (e->getFour() + 1) );
    }


};

#endif //TP_FINAL_TEST_1_H
