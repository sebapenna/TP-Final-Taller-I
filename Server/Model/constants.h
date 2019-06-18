#ifndef TP_FINAL_CONSTANTES_H
#define TP_FINAL_CONSTANTES_H

#include <cstdint>
#include <Common/ProtocolTranslator/protocol_macros.h>

/*
 *  IMPORTANTE
 *
 *  TODAS LOS ANCHOS Y ALTOS SON DE MEDIO CUERPO
 *
 * */

/* Orientaciones cara diagonal bloque metal diagonal */
#define O_NE    (uint8_t) NORTH_EAST
#define O_NO    (uint8_t) NORTH_WEST
#define O_SE    (uint8_t) SOUTH_EAST
#define O_SO    (uint8_t) SOUTH_WEST

/* Direcciones */
#define O_N  (uint8_t) NORTH
#define O_S   (uint8_t) SOUTH
#define O_E (uint8_t) EAST
#define O_O (uint8_t) WEST
#define O_V (uint8_t) 8
#define O_H (uint8_t) 9

/* Box2D */
#define GRAVITY_X   0.0f
#define GRAVITY_Y   -10.0f
#define TIME_STEP   (float) (1.0f / 30.0f)
#define VELOCITY_ITERATIONS 8
#define POSTION_ITERATIONS  3
#define STEP_ITERATIONS (1 / TIME_STEP)

/* Movimiento */
#define MOVE_FORCE  1500
#define JUMP_FORCE  /*1250*/2000
#define MOVE_LEFT   (uint8) 0
#define MOVE_RIGHT  (uint8) 1
#define MOVE_STOP   (uint8) 2
#define JUMPED (uint8) 0
#define ON_GROUND (uint8)   1
#define FALLING (uint8)  2
#define DELTA_VEL 0.001    // Error de velocidad en movimiento de cuerpos
#define DELTA_POS   (float) 0.02    // Error posicion (x e y)

#define HALF_BOX_LEN 2

/* Configuracion Chell */
#define CHELL_HALF_WIDTH  HALF_BOX_LEN
#define CHELL_HALF_HEIGHT  HALF_BOX_LEN
#define CHELL_DENSITY   5
#define CHELL_GRAVITY_SCALE 5

/* Coniguracion Rock */
#define ROCK_HALF_LEN  2    // Largo de medio lado de la roca (cuerpo cuadrado)
#define ROCK_DENSITY    1000000

/* Coniguracion Acid */
#define ACID_HALF_WIDTH  HALF_BOX_LEN
#define ACID_HALF_HEIGHT  1
#define ACID_FRICTION    100    // Cuerpo se frene en acido

/* Configuracion Button */
#define BUTTON_HALF_WIDTH  HALF_BOX_LEN
#define BUTTON_HALF_HEIGHT  1
#define BUTTON_FRICTION    0

#define NOT_ACTIVATED   (uint8_t) 0
#define ACTIVATED (uint8_t) 1

/* Configuracion Gate */
#define GATE_HALF_WIDTH  HALF_BOX_LEN
#define GATE_HALF_HEIGHT  (2 * GATE_HALF_WIDTH)
#define GATE_FRICTION    0

/* Configuracion Energy Receiver y Energy Transmitter */
#define ENRG_BLOCK_HALF_LEN  HALF_BOX_LEN // Largo de medio lado del recvr/transmitter (cuerpos cuadrados)
#define ENRG_BLOCK_FRICTION    0
#define TIME_TO_RELEASE 10  // Tiempo tras que libera bola energia el transmisor

/* Configuracion Energy Ball */
#define ENRG_BALL_RADIUS    HALF_BOX_LEN
#define ENRG_BALL_DENSITY    1
#define ENRG_BALL_FORCE 100
#define ENERGY_BALL_MAX_LIFETIME 5

/* Configuracion Bloques */
#define METAL_DIAG_BLOC_FRICTION    100
#define BLOCK_FRICTION  0
#define BLOCK_DENSITY   1

/* Configuracion Energy Barrier */
#define BARRIER_HALF_LENGTH  4
#define BARRIER_HALF_WIDTH   1
#define BARRIER_FRICTION    0

/* Configuracion Cake */
#define CAKE_HALF_LEN   2
#define CAKE_FRICTION   0

/* Class Names*/
#define ENERGY_RECEIVER (uint8_t) 0
#define ENERGY_TRANSMITTER (uint8_t) 1
#define METAL_BLOCK (uint8_t) 2
#define METAL_DIAGONAL_BLOCK (uint8_t) 3
#define ROCK_BLOCK (uint8_t) 4
#define BUTTON (uint8_t) 5
#define GATE (uint8_t) 6
#define ROCK (uint8_t) 7
#define ACID    (uint8_t) 8
#define ENERGY_BARRIER (uint8_t) 9
#define CHELL   (uint8_t) 10
#define ENERGY_BALL (uint8_t) 11
#define PORTAL_RAY  (uint8_t) 12
#define PORTAL  (uint8_t) 13
#define PIN_TOOL_RAY    (uint8_t) 14
#define PIN_TOOL    (uint8_t) 15
#define CAKE    (uint8_t) 16

#endif //TP_FINAL_CONSTANTES_H
