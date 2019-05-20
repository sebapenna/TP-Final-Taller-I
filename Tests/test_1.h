#ifndef TP_FINAL_TEST_1_H
#define TP_FINAL_TEST_1_H

#include <cppunit/extensions/HelperMacros.h>
#include "../Ejemplo/ejemplo.h"
#include "../Box2D/Box2D.h"
//#include "../GroundBlocks/bloque_metal.h"
//#include "../Obstacles/boton.h"

class FirstTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( FirstTest );
        CPPUNIT_TEST( testEqual );
        CPPUNIT_TEST( testDifferent );
        CPPUNIT_TEST( testEjemplo );
        CPPUNIT_TEST( testBox );
    CPPUNIT_TEST_SUITE_END();
private:
    Ejemplo *e;

public:
    void setUp() {
        e = new Ejemplo();
    }

    void tearDown() {
        delete e;
    }

    void testEqual() {
        std::cout << "Test OK" << std::endl;
        CPPUNIT_ASSERT(  e->getFive() == (e->getFour() + 1) );
    }

    void testDifferent() {
        CPPUNIT_ASSERT( e->getFour() != e->getThree() );
    }

    void testEjemplo( ) {
        CPPUNIT_ASSERT(e->exists());
    }

    void testBox() {
        b2Vec2 gravity(0.0f, -10.0f);
        b2World world(gravity);

        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, -10.0f);
        b2Body *groundBody = world.CreateBody(&groundBodyDef);
        b2PolygonShape groundBox;
        groundBox.SetAsBox(50.0f, 10.0f);
        groundBody->CreateFixture(&groundBox, 0.0f);

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(0.0f, 4.0f);
        b2Body* body = world.CreateBody(&bodyDef);
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(1.0f, 1.0f);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        body->CreateFixture(&fixtureDef);

        float32 timeStep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;

        for (int32 i = 0; i < 60; ++i)
        {
            world.Step(timeStep, velocityIterations, positionIterations);
            b2Vec2 position = body->GetPosition();
            float32 angle = body->GetAngle();
            printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        }
    }
};

#endif //TP_FINAL_TEST_1_H
