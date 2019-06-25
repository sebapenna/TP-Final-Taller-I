#ifndef PORTAL_TESTCHELL_H
#define PORTAL_TESTCHELL_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <Common/exceptions.h>
#include <string>
#include <Server/Model/CollidableData/Data/RockBlockData.h>
#include <Server/Model/CollidableData/Data/ChellData.h>
#include <Server/Model/CollidableData/Data/MetalDiagonalBlockData.h>
#include <Server/Model/CollidableData/Data/RockData.h>
#include <Server/Model/CollidableData/Data/AcidData.h>
#include <Server/Model/CollidableData/Data/EnergyTransmitterData.h>
#include <Server/Model/CollidableData/Data/EnergyBarrierData.h>

using std::cout;
using std::endl;
using std::make_shared;

class TestChell : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( TestChell );
        CPPUNIT_TEST( testCreateChell );
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
        CPPUNIT_TEST( testContactWithEnergyBall );
        CPPUNIT_TEST( testAddedToUpdateVectorAfterMoving );
        CPPUNIT_TEST( testAddedToUpdateVectorafterStopping );
        CPPUNIT_TEST( testAddedToUpdateVectorAfterJumping );
        CPPUNIT_TEST( testAddedToUpdateVectorAfterLandingOnGround );
        CPPUNIT_TEST( testAddedToDeleteVectorAfterDead );
        CPPUNIT_TEST( testIgnoreCollitionWithOtherChell );
        CPPUNIT_TEST( testIgnoreCollitionWithEnergyBarrier );
    CPPUNIT_TEST_SUITE_END();

private:
    std::shared_ptr<Configuration> ptr;
    Configuration *config;
    World *world;
    Chell *chell;
    size_t width = 100;
    size_t height = 200;
    float chell_init_x = 0;
    float chell_init_y = 2;

