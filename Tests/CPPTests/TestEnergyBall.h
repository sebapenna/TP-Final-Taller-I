#ifndef PORTAL_TESTENERGYBALL_H
#define PORTAL_TESTENERGYBALL_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <string>

using std::cout;
using std::endl;

class TestEnergyBall : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestEnergyBall);
        CPPUNIT_TEST(testContactWithRockBlock);
        CPPUNIT_TEST(testContactWithAcid);
        CPPUNIT_TEST(testContactWithButton);
        CPPUNIT_TEST(testContactWithRock);
        CPPUNIT_TEST(testContactWithEnergyTransmitter);
        CPPUNIT_TEST(testContactWithChell);
        CPPUNIT_TEST(testContactWithEnergyBall);
        CPPUNIT_TEST(testContactWithEnergyBarrier);
        CPPUNIT_TEST(testContactWithOpenGate);
        CPPUNIT_TEST(testContactWithClosedGate);
        CPPUNIT_TEST(testAddedToUpdateVectorAfterMoving);
        CPPUNIT_TEST(testAddedToDeleteVectorAfterDead);
        CPPUNIT_TEST(testContactWithMetalBlockFromLeft);
        CPPUNIT_TEST(testContactWithMetalBlockFromRight);
        CPPUNIT_TEST(testContactWithMetalBlockFromAbove);
        CPPUNIT_TEST(testContactWithMetalBlockFromBelow);
//        CPPUNIT_TEST(testContactWithMetalDiagonalBlockNEFromLeft);
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    size_t width = 100, height = 200;
    float e_transm_x = 0, e_transm_y = 2;

