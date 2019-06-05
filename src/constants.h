#ifndef TP_FINAL_CONSTANTES_H
#define TP_FINAL_CONSTANTES_H

#include <cstdint>


/*
 *  IMPORTANTE
 *
 *  TODAS LOS ANCHOS Y ALTOS SON DE MEDIO CUERPO
 *
 * */

// todo: CONFIGURACIONES A UN YAML

/* Orientaciones cara diagonal bloque metal diagonal */
#define O_NE    (uint8_t) 0 /* Noreste*/
#define O_NO    (uint8_t) 1 /* Noroeste*/
#define O_SE    (uint8_t) 2 /* Sureste */
#define O_SO    (uint8_t) 3 /* Suroeste */

/* Direcciones */
#define O_N  (uint8_t) 4    /* Norte */
#define O_S   (uint8_t) 5 /* Sur */
#define O_E (uint8_t) 6 /* Este */
#define O_O (uint8_t) 7 /* Oeste */
#define O_V (uint8_t) 8 /* Vertical */
#define O_H (uint8_t) 9 /* Horizontal */

/* Box2D */
#define GRAVITY_X   0.0f
#define GRAVITY_Y   -10.0f
#define TIME_STEP   (float32) (1.0f / 30.0f)
#define VELOCITY_ITERATIONS 8
#define POSTION_ITERATIONS  3
#define STEP_ITERATIONS (1 / TIME_STEP)

/* Movimiento */
#define MOVE_FORCE  100
#define MOVE_LEFT   (uint8) 0
#define MOVE_RIGHT  (uint8) 1
#define MOVE_STOP   (uint8) 2
#define JUMPED (uint8) 0
#define ON_GROUND (uint8)   1
#define FALLING (uint8)  2
#define DELTA_Y_VEL 0.001    // Error de velocidad por caida de cuerpos al suelo
#define DELTA_POS   (float) 0.02    // Error posicion (x e y)

/* Configuracion Chell */
#define CHELL_HALF_WIDTH  2
#define CHELL_HALF_HEIGHT  2
#define CHELL_DENSITY   1

/* Coniguracion Rock */
#define ROCK_HALF_WIDTH  2
#define ROCK_HALF_HEIGHT  2
#define ROCK_DENSITY    1

/* Coniguracion Acid */
#define ACID_HALF_WIDTH  2
#define ACID_HALF_HEIGHT  0.5
#define ACID_FRICTION    100    // Cuerpo se frene en acido

/* Configuracion Button */
#define BUTTON_HALF_WIDTH  2
#define BUTTON_HALF_HEIGHT  0.5
#define BUTTON_FRICTION    0

#define ACTIVATED (uint8_t) 0
#define NOT_ACTIVATED   (uint8_t) 1

/* Configuracion Gate */
#define GATE_HALF_WIDTH  2
#define GATE_HALF_HEIGHT  4
#define GATE_FRICTION    0

/* Configuracion Energy Receiver */
#define ENRG_RECV_HALF_WIDTH  2
#define ENRG_RECV_HALF_HEIGHT  2
#define ENRG_RECV_FRICTION    0

/* Configuracion Energy Transmitter */
#define ENRG_TRANSM_HALF_WIDTH  2
#define ENRG_TRANSM_HALF_HEIGHT  2
#define ENRG_TRANSM_FRICTION    0
#define TIME_TO_RELEASE 10

/* Configuracion Energy Ball */
#define ENRG_BALL_RADIUS    2
#define ENRG_BALL_DENSITY    1
#define ENRG_BALL_FORCE 100
#define ENERGY_BALL_MAX_LIFETIME 5

/* Configuracion Bloques */
#define BLOCK_FRICTION  0
#define BLOCK_DENSITY   1

/* Configuracion Energy Barrier */
#define BARRIER_HALF_LENGTH  4
#define BARRIER_HALF_WIDTH   1

/* Class Names*/
#define ENERGY_RECEIVER "EnergyReceiver"
#define ENERGY_TRANSMITTER "EnergyTranmistter"
#define METAL_BLOCK "MetalBlock"
#define METAL_DIAGONAL_BLOCK "MetalDiagonalBlock"
#define ROCK_BLOCK "RockBlock"
#define BUTTON "Button"
#define GATE "Gate"
#define ROCK "Rock"
#define ACID    "Acid"
#define ENERGY_BARRIER "EnergyBarrier"
#define CHELL   "Chell"
#define ENERGY_BALL "EnergyBall"
#define PORTAL_RAY  "PortalRay"
#define PORTAL  "Portal"
#define PIN_TOOL_RAY    "PinToolRay"
#define PIN_TOOL    "PinTool"
#define CAKE    "Cake"

/* Path YAML */
//#ifdef DEBUG_MODE
//    #define YAML_TEST_PATH "./"
//#elif
//#define YAML_TEST_PATH "/etc/portal/"
//#endif
// gcc -DDEBUG_MODE
#define YAML_TEST_PATH "/home/seba/Escritorio/Portal/Tests/"
#define YAML_PATH   "/home/seba/Escritorio/Portal/src/"

#endif //TP_FINAL_CONSTANTES_H
