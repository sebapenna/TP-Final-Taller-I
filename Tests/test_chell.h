#ifndef PORTAL_TEST_CHELL_H
#define PORTAL_TEST_CHELL_H

#include <cppunit/extensions/HelperMacros.h>
#include "../Box2D/Box2D.h"
#include "../src/stage.h"
#include "../src/constants.h"

using std::cout;
using std::endl;

class TestChell : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( TestChell );
        CPPUNIT_TEST( testCreateChell );
        CPPUNIT_TEST( testTeletransport );
        CPPUNIT_TEST( testFall );
        CPPUNIT_TEST( testMoveRight );
        CPPUNIT_TEST( testMoveLeft );
        CPPUNIT_TEST( testJump );
    CPPUNIT_TEST_SUITE_END();

private:
    Stage *stage;
    Chell *chell;
    size_t width = 100;
    size_t height = 200;
    float chell_ground_x = 0;
    float chell_ground_y = 2;

public:
    void setUp() {
        stage = new Stage(width, height);
        stage->createChell(chell_ground_x, chell_ground_y, 0);
        chell = stage->getChell(0);
    }

    void tearDown() {
        delete stage;
    }

    void testCreateChell() {
        cout << "TEST crear chell correctamente: ";
        CPPUNIT_ASSERT_EQUAL(chell->getId(), (uint) 0);
        CPPUNIT_ASSERT_EQUAL(chell->getX(), chell_ground_x);
        CPPUNIT_ASSERT_EQUAL(chell->getY(), chell_ground_y);
        cout << "OK" << endl;
    }

    void testTeletransport() {
        cout << "TEST teletransportar chell: ";
        chell->teletransport(5,5);
        CPPUNIT_ASSERT_EQUAL(chell->getX(), (float) 5);
        CPPUNIT_ASSERT_EQUAL(chell->getY(), (float) 5);
        cout << "OK" << endl;
    }

    void testFall() {
        cout << "TEST chell cae con gravedad: ";
        chell->teletransport(0, 4); // Elevo a chell para que caiga
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            stage->step();
            cout << "x: " << chell->getX() << " y: " << chell->getY() << endl;
        }
        float y_diff = chell->getY() - chell_ground_y;
        float x_diff = chell->getX() - chell_ground_x;
        CPPUNIT_ASSERT_LESSEQUAL((float) 0.02, x_diff);
        CPPUNIT_ASSERT_LESSEQUAL((float) 0.02, y_diff);
        cout << "OK" << endl;
    }

    void testMoveRight() {
        cout << "TEST mover chell hacia derecha: ";
        chell->move_right();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            stage->step();
            cout << "x: " << chell->getX() << " y: " << chell->getY() << endl;
        }
        //todo: test
    }

    void testMoveLeft() {
        cout << "TEST mover chell hacia izquierda: ";
        chell->move_left();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            stage->step();
            cout << "x: " << chell->getX() << " y: " << chell->getY() << endl;
        }
        //todo: test
    }

    void testJump() {
        cout << "TEST hacer saltar a chell: ";
        chell->jump();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            stage->step();
            cout << "x: " << chell->getX() << " y: " << chell->getY() << endl;
        }
        //todo: test
    }

    // todo: teste de la exception

    // todo: test saltar a otra superficie

    // todo: test saltar y mover



};

#endif //PORTAL_TEST_CHELL_H
