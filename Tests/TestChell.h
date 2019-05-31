#ifndef PORTAL_TESTCHELL_H
#define PORTAL_TESTCHELL_H

#include <cppunit/extensions/HelperMacros.h>
#include "src/World.h"
#include "../src/constants.h"
#include "../src/exceptions.h"

using std::cout;
using std::endl;

class TestChell : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( TestChell );
        CPPUNIT_TEST( testCreateChell );
        CPPUNIT_TEST( testTeletransport );
        CPPUNIT_TEST( testFall );
        CPPUNIT_TEST( testMoveRight );
        CPPUNIT_TEST( testMoveLeft );
        CPPUNIT_TEST( testMoveRightWithFixedSpeed );
        CPPUNIT_TEST( testMoveLeftWithFixedSpeed );
        CPPUNIT_TEST( testMoveRightAndStop );
        CPPUNIT_TEST( testMoveLeftAndStop );
        CPPUNIT_TEST( testMoveRightAndThenLeft );
        CPPUNIT_TEST( testMoveLeftAndThenRight );
        CPPUNIT_TEST( testJumpOnGround );
        CPPUNIT_TEST_EXCEPTION( testJumpOnAir, ChellNotOnGroundException);
        CPPUNIT_TEST( testJumpTwoTimes );
        CPPUNIT_TEST( testJumpAndMoveRight );
        CPPUNIT_TEST( testJumpAndMoveLeft );
        CPPUNIT_TEST( testMoveRightAndJump );
        CPPUNIT_TEST( testMoveLeftAndJump );
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    Chell *chell;
    size_t width = 100;
    size_t height = 200;
    float chell_init_x = 0;
    float chell_init_y = 2;

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(100, 4, 0, -2);  // Piso
        world->createChell(chell_init_x, chell_init_y, 0);
        chell = world->getChell(0);
    }

    void tearDown() {
        delete world;
    }

    void testCreateChell() {
        cout << endl << endl << "TESTS CHELL";
        cout << endl << "TEST crear correctamente: ";
        CPPUNIT_ASSERT_EQUAL(chell->getPositionX(), chell_init_x);
        CPPUNIT_ASSERT_EQUAL(chell->getPositionY(), chell_init_y);
        cout << "OK";
    }

    void testTeletransport() {
        cout << endl <<  "TEST teletransportar: ";
        chell->teletransport(5,5);
        CPPUNIT_ASSERT_EQUAL(chell->getPositionX(), (float) 5);
        CPPUNIT_ASSERT_EQUAL(chell->getPositionY(), (float) 5);
        cout << "OK";
    }

    void testFall() {
        cout << endl << "TEST caer con gravedad: ";
        chell->teletransport(0, 4); // Elevo a chell para que caiga
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        float y_diff = chell->getPositionY() - chell_init_y;
        float x_diff = chell->getPositionX() - chell_init_x;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, x_diff);
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, y_diff);
        cout << "OK";
    }

    void testMoveRight() {
        cout << endl << "TEST mover hacia derecha: ";
        chell->move_right();
        for (int i = 1; i < STEP_ITERATIONS; i++)
            world->step();
        float diff_x = chell->getPositionX() - chell_init_x;
        CPPUNIT_ASSERT_GREATER((float) 0, diff_x);
        cout << "OK";
    }

    void testMoveLeft() {
        cout << endl << "TEST mover hacia izquierda: ";
        chell->move_left();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        float diff_x = chell->getPositionX() - chell_init_x;
        CPPUNIT_ASSERT_LESS((float) 0, diff_x);
        cout << "OK";
    }

    void testMoveRightWithFixedSpeed() {
        cout << endl << "TEST mover hacia derecha con velocidad constante: ";
        float x_step = 0;
        chell->move_right();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if (x_step == 0)
                x_step = chell->getPositionX() - chell_init_x;
            float diff_x = abs(x_step * i) - abs(chell->getPositionX());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
        }
        cout << "OK";
    }

    void testMoveLeftWithFixedSpeed() {
        cout << endl << "TEST mover hacia izquierda con velocidad constante: ";
        float x_step = 0;
        chell->move_left();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if (x_step == 0)
                x_step = chell->getPositionX() - chell_init_x;
            float diff_x = abs(x_step * i) - abs(chell->getPositionX());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
        }
        cout << "OK";
    }

    void testMoveLeftAndStop() {
        cout << endl << "TEST mover hacia izquierda y frenar: ";
        chell->move_left();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        chell->stop_movement();
        for (int i = 0; i < STEP_ITERATIONS; i++)   // Tiempo que demora frenar
            world->step(); // Tiempo que demora frenar por el impulso
        float pos_after_stop = chell->getPositionX();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            float diff_x = pos_after_stop - chell->getPositionX();
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
        }
        cout << "OK";
    }

    void testMoveRightAndStop() {
        cout << endl << "TEST mover hacia derecha y frenar: ";
        chell->move_right();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        chell->stop_movement();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step(); // Tiempo que demora frenar por el impulso
        float pos_after_stop = chell->getPositionX();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            float diff_x = pos_after_stop - chell->getPositionX();
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
        }
        cout << "OK";
    }

    void testMoveRightAndThenLeft() {
        cout << endl << "TEST mover hacia derecha y luego hacia izquierda: ";
        chell->move_right();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        float pos_before_move_left = chell->getPositionX();
        chell->move_left();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step(); // Tiempo que demora frenar por el impulso
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT_LESS(pos_before_move_left,  chell->getPositionX());
        cout << "OK";
    }

    void testMoveLeftAndThenRight() {
        cout << endl << "TEST mover hacia izquierda y luego hacia derecha: ";
        chell->move_left();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        float pos_before_move_left = chell->getPositionX();
        chell->move_right();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step(); // Tiempo que demora frenar por el impulso
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT_GREATER(pos_before_move_left,  chell->getPositionX());
        cout << "OK";
    }

    void testJumpOnGround() {
        cout << endl << "TEST saltar sobre una superficie: ";
        bool jumped = false;
        chell->jump();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if ((chell->getPositionY() - chell_init_y) > DELTA_POS)
                jumped = true;
        }
        CPPUNIT_ASSERT(jumped);
        cout << "OK";
    }

    void testJumpOnAir() {
        cout << endl << "TEST no es posible saltar en el aire: ";
        chell->jump();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            try {
                chell->jump();
            } catch (ChellNotOnGroundException& e) {
                cout << "OK";
                throw e;
            }
        }
    }

    void testJumpTwoTimes() {
        cout << endl << "TEST saltar, caer y volver a saltar: ";
        bool jumped1 = false, jumped2 = false;
        chell->jump();
        for (int i = 0; i < 10000; i++) {
            world->step();
            if ((chell->getPositionY() - chell_init_y) > DELTA_POS)
                jumped1 = true;
        }
        float diff_y = chell->getPositionY() - chell_init_y;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, diff_y);
        chell->jump();
        for (int i = 0; i < 10000; i++) {
            world->step();
            if ((chell->getPositionY() - chell_init_y) > DELTA_POS)
                jumped2 = true;
        }
        diff_y = chell->getPositionY() - chell_init_y;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, diff_y);
        CPPUNIT_ASSERT(jumped1);
        CPPUNIT_ASSERT(jumped2);
        cout << "OK";
    }

    void testJumpAndMoveRight() {
        cout << endl << "TEST saltar y moverse a la derecha en el aire: ";
        bool jumped = false, moved_on_air = false;
        chell->jump();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if ((chell->getPositionY() - chell_init_y) > DELTA_POS) {
                if (!jumped)
                    chell->move_right();    // Muevo una vez que salto
                jumped = true;
                if (chell->getPositionX() > chell_init_x)
                    moved_on_air = true;    // Se movio en X estando en el aire
            }
        }

        float diff_y = chell->getPositionY() - chell_init_y;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, diff_y);
        CPPUNIT_ASSERT_GREATER(chell_init_x, chell->getPositionX());
        CPPUNIT_ASSERT(jumped);
        CPPUNIT_ASSERT(moved_on_air);
        cout << "OK";
    }

    void testJumpAndMoveLeft() {
        cout << endl << "TEST saltar y moverse a la izquierda en el aire: ";
        bool jumped = false, moved_on_air = false;
        chell->jump();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if ((chell->getPositionY() - chell_init_y) > DELTA_POS) {
                if (!jumped)
                    chell->move_left();    // Muevo una vez que salto
                jumped = true;
                if (chell->getPositionX() < chell_init_x)
                    moved_on_air = true;    // Se movio en X estando en el aire
            }
        }
        float diff_y = chell->getPositionY() - chell_init_y;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, diff_y);
        CPPUNIT_ASSERT_LESS(chell_init_x, chell->getPositionX());
        CPPUNIT_ASSERT(jumped);
        CPPUNIT_ASSERT(moved_on_air);
        cout << "OK";
    }

    void testMoveRightAndJump() {
        cout << endl << "TEST moverse a la derecha y saltar ";
        bool jumped = false, jumped_after_moving = false;
        chell->move_right();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if (chell->getPositionX() > chell_init_x) {
                if (!jumped) {
                    jumped = true;
                    chell->jump();
                }
                if ((chell->getPositionY() - chell_init_y) > DELTA_POS)
                    jumped_after_moving = true;
            }
        }
        CPPUNIT_ASSERT(jumped);
        CPPUNIT_ASSERT(jumped_after_moving);
        CPPUNIT_ASSERT_LESS(DELTA_POS, chell->getPositionY() - chell_init_y);
        cout << "OK";
    }

    void testMoveLeftAndJump() {
        cout << endl << "TEST moverse a la izquierda y saltar ";
        bool jumped = false, jumped_after_moving = false;
        chell->move_left();
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if (chell->getPositionX() < chell_init_x) {
                if (!jumped) {
                    jumped = true;
                    chell->jump();
                }
                if ((chell->getPositionY() - chell_init_y) > DELTA_POS)
                    jumped_after_moving = true;
            }
        }
        CPPUNIT_ASSERT(jumped);
        CPPUNIT_ASSERT(jumped_after_moving);
        CPPUNIT_ASSERT_LESS(DELTA_POS, chell->getPositionY() - chell_init_y);
        cout << "OK";
    }

};

// todo: TEST TELETRANSPORTAR Y VER LAS VELOCIDADES ?

//todo: test chocar con pared, saltar a otra superficie, etc.

//todo: test caminar en diagonal cuando choca con triangulo

#endif //PORTAL_TESTCHELL_H
