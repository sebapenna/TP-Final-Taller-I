#ifndef PORTAL_TESTCHELL_H
#define PORTAL_TESTCHELL_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/World.h"
#include "../Server/constants.h"
#include <Common/exceptions.h>

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
        CPPUNIT_TEST( testCollideWithWall );
        CPPUNIT_TEST( testCollideWithRoof );
        CPPUNIT_TEST( testMoveRightCollideWithDiagonalBlock );
        CPPUNIT_TEST( testMoveLeftCollideWithDiagonalBlock );
        CPPUNIT_TEST( testMoveRightAndFallOverDiagonalBlock );
        CPPUNIT_TEST( testMoveLeftAndFallOverDiagonalBlock );
        CPPUNIT_TEST( testContactWithFallingRock );
        CPPUNIT_TEST( testContactWithRockInItsWay );
        CPPUNIT_TEST( testContactWithAcid );
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
        world->createRockBlock(1000, 4, 0, -2);  // Piso
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
        for (int i = 0; i < 200; i++) {
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
        for (int i = 0; i < 200; i++) {
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
        for (int i = 0; i < 200; i++) {
            world->step();
            if ((chell->getPositionY() - chell_init_y) > DELTA_POS)
                jumped1 = true;
        }
        float diff_y = chell->getPositionY() - chell_init_y;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, diff_y);
        chell->jump();
        for (int i = 0; i < 200; i++) {
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
        for (int i = 0; i < 200; i++) {
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
        for (int i = 0; i < 200; i++) {
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
        for (int i = 0; i < 200; i++) {
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
        for (int i = 0; i < 200; i++) {
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

    void testCollideWithWall() {
        cout << endl << "TEST moverse y chocar con pared: ";
        float b_width = 2, b_height = 60;
        float b_x = chell_init_x + CHELL_HALF_WIDTH + b_width;
        float b_y = b_height / 2;
        world->createRockBlock(b_width, b_height, b_x, b_y);
        chell->move_right();
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step();
        CPPUNIT_ASSERT_GREATER(chell_init_x, chell->getPositionX());
        float expected_pos = b_x - b_width/2 - CHELL_HALF_WIDTH;
        CPPUNIT_ASSERT_LESS(expected_pos, chell->getPositionX());
        float diff_y = chell->getPositionY() - chell_init_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        cout << "OK";
    }

    void testCollideWithRoof() {
        cout << endl << "TEST saltar y chocar con superficie: ";
        float b_width = 100;
        float b_height = 2;
        float b_x = 0;
        float b_y = chell_init_y + CHELL_HALF_HEIGHT + b_height;
        chell->jump();
        float max_height = 0;
        for (int i = 0; i < 200; ++i) {   // Jump with no roof
            world->step();
            if (chell->getPositionY() > max_height)
                max_height = chell->getPositionY();
        }
        world->createRockBlock(b_width, b_height, b_x, b_y);
        chell->jump();
        for (int i = 0; i < 200; ++i) {   // Jump with roof
            world->step();
            CPPUNIT_ASSERT_LESS(max_height, chell->getPositionY());
        }
        cout << "OK";
    }

    void testMoveRightCollideWithDiagonalBlock() {
        cout << endl << "TEST mover hacia derecha y caminar sobre diagonal: ";
        float b_width = 2 * CHELL_HALF_WIDTH, b_height = 2 * CHELL_HALF_HEIGHT;
        float b_x = chell_init_x + CHELL_HALF_WIDTH + 1;
        float b_y = 0;
        world->createMetalDiagonalBlock(b_width, b_height, b_x, b_y, O_NO);
        chell->move_right();
        bool y_increased = false;
        for (int i = 1; i < 200; i++) {
            world->step();
            CPPUNIT_ASSERT_GREATEREQUAL(chell_init_x, chell->getPositionX());
            if ((chell->getPositionY() - DELTA_POS) > chell_init_y)
                y_increased = true; // Subio por bloque diagonal
        }
        float diff_y = chell->getPositionY() - chell_init_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y); // Cayo al final del bloque
        CPPUNIT_ASSERT(y_increased);
        cout << "OK";
    }

    void testMoveLeftCollideWithDiagonalBlock() {
        cout << endl << "TEST mover hacia izquierda y caminar sobre diagonal: ";
        float b_width = 2 * CHELL_HALF_WIDTH, b_height = 2 * CHELL_HALF_HEIGHT;
        float b_x = chell_init_x - CHELL_HALF_WIDTH - b_width - 1;
        float b_y = 0;
        world->createMetalDiagonalBlock(b_width, b_height, b_x, b_y, O_NE);
        chell->move_left();
        bool y_increased = false;
        for (int i = 1; i < 200; i++) {
            world->step();
            CPPUNIT_ASSERT_LESSEQUAL(chell_init_x, chell->getPositionX());
            if ((chell->getPositionY() - DELTA_POS) > chell_init_y)
                y_increased = true; // Subio por bloque diagonal
        }
        float diff_y = chell->getPositionY() - chell_init_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y); // Cayo al final del bloque
        CPPUNIT_ASSERT(y_increased);
        cout << "OK";
    }

    void testMoveRightAndFallOverDiagonalBlock() {
        cout << endl << "TEST mover hacia derecha y caer por bloque diagonal: ";
        float b_width = 2 * CHELL_HALF_WIDTH, b_height = 2 * CHELL_HALF_HEIGHT;
        float ground_width = 2 * b_width;
        float ground_x = chell_init_x;
        float ground_y = chell_init_y + (CHELL_HALF_HEIGHT * 2);
        float b_x = ground_x + ground_width / 2;
        float b_y = ground_y - b_height / 2;
//         Superficie donde probar
        world->createRockBlock(ground_width, b_height, ground_x, ground_y);
        world->createMetalDiagonalBlock(b_width, b_height, b_x, b_y, O_NE);
        float new_x = ground_x;
        float new_y = ground_y + b_height / 2 + CHELL_HALF_HEIGHT;
        chell->teletransport(new_x, new_y);
        chell->move_right();
        for (int i = 1; i < 200; i++) {
            world->step();
            CPPUNIT_ASSERT_GREATEREQUAL(chell_init_x, chell->getPositionX());
        }
        float diff_y = chell->getPositionY() - chell_init_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        cout << "OK";
    }

    void testMoveLeftAndFallOverDiagonalBlock() {
        cout << endl << "TEST mover hacia izquierda y caer por bloque "
                        "diagonal: ";
        float b_width = 2 * CHELL_HALF_WIDTH, b_height = 2 * CHELL_HALF_HEIGHT;
        float ground_width = 2 * b_width;
        float ground_x = chell_init_x;
        float ground_y = chell_init_y + (CHELL_HALF_HEIGHT * 2);
        float b_x = ground_x - ground_width / 2;
        float b_y = ground_y - b_height / 2;
        // Superficie donde probar
        world->createRockBlock(ground_width, b_height, ground_x, ground_y);
        world->createMetalDiagonalBlock(b_width, b_height, b_x, b_y, O_NO);
        float new_x = ground_x;
        float new_y = ground_y + b_height / 2 + CHELL_HALF_HEIGHT;
        chell->teletransport(new_x, new_y);
        chell->move_left();
        for (int i = 1; i < 200; i++) {
            world->step();
            if (abs(chell->getPositionX()) > DELTA_POS) // Evito falla por delta
                CPPUNIT_ASSERT_LESSEQUAL(chell_init_x, chell->getPositionX());
        }
        float diff_y = chell->getPositionY() - chell_init_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        cout << "OK";
    }

    void testContactWithFallingRock() {
        cout << endl << "TEST morir al caerle roca encima: ";
        float rock_x = chell_init_x;
        float rock_y = chell_init_y + CHELL_HALF_HEIGHT + ROCK_HALF_LEN + 1;
        // Creo roca sobre chell
        world->createRock(rock_x, rock_y);
        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 1; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(chell->isDead()); // Se elimino chell
        CPPUNIT_ASSERT_LESS(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testContactWithRockInItsWay() {
        cout << endl << "TEST chocar con roca en su camino y no morir: ";
        float rock_x = chell_init_x + CHELL_HALF_WIDTH + ROCK_HALF_LEN + 1;
        float rock_y = chell_init_y;
        world->createRock(rock_x, rock_y);
        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 1; i < 2 * STEP_ITERATIONS; i++)
            world->step();
        auto rock = world->getRocks().at(0);
        // Verifico roca frena a chell
        CPPUNIT_ASSERT_LESS(rock->getPositionX(), chell->getPositionX());
        CPPUNIT_ASSERT(!chell->isDead());
        CPPUNIT_ASSERT_EQUAL(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testContactWithAcid() {
        cout << endl << "TEST morir tras contacto con acido: ";
        float acid_x = chell_init_x + CHELL_HALF_WIDTH + ACID_HALF_WIDTH + 1;
        float acid_y = ACID_HALF_HEIGHT;
        world->createAcid(acid_x, acid_y);
        auto n_bodies = world->getWorld()->GetBodyCount();
        chell->move_right();    // Avanzo chell para que choque con acido
        for (int i = 1; i < 2 * STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(chell->isDead());
        CPPUNIT_ASSERT_LESS(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

};

// todo: TEST TELETRANSPORTAR Y VER LAS VELOCIDADES ?


#endif //PORTAL_TESTCHELL_H
