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

#define BLOCK_DIVISION  4

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

/* Movimiento */
#define MOVE_LEFT   (uint8) 0
#define MOVE_RIGHT  (uint8) 1
#define MOVE_STOP   (uint8) 2
#define JUMPED (uint8) 0
#define ON_GROUND (uint8)   1
#define FALLING (uint8)  2
#define DELTA_VEL 0.001    // Error de velocidad en movimiento de cuerpos
#define DELTA_POS   (float) 0.02    // Error posicion (x e y)

#define NOT_ACTIVATED   (uint8_t) 0
#define ACTIVATED (uint8_t) 1



/* Inclinacion Portal */
#define STRAIGHT    (int16_t) 0
#define LEFT    (int16_t)   1
#define RIGHT    (int16_t)   2

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
#define PORTAL  (uint8_t) 12
#define PIN_TOOL    (uint8_t) 13
#define CAKE    (uint8_t) 14

#endif //TP_FINAL_CONSTANTES_H