public:
    void setUp() override {
        world = new World(width, height);
    }

    void tearDown() override {
        delete world;
    }

    void releaseEnergyBall() {
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i)
                world->step();
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
    }

    void testContactWithRockBlock() {
        cout << endl << endl << "TEST ENERGY BALL";
        cout << endl << "TEST eliminar al contacto con bloque roca: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);

        float wall_width = 4, wall_height = 10;
        float wall_x = energy_ball->getX() + ENRG_BALL_RADIUS + wall_width;
        float wall_y = wall_height / 2;
        // Creo pared donde colisionar la bola
        world->createRockBlock(wall_width, wall_height, wall_x, wall_y);

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        int n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }

        CPPUNIT_ASSERT(ball_deleted);
        cout << "OK";
    }

    void testContactWithAcid() {
        cout << endl << "TEST eliminar al contacto con acido: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);

        float acid_x = energy_ball->getX();
        float acid_y = energy_ball->getY() - ENRG_BALL_RADIUS - ACID_HALF_HEIGHT - 1;

        // Creo acido donde colisionar la bola
        world->createAcid(acid_x, acid_y);
        int n_bodies = world->getWorld()->GetBodyCount();

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }
        CPPUNIT_ASSERT(ball_deleted);
        cout << "OK";
    }

    void testContactWithButton() {
        cout << endl << "TEST eliminar al contacto con boton: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);

        float button_x = energy_ball->getX();
        float button_y = energy_ball->getY() - ENRG_BALL_RADIUS - BUTTON_HALF_HEIGHT - 1;

        // Creo boton donde colisionar la bola
        world->createButton(button_x, button_y);
        int n_bodies = world->getWorld()->GetBodyCount();

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }

        CPPUNIT_ASSERT(ball_deleted);
        cout << "OK";
    }

    void testContactWithRock() {
        cout << endl << "TEST eliminar al contacto con roca: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);

        float rock_x = energy_ball->getX();
        float rock_y = energy_ball->getY() - ENRG_BALL_RADIUS - ROCK_HALF_LEN - 1;

        // Creo roca donde colisionar la bola
        world->createRock(rock_x, rock_y);
        int n_bodies = world->getWorld()->GetBodyCount();

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }

        CPPUNIT_ASSERT(ball_deleted);
        cout << "OK";
    }

    void testContactWithEnergyTransmitter() {
        cout << endl << "TEST eliminar al contacto con transmisor de energia: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBall(0);

        float e_transm_2_x = e_ball->getX();
        float e_transm_2_y = e_ball->getY() - ENRG_BALL_RADIUS - ENRG_BLOCK_HALF_LEN- 1;

        // Creo tranmisor donde colisionar la bola
        world->createEnergyTransmitter(e_transm_2_x, e_transm_2_y, O_E);
        int n_bodies = world->getWorld()->GetBodyCount();

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }

        CPPUNIT_ASSERT(ball_deleted);
        cout << "OK";
    }

    void testContactWithChell() {
        cout << endl << "TEST eliminar al contacto con chell: ";

        world->createRockBlock(100, 4, 0, -2); // Piso
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);

        float chell_x = energy_ball->getX() + ENRG_BALL_RADIUS + CHELL_HALF_WIDTH + 1;
        float chell_y = energy_ball->getY();

        // Creo chell donde colisionar la bola
        world->createChell(chell_x, chell_y);
        int n_bodies = world->getWorld()->GetBodyCount();

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }

        CPPUNIT_ASSERT(ball_deleted);
        cout << "OK";
    }

    void testContactWithEnergyBall() {
        cout << endl << "TEST ignorar contacto con otra bola de energia: ";

        float e_transm_2_x = e_transm_x + 4 * ENRG_BALL_RADIUS + 2 * ENRG_BLOCK_HALF_LEN + 2;
        float e_transm_2_y = e_transm_y;
        // Creo transmisores en sentido opuesto para que choquen bolas energia
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        world->createEnergyTransmitter(e_transm_2_x, e_transm_2_y, O_O);
        releaseEnergyBall();
        auto e_ball_1 = world->getEnergyBall(0); // Bola de transm1
        auto e_ball_2 = world->getEnergyBall(1); // Bola de transm2

        // Verifico bola 1 esta a la izquierda de la bola 2
        CPPUNIT_ASSERT(e_ball_1->getX() < e_ball_2->getX());

        int n_bodies = world->getWorld()->GetBodyCount();
        bool balls_ignored = false;
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step();
            // Verifico que una bola paso a la otra
            // IMPORTANTE: primero compruebo n_bodies para asegurarme que no fueron eliminados
            if ((n_bodies == world->getWorld()->GetBodyCount()) &&
            (e_ball_1->getX() > e_ball_2->getX()))
                    balls_ignored = true;
        }

        CPPUNIT_ASSERT(balls_ignored);
        cout << "OK";
    }

    void testContactWithEnergyBarrier() {
        cout << endl << "TEST ignorar contacto con barrera energia: ";
        float barrier_x = e_transm_x + 4 * ENRG_BALL_RADIUS + BARRIER_HALF_WIDTH + 2;
        float barrier_y = BARRIER_HALF_LENGTH;
        // Creo transmisores en sentido opuesto para que choquen bolas energia
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        world->createEnergyBarrier(barrier_x, barrier_y, O_V);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBall(0); // Bola de transm1

        int n_bodies = world->getWorld()->GetBodyCount();
        bool barrier_ignored = false;
        for (int i = 0; i < 2 * STEP_ITERATIONS; ++i) {
            world->step();
            // Verifico que bola paso la barrera
            // IMPORTANTE: primero compruebo n_bodies para asegurarme que no fueron eliminados
            if ((n_bodies == world->getWorld()->GetBodyCount()) &&
            (e_ball->getX() > barrier_x))
                barrier_ignored = true;
        }

        CPPUNIT_ASSERT(barrier_ignored);
        cout << "OK";
    }

    void testContactWithOpenGate() {
        cout << endl << "TEST ignorar contacto con compuerta abierta: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBall(0); // Bola de transm1

        world->createButton(100, 100); // Boton para abrir gate
        auto button  = world->getButton(0);
        button->activate(); // Activo boton

        float gate_x = e_ball->getX() + ENRG_BALL_RADIUS + GATE_HALF_WIDTH + 2;
        float gate_y = GATE_HALF_HEIGHT;
        world->createGate(gate_x, gate_y, {0}, {});
        auto gate = world->getGate(0);

        int n_bodies = world->getWorld()->GetBodyCount();
        bool gate_ignored = false;

        for (int i = 0; i < 2 * STEP_ITERATIONS; ++i) {
            world->step();
            // Verifico que bola paso la compuerta
            // IMPORTANTE: primero compruebo n_bodies para asegurarme que no fueron eliminados
            if ((n_bodies == world->getWorld()->GetBodyCount()) && (e_ball->getX() > gate_x))
                gate_ignored = true;
        }

        CPPUNIT_ASSERT(gate->isOpen());
        CPPUNIT_ASSERT(gate_ignored);
        cout << "OK";
    }


    void testContactWithClosedGate() {
        cout << endl << "TEST destruir al chocar con compuerta cerrada: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBall(0); // Bola de transm1
        world->createButton(100, 100); // Boton para abrir gate

        float gate_x = e_ball->getX() + ENRG_BALL_RADIUS + GATE_HALF_WIDTH + 2;
        float gate_y = GATE_HALF_HEIGHT;
        world->createGate(gate_x, gate_y, {0}, {});
        auto gate = world->getGate(0);

        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < 2 * STEP_ITERATIONS; ++i)
            world->step();

        CPPUNIT_ASSERT(!gate->isOpen());
        CPPUNIT_ASSERT(!world->getEnergyBall(0));
        CPPUNIT_ASSERT_LESS(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testAddedToUpdateVectorAfterMoving () {
        cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                        "movimiento: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        CPPUNIT_ASSERT(world->getObjectsToUpdate().empty());
        releaseEnergyBall();
        world->step();
        // EnergyBall ahora se esta moviendo
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getObjectsToUpdate().size());
        // Verifico no se lo agrego a vector de elementos a eliminar
        CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
        // Verifico energ ball correcta
        auto update_e_ball = (EnergyBall*) world->getObjectsToUpdate().at(0);
        CPPUNIT_ASSERT_EQUAL(e_transm_y, update_e_ball->getY());
        CPPUNIT_ASSERT_EQUAL((size_t) 0, update_e_ball->getId());
        cout << "OK";
    }

    void testAddedToDeleteVectorAfterDead () {
        cout << endl << "TEST verificar que se agrega a vector de objetos a eliminar luego de "
                        "morir: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);
        float rock_x = energy_ball->getX() + ENRG_BALL_RADIUS + ROCK_HALF_LEN + 1;
        float rock_y = energy_ball->getY();
        world->createRockBlock(100, 4, 0, -2); // Superficie donde apoyar roca
        // Creo roca donde colisionar la bola
        world->createRock(rock_x, rock_y);

        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step();
            if (world->getObjectsToDelete().size() == 1) {  // Se elimino bola energia
                // Verifico no se lo agrego a vector de elementos a actualizar
                CPPUNIT_ASSERT(world->getObjectsToUpdate().empty());
                // Verifico energy ball correcta (id y classId)
                auto delete_ball_data = world->getObjectsToDelete().at(0);
                CPPUNIT_ASSERT_EQUAL((size_t) 0, delete_ball_data.first);
                CPPUNIT_ASSERT_EQUAL(ENERGY_BALL, delete_ball_data.second);
            }
        }
        CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
        cout << "OK";
    }

    void testContactWithMetalBlockFromLeft() {
        cout << endl << "TEST rebotar en bloque metal, cara izquierda: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        world->createMetalBlock(4, 4, (e_transm_x + 15), 2);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);
        auto last_x = energy_ball->getX();
        bool bounced = false;
        for (int i = 0; i < 2 * STEP_ITERATIONS; ++i) {
            world->step();
            energy_ball = world->getEnergyBall(0);  // Verifico que no colision y fue destruida
            if (energy_ball) {
                if (last_x > energy_ball->getX())   // Si x mayor a la actual, reboto
                    bounced = true;
                last_x = energy_ball->getX();   // Actualizo ultima posicion
            }
        }
        CPPUNIT_ASSERT(bounced);
        cout << "OK";
    }

    void testContactWithMetalBlockFromRight() {
        cout << endl << "TEST rebotar en bloque metal, cara derecha: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_O);
        world->createMetalBlock(4, 4, (e_transm_x - 15), 2);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);
        auto last_x = energy_ball->getX();
        bool bounced = false;
        for (int i = 0; i < 2 * STEP_ITERATIONS; ++i) {
            world->step();
            energy_ball = world->getEnergyBall(0);  // Verifico que no colision y fue destruida
            if (energy_ball) {
                if (last_x < energy_ball->getX())  // Si x menor a la actual, reboto
                    bounced = true;
                last_x = energy_ball->getX();   // Actualizo ultima posicion
            }
        }
        CPPUNIT_ASSERT(bounced);
        cout << "OK";
    }

    void testContactWithMetalBlockFromAbove() {
        cout << endl << "TEST rebotar en bloque metal, cara superior: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        world->createMetalBlock(4, 4, (e_transm_x), (e_transm_y - 15));
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);
        auto last_y = energy_ball->getY();
        bool bounced = false;
        for (int i = 0; i < 2 * STEP_ITERATIONS; ++i) {
            world->step();
            energy_ball = world->getEnergyBall(0);  // Verifico que no colision y fue destruida
            if (energy_ball) {
                if (last_y < energy_ball->getY())  // Si y menor a la actual, reboto
                    bounced = true;
                last_y = energy_ball->getY();   // Actualizo ultima posicion
            }
        }
        CPPUNIT_ASSERT(bounced);
        cout << "OK";
    }

    void testContactWithMetalBlockFromBelow() {
        cout << endl << "TEST rebotar en bloque metal, cara inferior: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_N);
        world->createMetalBlock(4, 4, (e_transm_x), (e_transm_y + 15));
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);
        auto last_y = energy_ball->getY();
        bool bounced = false;
        for (int i = 0; i < 2 * STEP_ITERATIONS; ++i) {
            world->step();
            energy_ball = world->getEnergyBall(0);  // Verifico que no colision y fue destruida
            if (energy_ball) {
                if (last_y > energy_ball->getY())  // Si y mayor a la actual, reboto
                    bounced = true;
                last_y = energy_ball->getY();   // Actualizo ultima posicion
            }
        }
        CPPUNIT_ASSERT(bounced);
        cout << "OK";
    }


// todo: test rebote con todos los bloques diagonal


//    void testContactWithMetalDiagonalBlockNEFromLeft() {
//        cout << endl << "TEST rebotar en bloque diagonal metal NE, cara derecha: ";
//        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
//        world->createMetalDiagonalBlock(4, 4, (e_transm_x + 15), 0, O_NO);
//        releaseEnergyBall();
//        auto energy_ball = world->getEnergyBall(0);
////        auto last_x = energy_ball->getX();
////        bool bounced = false;
//        for (int i = 0; i < 2 * STEP_ITERATIONS; ++i) {
//            world->step();
//            energy_ball = world->getEnergyBall(0);  // Verifico que no colision y fue destruida
//            std::cout << "y: "<<energy_ball->getY() << " x: "<<energy_ball->getX()<<endl;
//
////            if (energy_ball) {
////                if (last_x > energy_ball->getX())   // Si x mayor a la actual, reboto
////                    bounced = true;
////                last_x = energy_ball->getX();   // Actualizo ultima posicion
////            }
//        }
////        CPPUNIT_ASSERT(bounced);
//        cout << "OK";
//    }
};


#endif //PORTAL_TESTENERGYBALL_H
