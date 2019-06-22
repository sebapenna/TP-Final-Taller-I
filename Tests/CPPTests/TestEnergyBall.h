#ifndef PORTAL_TESTENERGYBALL_H
#define PORTAL_TESTENERGYBALL_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <string>

using std::cout;
using std::endl;
using std::make_shared;

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
    std::shared_ptr<Configuration> ptr;
    Configuration *config;
    World *world;
    size_t width = 100, height = 200;
    float e_transm_x = 0, e_transm_y = 2;

public:
    void setUp() override {
        ptr = make_shared<Configuration>();
config = ptr.get();
        world = new World(width, height, ptr);
    }

    void tearDown() override {
        delete world;
    }

    void releaseEnergyBall() {
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < config->getFps(); ++i)
                world->step();
        for (int i = 0; i < config->getFps(); ++i)
            world->step(); // Step donde se crea EnergyBall
    }

    void testContactWithRockBlock() {
        cout << endl << endl << "TEST ENERGY BALL";
        cout << endl << "TEST eliminar al contacto con bloque roca: ";
        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);

        float wall_width = 4, wall_height = 10;
        float wall_x = energy_ball->x() + ENRG_BALL_RADIUS + wall_width;
        float wall_y = wall_height / 2;
        // Creo pared donde colisionar la bola
        auto data1 = make_shared<RockBlockData>(wall_width, wall_height, wall_x, wall_y);
        world->createCollidable(data1);

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        int n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < config->getFps(); ++i) {
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

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "S");
        world->createCollidable(data);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);

        float acid_x = energy_ball->x();
        float acid_y = energy_ball->y() - ENRG_BALL_RADIUS - ACID_HALF_HEIGHT - 1;

        // Creo acido donde colisionar la bola
        auto data1 = make_shared<AcidData>(acid_x, acid_y, 4);
        world->createCollidable(data1);
        int n_bodies = world->getWorld()->GetBodyCount();

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < config->getFps(); ++i) {
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
        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "S");
        world->createCollidable(data);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);

        float button_x = energy_ball->x();
        float button_y = energy_ball->y() - ENRG_BALL_RADIUS - BUTTON_HALF_HEIGHT - 1;

        // Creo boton donde colisionar la bola
        auto data1 = make_shared<ButtonData>(0, button_x, button_y);
        world->createCollidable(data1);
        int n_bodies = world->getWorld()->GetBodyCount();

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < config->getFps(); ++i) {
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

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "S");
        world->createCollidable(data);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);

        float rock_x = energy_ball->x();
        float rock_y = energy_ball->y() - ENRG_BALL_RADIUS - ROCK_HALF_LEN - 1;

        // Creo roca donde colisionar la bola
        auto data1 = make_shared<RockData>(rock_x, rock_y);
        world->createCollidable(data1);
        int n_bodies = world->getWorld()->GetBodyCount();

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < config->getFps(); ++i) {
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

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "S");
        world->createCollidable(data);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBall(0);

        float e_transm_2_x = e_ball->x();
        float e_transm_2_y = e_ball->y() - ENRG_BALL_RADIUS - ENRG_BLOCK_HALF_LEN- 1;

        // Creo tranmisor donde colisionar la bola
        auto data2 = make_shared<EnergyTransmitterData>(e_transm_2_x, e_transm_2_y, "E");
        world->createCollidable(data2);
        int n_bodies = world->getWorld()->GetBodyCount();

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < config->getFps(); ++i) {
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

        auto data = make_shared<RockBlockData>(100, 4, 0, -2); // Piso
        world->createCollidable(data);
        auto data1 = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data1);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);

        float chell_x = energy_ball->x() + ENRG_BALL_RADIUS + CHELL_HALF_WIDTH + 1;
        float chell_y = energy_ball->y();

        // Creo chell donde colisionar la bola
        auto data2 = make_shared<ChellData>(0, chell_x, chell_y);
        world->createCollidable(data2);
        int n_bodies = world->getWorld()->GetBodyCount();

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < config->getFps(); ++i) {
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
        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        auto data1 = make_shared<EnergyTransmitterData>(e_transm_2_x, e_transm_2_y, "O");
        world->createCollidable(data1);
        releaseEnergyBall();
        auto e_ball_1 = world->getEnergyBall(0); // Bola de transm1
        auto e_ball_2 = world->getEnergyBall(1); // Bola de transm2

        // Verifico bola 1 esta a la izquierda de la bola 2
        CPPUNIT_ASSERT(e_ball_1->x() < e_ball_2->x());

        int n_bodies = world->getWorld()->GetBodyCount();
        bool balls_ignored = false;
        for (int i = 0; i < config->getFps(); ++i) {
            world->step();
            // Verifico que una bola paso a la otra
            // IMPORTANTE: primero compruebo n_bodies para asegurarme que no fueron eliminados
            if ((n_bodies == world->getWorld()->GetBodyCount()) &&
            (e_ball_1->x() > e_ball_2->x()))
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
        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        auto data1 = make_shared<EnergyBarrierData>(barrier_x, barrier_y, "V");
        world->createCollidable(data1);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBall(0); // Bola de transm1

        int n_bodies = world->getWorld()->GetBodyCount();
        bool barrier_ignored = false;
        for (int i = 0; i < 2 * config->getFps(); ++i) {
            world->step();
            // Verifico que bola paso la barrera
            // IMPORTANTE: primero compruebo n_bodies para asegurarme que no fueron eliminados
            if ((n_bodies == world->getWorld()->GetBodyCount()) &&
            (e_ball->x() > barrier_x))
                barrier_ignored = true;
        }

        CPPUNIT_ASSERT(barrier_ignored);
        cout << "OK";
    }

    void testContactWithOpenGate() {
        cout << endl << "TEST ignorar contacto con compuerta abierta: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBall(0); // Bola de transm1

        auto data1 = make_shared<ButtonData>(0, 100, 100);
        world->createCollidable(data1); // Boton para abrir gate
        auto button  = world->getButton(0);
        button->activate(); // Activo boton

        float gate_x = e_ball->x() + ENRG_BALL_RADIUS + GATE_HALF_WIDTH + 2;
        float gate_y = GATE_HALF_HEIGHT;
        auto data2 = make_shared<GateData>(0, gate_x, gate_y);
        data2->addButtonNeeded(0);
        world->createCollidable(data2);

        auto gate = world->getGate(0);

        int n_bodies = world->getWorld()->GetBodyCount();
        bool gate_ignored = false;

        for (int i = 0; i < 2 * config->getFps(); ++i) {
            world->step();
            // Verifico que bola paso la compuerta
            // IMPORTANTE: primero compruebo n_bodies para asegurarme que no fueron eliminados
            if ((n_bodies == world->getWorld()->GetBodyCount()) && (e_ball->x() > gate_x))
                gate_ignored = true;
        }

        CPPUNIT_ASSERT(gate->isOpen());
        CPPUNIT_ASSERT(gate_ignored);
        cout << "OK";
    }


    void testContactWithClosedGate() {
        cout << endl << "TEST destruir al chocar con compuerta cerrada: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBall(0); // Bola de transm1
        auto data1 = make_shared<ButtonData>(0, 100, 100);
        world->createCollidable(data1); // Boton para abrir gate
        auto button  = world->getButton(0);
        button->activate(); // Activo boton

        float gate_x = e_ball->x() + ENRG_BALL_RADIUS + GATE_HALF_WIDTH + 2;
        float gate_y = GATE_HALF_HEIGHT;
        auto data2 = make_shared<GateData>(0, gate_x, gate_y);
        world->createCollidable(data2);
        data2->addButtonNeeded(0);
        auto gate = world->getGate(0);

        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < 2 * config->getFps(); ++i)
            world->step();

        CPPUNIT_ASSERT(!gate->isOpen());
        CPPUNIT_ASSERT(!world->getEnergyBall(0));
        CPPUNIT_ASSERT_LESS(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testAddedToUpdateVectorAfterMoving () {
        cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                        "movimiento: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        CPPUNIT_ASSERT(world->getObjectsToUpdate().empty());
        releaseEnergyBall();
        world->step();
        // EnergyBall ahora se esta moviendo
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getObjectsToUpdate().size());
        // Verifico no se lo agrego a vector de elementos a eliminar
        CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
        // Verifico energ ball correcta
        auto update_e_ball = (EnergyBall*) world->getObjectsToUpdate().at(0);
        CPPUNIT_ASSERT_EQUAL(e_transm_y, update_e_ball->y());
        CPPUNIT_ASSERT_EQUAL((size_t) 0, update_e_ball->id());
        cout << "OK";
    }

    void testAddedToDeleteVectorAfterDead () {
        cout << endl << "TEST verificar que se agrega a vector de objetos a eliminar luego de "
                        "morir: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);
        float rock_x = energy_ball->x() + ENRG_BALL_RADIUS + ROCK_HALF_LEN + 1;
        float rock_y = energy_ball->y();
        auto data1 = make_shared<RockBlockData>(100, 4, 0, -2);
        world->createCollidable(data1); // Superficie donde apoyar roca
        // Creo roca donde colisionar la bola
        auto data2 = make_shared<RockData>(rock_x, rock_y);
        world->createCollidable(data2);

        for (int i = 0; i < config->getFps(); ++i) {
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
        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        auto data1 = make_shared<MetalBlockData>(4, 4, (e_transm_x + 15), 2);
        world->createCollidable(data1);

        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);
        auto last_x = energy_ball->x();
        bool bounced = false;
        for (int i = 0; i < 2 * config->getFps(); ++i) {
            world->step();
            energy_ball = world->getEnergyBall(0);  // Verifico que no colision y fue destruida
            if (energy_ball) {
                if (last_x > energy_ball->x())   // Si x mayor a la actual, reboto
                    bounced = true;
                last_x = energy_ball->x();   // Actualizo ultima posicion
            }
        }
        CPPUNIT_ASSERT(bounced);
        cout << "OK";
    }

    void testContactWithMetalBlockFromRight() {
        cout << endl << "TEST rebotar en bloque metal, cara derecha: ";
        auto data1 = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "O");
        world->createCollidable(data1);

        auto data2 = make_shared<MetalBlockData>(4, 4, (e_transm_x - 15), 2);
        world->createCollidable(data2);

        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);
        auto last_x = energy_ball->x();
        bool bounced = false;
        for (int i = 0; i < 2 * config->getFps(); ++i) {
            world->step();
            energy_ball = world->getEnergyBall(0);  // Verifico que no colision y fue destruida
            if (energy_ball) {
                if (last_x < energy_ball->x())  // Si x menor a la actual, reboto
                    bounced = true;
                last_x = energy_ball->x();   // Actualizo ultima posicion
            }
        }
        CPPUNIT_ASSERT(bounced);
        cout << "OK";
    }

    void testContactWithMetalBlockFromAbove() {
        cout << endl << "TEST rebotar en bloque metal, cara superior: ";
        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "S");
        world->createCollidable(data);
        auto data1 = make_shared<MetalBlockData>(4, 4, e_transm_x, (e_transm_y - 15));
        world->createCollidable(data1);

        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);
        auto last_y = energy_ball->y();
        bool bounced = false;
        for (int i = 0; i < 2 * config->getFps(); ++i) {
            world->step();
            energy_ball = world->getEnergyBall(0);  // Verifico que no colision y fue destruida
            if (energy_ball) {
                if (last_y < energy_ball->y())  // Si y menor a la actual, reboto
                    bounced = true;
                last_y = energy_ball->y();   // Actualizo ultima posicion
            }
        }
        CPPUNIT_ASSERT(bounced);
        cout << "OK";
    }

    void testContactWithMetalBlockFromBelow() {
        cout << endl << "TEST rebotar en bloque metal, cara inferior: ";
        auto data1 = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "N");
        world->createCollidable(data1);

        auto data2 = make_shared<MetalBlockData>(4, 4, e_transm_x, (e_transm_y + 15));
        world->createCollidable(data2);

        releaseEnergyBall();
        auto energy_ball = world->getEnergyBall(0);
        auto last_y = energy_ball->y();
        bool bounced = false;
        for (int i = 0; i < 2 * config->getFps(); ++i) {
            world->step();
            energy_ball = world->getEnergyBall(0);  // Verifico que no colision y fue destruida
            if (energy_ball) {
                if (last_y > energy_ball->y())  // Si y mayor a la actual, reboto
                    bounced = true;
                last_y = energy_ball->y();   // Actualizo ultima posicion
            }
        }
        CPPUNIT_ASSERT(bounced);
        cout << "OK";
    }


// todo: test rebote con todos los bloques diagonal


//    void testContactWithMetalDiagonalBlockNEFromLeft() {
//        cout << endl << "TEST rebotar en bloque diagonal metal NE, cara derecha: ";
//        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
//        world->createCollidable(data);
//        world->createMetalDiagonalBlock(4, 4, (e_transm_x + 15), 0, O_NO);
//        releaseEnergyBall();
//        auto energy_ball = world->getEnergyBall(0);
////        auto last_x = energy_ball->x();
////        bool bounced = false;
//        for (int i = 0; i < 2 * config->getFps(); ++i) {
//            world->step();
//            energy_ball = world->getEnergyBall(0);  // Verifico que no colision y fue destruida
//            std::cout << "y: "<<energy_ball->y() << " x: "<<energy_ball->x()<<endl;
//
////            if (energy_ball) {
////                if (last_x > energy_ball->x())   // Si x mayor a la actual, reboto
////                    bounced = true;
////                last_x = energy_ball->x();   // Actualizo ultima posicion
////            }
//        }
////        CPPUNIT_ASSERT(bounced);
//        cout << "OK";
//    }
};


#endif //PORTAL_TESTENERGYBALL_H