public:
    void setUp() {
        ptr = make_shared<Configuration>();
        config = ptr.get();
        world = new World(width, height, ptr);
        auto data = make_shared<RockBlockData>(100, 4, 0, -2); // Piso
        world->createCollidable(data);
        auto data2 = make_shared<ChellData>(1, chell_init_x, chell_init_y);
        world->createCollidable(data2);
        chell = world->getChell(0);
    }

    void tearDown() {
        delete world;
    }

    void testCreateChell() {
        cout << endl << endl << "TESTS CHELL";
        cout << endl << "TEST crear correctamente: ";
        CPPUNIT_ASSERT_EQUAL(chell->x(), chell_init_x);
        CPPUNIT_ASSERT_EQUAL(chell->y(), chell_init_y);
        cout << "OK";
    }

    void testFall() {
        cout << endl << "TEST caer con gravedad: ";
        auto data = make_shared<ChellData>(0, 10, 10);
        world->createCollidable(data); // Creo chell en aire
        auto chell2 = world->getChell(1);
        for (int i = 0; i < 2 * config->getFps(); i++)
            world->step();
        float y_diff = chell2->y() - 2;
        float x_diff = chell2->x() - 10;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, x_diff);
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, y_diff);
        cout << "OK";
    }

    void testMoveRight() {
        cout << endl << "TEST mover hacia derecha: ";
        chell->move_right();
        for (int i = 1; i < config->getFps(); i++)
            world->step();
        float diff_x = chell->x() - chell_init_x;
        CPPUNIT_ASSERT_GREATER((float) 0, diff_x);
        CPPUNIT_ASSERT(chell->isMoving());
        CPPUNIT_ASSERT_EQUAL(O_E, chell->movementDirection());
        CPPUNIT_ASSERT_EQUAL(NOT_TILTED, chell->tilt());
        cout << "OK";
    }

    void testMoveLeft() {
        cout << endl << "TEST mover hacia izquierda: ";
        chell->move_left();
        for (int i = 0; i < config->getFps(); i++)
            world->step();
        float diff_x = chell->x() - chell_init_x;
        CPPUNIT_ASSERT_LESS((float) 0, diff_x);
        CPPUNIT_ASSERT(chell->isMoving());
        CPPUNIT_ASSERT_EQUAL(O_O, chell->movementDirection());
        CPPUNIT_ASSERT_EQUAL(NOT_TILTED, chell->tilt());
        cout << "OK";
    }

    void testMoveRightWithFixedSpeed() {
        cout << endl << "TEST mover hacia derecha con velocidad constante: ";
        float x_step = 0;
        chell->move_right();
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            if (x_step == 0)
                x_step = chell->x() - chell_init_x;
            float diff_x = abs(x_step * i) - abs(chell->x());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
        }
        cout << "OK";
    }

    void testMoveLeftWithFixedSpeed() {
        cout << endl << "TEST mover hacia izquierda con velocidad constante: ";
        float x_step = 0;
        chell->move_left();
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            if (x_step == 0)
                x_step = chell->x() - chell_init_x;
            float diff_x = abs(x_step * i) - abs(chell->x());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
        }
        cout << "OK";
    }

    void testMoveLeftAndStop() {
        cout << endl << "TEST mover hacia izquierda y frenar: ";
        chell->move_left();
        for (int i = 0; i < config->getFps(); i++)
            world->step();
        chell->stopMovement();
        for (int i = 0; i < config->getFps(); i++)   // Tiempo que demora frenar
            world->step(); // Tiempo que demora frenar por el impulso
        float pos_after_stop = chell->x();
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            float diff_x = pos_after_stop - chell->x();
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
            CPPUNIT_ASSERT(!chell->isMoving());
        }
        cout << "OK";
    }

    void testMoveRightAndStop() {
        cout << endl << "TEST mover hacia derecha y frenar: ";
        chell->move_right();
        for (int i = 0; i < config->getFps(); i++)
            world->step();
        chell->stopMovement();
        for (int i = 0; i < config->getFps(); i++)
            world->step(); // Tiempo que demora frenar por el impulso
        float pos_after_stop = chell->x();
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            float diff_x = pos_after_stop - chell->x();
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
            CPPUNIT_ASSERT(!chell->isMoving());
        }
        cout << "OK";
    }

    void testMoveRightAndThenLeft() {
        cout << endl << "TEST mover hacia derecha y luego hacia izquierda: ";
        chell->move_right();
        for (int i = 0; i < config->getFps(); i++)
            world->step();
        float pos_before_move_left = chell->x();
        chell->move_left();
        for (int i = 0; i < config->getFps(); i++)
            world->step(); // Tiempo que demora frenar por el impulso
        for (int i = 0; i < config->getFps(); i++)
            world->step();
        CPPUNIT_ASSERT_LESS(pos_before_move_left, chell->x());
        cout << "OK";
    }

    void testMoveLeftAndThenRight() {
        cout << endl << "TEST mover hacia izquierda y luego hacia derecha: ";
        chell->move_left();
        for (int i = 0; i < config->getFps(); i++)
            world->step();
        float pos_before_move_left = chell->x();
        chell->move_right();
        for (int i = 0; i < config->getFps(); i++)
            world->step(); // Tiempo que demora frenar por el impulso
        for (int i = 0; i < config->getFps(); i++)
            world->step();
        CPPUNIT_ASSERT_GREATER(pos_before_move_left, chell->x());
        cout << "OK";
    }

    void testJumpOnGround() {
        cout << endl << "TEST saltar sobre una superficie: ";
        bool jumped = false;
        chell->jump();
        for (int i = 0; i < 200; i++) {
            world->step();
            if ((chell->y() - chell_init_y) > DELTA_POS) {
                jumped = true;
                CPPUNIT_ASSERT(chell->isJumping());
            }
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
            if ((chell->y() - chell_init_y) > DELTA_POS)
                jumped1 = true;
        }
        float diff_y = chell->y() - chell_init_y;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, diff_y);
        chell->jump();
        for (int i = 0; i < 200; i++) {
            world->step();
            if ((chell->y() - chell_init_y) > DELTA_POS)
                jumped2 = true;
        }
        diff_y = chell->y() - chell_init_y;
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
            if ((chell->y() - chell_init_y) > DELTA_POS) {
                if (!jumped) {
                    chell->move_right();    // Muevo una vez que salto
                    CPPUNIT_ASSERT(chell->isJumping());
                }
                jumped = true;
                if (chell->x() > chell_init_x)
                    moved_on_air = true;    // Se movio en X estando en el aire
            }
        }
        float diff_y = chell->y() - chell_init_y;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, diff_y);
        CPPUNIT_ASSERT_GREATER(chell_init_x, chell->x());
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
            if ((chell->y() - chell_init_y) > DELTA_POS) {
                if (!jumped) {
                    chell->move_left();    // Muevo una vez que salto
                    CPPUNIT_ASSERT(chell->isJumping());
                }
                jumped = true;
                if (chell->x() < chell_init_x)
                    moved_on_air = true;    // Se movio en X estando en el aire
            }
        }
        float diff_y = chell->y() - chell_init_y;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, diff_y);
        CPPUNIT_ASSERT_LESS(chell_init_x, chell->x());
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
            if (chell->x() > chell_init_x) {
                if (!jumped) {
                    jumped = true;
                    chell->jump();
                }
                if ((chell->y() - chell_init_y) > DELTA_POS)
                    jumped_after_moving = true;
            }
        }
        CPPUNIT_ASSERT(jumped);
        CPPUNIT_ASSERT(jumped_after_moving);
        CPPUNIT_ASSERT_LESS(DELTA_POS, chell->y() - chell_init_y);
        cout << "OK";
    }

    void testMoveLeftAndJump() {
        cout << endl << "TEST moverse a la izquierda y saltar ";
        bool jumped = false, jumped_after_moving = false;
        chell->move_left();
        for (int i = 0; i < 200; i++) {
            world->step();
            if (chell->x() < chell_init_x) {
                if (!jumped) {
                    jumped = true;
                    chell->jump();
                }
                if ((chell->y() - chell_init_y) > DELTA_POS)
                    jumped_after_moving = true;
            }
        }
        CPPUNIT_ASSERT(jumped);
        CPPUNIT_ASSERT(jumped_after_moving);
        CPPUNIT_ASSERT_LESS(DELTA_POS, chell->y() - chell_init_y);
        cout << "OK";
    }

    void testCollideWithWall() {
        cout << endl << "TEST moverse y chocar con pared: ";
        float b_width = 2, b_height = 60;
        float b_x = chell_init_x + chell->width()/2 + b_width;
        float b_y = b_height / 2;
        auto data = make_shared<RockBlockData>(b_width, b_height, b_x, b_y);
        world->createCollidable(data);
        chell->move_right();
        for (int i = 0; i < config->getFps(); ++i)
            world->step();
        CPPUNIT_ASSERT_GREATER(chell_init_x, chell->x());
        float expected_pos = b_x - b_width/2 - chell->width()/2;
        CPPUNIT_ASSERT_LESS(expected_pos, chell->x());
        float diff_y = chell->y() - chell_init_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        cout << "OK";
    }

    void testCollideWithRoof() {
        cout << endl << "TEST saltar y chocar con superficie: ";
        float b_width = 100;
        float b_height = 2;
        float b_x = 0;
        float b_y = chell_init_y + config->getChellHalfHeight() + b_height;
        chell->jump();
        float max_height = 0;
        for (int i = 0; i < 200; ++i) {   // Jump with no roof
            world->step();
            if (chell->y() > max_height)
                max_height = chell->y();
        }
        auto data = make_shared<RockBlockData>(b_width, b_height, b_x, b_y);
        world->createCollidable(data);
        chell->jump();
        for (int i = 0; i < 200; ++i) {   // Jump with roof
            world->step();
            CPPUNIT_ASSERT_LESS(max_height, chell->y());
        }
        cout << "OK";
    }

    void testMoveRightCollideWithDiagonalBlock() {
        cout << endl << "TEST mover hacia derecha y caminar sobre diagonal: ";
        float b_width = 2 * chell->width()/2, b_height = 2 * config->getChellHalfHeight();
        float b_x = chell_init_x + chell->width()/2 + 1;
        float b_y = 0;
        auto data = make_shared<MetalDiagonalBlockData>(b_width, b_height, b_x, b_y, "NO");
        world->createCollidable(data);
        chell->move_right();
        bool y_increased = false, tilted = false;
        for (int i = 1; i < 200; i++) {
            world->step();
            CPPUNIT_ASSERT_GREATEREQUAL(chell_init_x, chell->x());
            if ((chell->y() - DELTA_POS) > chell_init_y)
                y_increased = true; // Subio por bloque diagonal
            if (chell->tilt() == WEST)
                tilted = true;
        }
        float diff_y = chell->y() - chell_init_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y); // Cayo al final del bloque
        CPPUNIT_ASSERT(y_increased);
        CPPUNIT_ASSERT(tilted);
        CPPUNIT_ASSERT_EQUAL(NOT_TILTED, chell->tilt());
        cout << "OK";
    }

    void testMoveLeftCollideWithDiagonalBlock() {
        cout << endl << "TEST mover hacia izquierda y caminar sobre diagonal: ";
        float b_width = 2 * chell->width()/2, b_height = 2 * config->getChellHalfHeight();
        float b_x = chell_init_x - chell->width()/2 - b_width - 1;
        float b_y = 0;
        auto data = make_shared<MetalDiagonalBlockData>(b_width, b_height, b_x, b_y, "NE");
        world->createCollidable(data);
        chell->move_left();
        bool y_increased = false, tilted= false;
        for (int i = 1; i < 200; i++) {
            world->step();
            CPPUNIT_ASSERT_LESSEQUAL(chell_init_x, chell->x());
            if ((chell->y() - DELTA_POS) > chell_init_y)
                y_increased = true; // Subio por bloque diagonal
            if (chell->tilt() == EAST)
                tilted = true;
        }
        float diff_y = chell->y() - chell_init_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y); // Cayo al final del bloque
        CPPUNIT_ASSERT(y_increased);
        CPPUNIT_ASSERT(tilted);
        CPPUNIT_ASSERT_EQUAL(NOT_TILTED, chell->tilt());
        cout << "OK";
    }

    void testMoveRightAndFallOverDiagonalBlock() {
        cout << endl << "TEST mover hacia derecha y caer por bloque diagonal: ";
        float b_width = 2 * chell->width()/2, b_height = 2 * config->getChellHalfHeight();
        float ground_width = 2 * b_width;
        float ground_x = chell_init_x;
        float ground_y = chell_init_y + (config->getChellHalfHeight() * 2);
        float b_x = ground_x + ground_width / 2;
        float b_y = ground_y - b_height / 2;
//         Superficie donde probar
        auto data1 = make_shared<RockBlockData>(ground_width, b_height, ground_x, ground_y);
        world->createCollidable(data1);
        auto data = make_shared<MetalDiagonalBlockData>(b_width, b_height, b_x, b_y, "NE");
        world->createCollidable(data);
        float new_x = ground_x;
        float new_y = ground_y + b_height / 2 + config->getChellHalfHeight();
        auto data3 = make_shared<ChellData>(1, new_x, new_y);
        world->createCollidable(data3);
        auto chell2 = world->getChell(1);
        chell2->move_right();
        for (int i = 1; i < 200; i++) {
            world->step();
            CPPUNIT_ASSERT_GREATEREQUAL(chell_init_x, chell2->x());
        }
        float diff_y = chell2->y() - chell_init_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        cout << "OK";
    }

    void testMoveLeftAndFallOverDiagonalBlock() {
        cout << endl << "TEST mover hacia izquierda y caer por bloque "
                        "diagonal: ";
        float b_width = 2 * chell->width()/2, b_height = 2 * config->getChellHalfHeight();
        float ground_width = 2 * b_width;
        float ground_x = chell_init_x;
        float ground_y = chell_init_y + (config->getChellHalfHeight() * 2);
        float b_x = ground_x - ground_width / 2;
        float b_y = ground_y - b_height / 2;
        // Superficie donde probar
        auto data1 = make_shared<RockBlockData>(ground_width, b_height, ground_x, ground_y);
        world->createCollidable(data1);
        auto data = make_shared<MetalDiagonalBlockData>(b_width, b_height, b_x, b_y, "NO");
        world->createCollidable(data);
        float new_x = ground_x;
        float new_y = ground_y + b_height / 2 + config->getChellHalfHeight();
        auto data3 = make_shared<ChellData>(1, new_x, new_y);
        world->createCollidable(data3);
        auto chell2 = world->getChell(1);
        chell2->move_left();
        for (int i = 1; i < 200; i++) {
            world->step();
            if (abs(chell->x()) > DELTA_POS) // Evito falla por delta
                CPPUNIT_ASSERT_LESSEQUAL(chell_init_x, chell2->x());
        }
        float diff_y = chell->y() - chell_init_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        cout << "OK";
    }

    void testContactWithFallingRock() {
        cout << endl << "TEST morir al caerle roca encima: ";
        float rock_x = chell_init_x;
        float rock_y = chell_init_y + chell->width()/2 + config->getRockHalfLen() + 1;
        // Creo roca sobre chell
        auto data = make_shared<RockData>(rock_x, rock_y);
        world->createCollidable(data);
        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 1; i < config->getFps(); i++)
            world->step();
        CPPUNIT_ASSERT_EQUAL((Chell*)nullptr, world->getChell(0)); // Se elimino chell
        CPPUNIT_ASSERT_LESS(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testContactWithRockInItsWay() {
        cout << endl << "TEST chocar con roca en su camino y no morir: ";
        float rock_x = chell_init_x + chell->width()/2 + config->getRockHalfLen() + 1;
        float rock_y = chell_init_y;
        auto data = make_shared<RockData>(rock_x, rock_y);
        world->createCollidable(data);
        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 1; i < 2 * config->getFps(); i++)
            world->step();
        auto rock = world->getRock(0);
        // Verifico roca frena a chell
        CPPUNIT_ASSERT_LESS(rock->x(), chell->x());
        CPPUNIT_ASSERT(!chell->isDead(1 / config->getFps()));
        CPPUNIT_ASSERT_EQUAL(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testContactWithAcid() {
        cout << endl << "TEST morir tras contacto con acido: ";
        float w = 4;
        float acid_x = chell_init_x + chell->width()/2 + w/2 + 1;
        float acid_y = config->getAcidHalfHeight();
        auto data = make_shared<AcidData>(acid_x, acid_y, w);
        world->createCollidable(data);
        auto n_bodies = world->getWorld()->GetBodyCount();
        chell->move_right();    // Avanzo chell para que choque con acido
        for (int i = 1; i < 2 * config->getFps(); i++)
            world->step();
        CPPUNIT_ASSERT_EQUAL((Chell*)nullptr, world->getChell(0)); // Se elimino chell
        CPPUNIT_ASSERT_LESS(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testContactWithEnergyBall() {
        cout << endl << "TEST morir tras contacto con energy ball: ";
        float transm_x = chell_init_x + chell->width()/2 + 2 * (config->getEnergyBallRadius()) +
                config->getEnergyBlockHalfLen() + 4;
        float transm_y  = config->getEnergyBlockHalfLen();
        auto data = make_shared<EnergyTransmitterData>(transm_x, transm_y, "O");
        world->createCollidable(data);
        for (int j = 1; j < config->getTimeToReleaseEnrgBall(); ++j)
            for (int i = 0; i < config->getFps(); ++i)
                world->step();
        for (int i = 0; i < config->getFps(); ++i)
            world->step(); // Step donde se crea EnergyBall
        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < 2 * config->getFps(); ++i)
            world->step(); // Permito movimiento energy ball
        CPPUNIT_ASSERT_EQUAL((Chell*)nullptr, world->getChell(0)); // Se elimino chell
        CPPUNIT_ASSERT_LESS(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testAddedToUpdateVectorAfterMoving() {
        cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                        "movimiento: ";
        // Testeo con move_right
        CPPUNIT_ASSERT(world->getObjectsToUpdate().empty());
        chell->move_right();
        bool updated = false;
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            if (world->getObjectsToUpdate().size() == 1) {
                // Verifico no se lo agrego a vector de elementos a eliminar
                CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
                // Verifico chell correcta
                auto update_chell = (Chell *) world->getObjectsToUpdate().at(0);
                CPPUNIT_ASSERT_EQUAL((size_t) 0, update_chell->id());
                CPPUNIT_ASSERT(update_chell->isMoving());
                CPPUNIT_ASSERT_EQUAL(NOT_TILTED, chell->tilt());
                CPPUNIT_ASSERT_EQUAL(O_E, chell->movementDirection());
                CPPUNIT_ASSERT(!chell->isJumping());
                CPPUNIT_ASSERT(!chell->isShooting());
                CPPUNIT_ASSERT(!chell->isDead(1 / config->getFps()));
                updated = true;
            }
        }
        CPPUNIT_ASSERT(updated);

        updated = false;
        // Testeo con move_left
        chell->move_left();
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            if (world->getObjectsToUpdate().size() == 1) {
                // Verifico no se lo agrego a vector de elementos a eliminar
                CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
                // Verifico chell correcta
                auto update_chell = (Chell *) world->getObjectsToUpdate().at(0);
                CPPUNIT_ASSERT_EQUAL((size_t) 0, update_chell->id());
                CPPUNIT_ASSERT(update_chell->isMoving());
                CPPUNIT_ASSERT_EQUAL(NOT_TILTED, chell->tilt());
                CPPUNIT_ASSERT_EQUAL(O_O, chell->movementDirection());
                CPPUNIT_ASSERT(!chell->isJumping());
                CPPUNIT_ASSERT(!chell->isShooting());
                CPPUNIT_ASSERT(!chell->isDead(1 / config->getFps()));
                updated = true;
            }
        }
        CPPUNIT_ASSERT(updated);
        cout << "OK";
    }

    void testAddedToUpdateVectorAfterJumping() {
        cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                        "saltar: ";
        // Testeo con move_right
        CPPUNIT_ASSERT(world->getObjectsToUpdate().empty());
        chell->jump();
        bool updated = false;
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            if (world->getObjectsToUpdate().size() == 1) {
                // Verifico no se lo agrego a vector de elementos a eliminar
                CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
                // Verifico chell correcta
                auto update_chell = (Chell *) world->getObjectsToUpdate().at(0);
                CPPUNIT_ASSERT_EQUAL((size_t) 0, update_chell->id());
                CPPUNIT_ASSERT(!update_chell->isMoving());
                CPPUNIT_ASSERT_EQUAL(NOT_TILTED, chell->tilt());
                CPPUNIT_ASSERT_EQUAL(O_E, chell->movementDirection());
                CPPUNIT_ASSERT(chell->isJumping());
                CPPUNIT_ASSERT(!chell->isShooting());
                CPPUNIT_ASSERT(!chell->isDead(1 / config->getFps()));
                updated = true;
            }
        }
        CPPUNIT_ASSERT(updated);
        cout << "OK";
    }

    void testAddedToUpdateVectorAfterLandingOnGround() {
        cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                        "caer en superficie tras salto: ";
        // Testeo con move_right
        CPPUNIT_ASSERT(world->getObjectsToUpdate().empty());
        chell->jump();
        bool updated = false;
        for (int i = 0; i < 10 * config->getFps(); i++) {    // Varias iteraciones para saltar y caer
            world->step();
            if (world->getObjectsToUpdate().size() == 1) {
                auto update_chell = (Chell *) world->getObjectsToUpdate().at(0);
                if (!update_chell->isJumping()) {   // Chell cayo en superficie
                    // Verifico no se lo agrego a vector de elementos a eliminar
                    CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
                    // Verifico chell correcta
                    CPPUNIT_ASSERT_EQUAL((size_t) 0, update_chell->id());
                    CPPUNIT_ASSERT(!update_chell->isMoving());
                    CPPUNIT_ASSERT_EQUAL(NOT_TILTED, chell->tilt());
                    CPPUNIT_ASSERT_EQUAL(O_E, chell->movementDirection());
                    CPPUNIT_ASSERT(!chell->isJumping());
                    CPPUNIT_ASSERT(!chell->isShooting());
                    CPPUNIT_ASSERT(!chell->isDead(1 / config->getFps()));
                    updated = true;
                }
            }
        }
        CPPUNIT_ASSERT(updated);
        cout << "OK";
    }

     void testAddedToUpdateVectorafterStopping() {
         cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                         "frenar movimiento: ";
         CPPUNIT_ASSERT(world->getObjectsToUpdate().empty());
         chell->move_right();
         for (int i = 0; i < config->getFps(); i++)
             world->step();
         chell->stopMovement();
         bool updated = false;
         for (int i = 0; i < config->getFps(); i++) {
             world->step();
             if (world->getObjectsToUpdate().size() == 1) { // Chell freno (demora mas de un step)
                 // Verifico no se lo agrego a vector de elementos a eliminar
                 CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
                 // Verifico chell correcta
                 auto update_chell = (Chell*) world->getObjectsToUpdate().at(0);
                 CPPUNIT_ASSERT_EQUAL((size_t) 0, update_chell->id());
                 CPPUNIT_ASSERT_EQUAL(NOT_TILTED, chell->tilt());
                 CPPUNIT_ASSERT_EQUAL(O_E, chell->movementDirection());
                 CPPUNIT_ASSERT(!update_chell->isMoving()); // Not moving implica que se freno
                 CPPUNIT_ASSERT(!chell->isJumping());
                 CPPUNIT_ASSERT(!chell->isShooting());
                 CPPUNIT_ASSERT(!chell->isDead(1 / config->getFps()));
                 updated = true;
             }
         }
         CPPUNIT_ASSERT(updated);
         cout << "OK";
    }

    void testAddedToDeleteVectorAfterDead() {
        cout << endl << "TEST verificar que se agrega a vector de objetos a eliminar luego de "
                        "morir: ";
        float w = 4;
        float acid_x = chell_init_x + chell->width()/2 + w/2 + 1;
        float acid_y = config->getAcidHalfHeight();
        auto data = make_shared<AcidData>(acid_x, acid_y, w);
        world->createCollidable(data);
        chell->move_right();
        bool deleted = true;
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            if (world->getObjectsToDelete().size() == 1) { // Chell freno (demora mas de un step)
                // Verifico no se lo agrego a vector de elementos a actualizar
                CPPUNIT_ASSERT(world->getObjectsToUpdate().empty());
                // Verifico chell correcta
                auto deleted_chell_data = world->getObjectsToDelete().at(0);
                CPPUNIT_ASSERT_EQUAL((size_t) 0, deleted_chell_data.first);
                CPPUNIT_ASSERT_EQUAL(CHELL, deleted_chell_data.second);
                deleted = true;
            }
        }
        CPPUNIT_ASSERT(deleted);
        cout << "OK";
    }

    void testIgnoreCollitionWithOtherChell() {
        cout << endl << "TEST ignorar contacto con otras chell: ";
        float chell2_x = chell_init_x + 10, chell2_y = chell_init_y;
        auto data = make_shared<ChellData>(1, chell2_x, chell2_y);
        world->createCollidable(data);
        auto chell2 = world->getChell(1);
        chell->move_right();
        chell2->move_left(); // Las hago mover en centido contrario
        CPPUNIT_ASSERT_LESS(chell2->x(), chell->x());  // Una paso a la otra
        for (int i = 0; i < config->getFps(); i++) {
            world->step();}
        CPPUNIT_ASSERT_LESS(chell->x(), chell2->x());  // Una paso a la otra
        cout << "OK";
    }

    void testIgnoreCollitionWithEnergyBarrier() {
        cout << endl << "TEST ignorar contacto con barrera energia: ";
        float barrier_x = chell_init_x + 10, barrier_y = config->getBarrierHalfLen();
        auto data = make_shared<EnergyBarrierData>(barrier_x, barrier_y, "V");
        world->createCollidable(data);
        chell->move_right();
        for (int i = 0; i < config->getFps(); i++) {
            world->step();}
        CPPUNIT_ASSERT_GREATER(barrier_x, chell->x());  // Chell paso barrier
        cout << "OK";
    }
};


#endif //PORTAL_TESTCHELL_H
