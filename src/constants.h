#ifndef TP_FINAL_CONSTANTES_H
#define TP_FINAL_CONSTANTES_H

#include <cstdint>

/* Orientaciones cara diagonal bloque metal diagonal */
#define O_NE    (uint8_t) 0 /* Noreste*/

#define O_NO    (uint8_t) 1 /* Noroeste*/

#define O_SE    (uint8_t) 2 /* Sureste */

#define O_SO    (uint8_t) 3 /* Suroeste */

/* Direcciones */
#define O_N  (uint8_t) 6    /* Norte */

#define O_S   (uint8_t) 7 /* Sur */

#define O_O (uint8_t) 8 /* Oeste */

#define O_E (uint8_t) 9 /* Este */

/* Box2D */
#define GRAVITY_X   0.0f
#define GRAVITY_Y   -10.0f
#define TIME_STEP   (float32) (1.0f / 30.0f)
#define VELOCITY_ITERATIONS 8
#define POSTION_ITERATIONS  3
#define STEP_ITERATIONS (1 / TIME_STEP)

/* Movimiento */
#define MOVE_FORCE  50
#define MOVE_LEFT   (uint8) 0
#define MOVE_RIGHT  (uint8) 1
#define MOVE_STOP   (uint8) 2
#define JUMPING (uint8) 0
#define FALLING (uint8)  1
#define ON_GROUND (uint8)   2
#define DELTA_Y_VEL 0.001    // Error de velocidad por caida de cuerpos al suelo
#define DELTA_POS   (float) 0.02    // Error posicion (x e y)

/* Configuracion Chell */
#define CHELL_WIDTH  2
#define CHELL_HEIGHT  2
#define CHELL_DENSITY   1

/* Configuracion Bloques */
#define BLOCK_FRICTION  0
#define BLOCK_DENSITY   1

#endif //TP_FINAL_CONSTANTES_H
