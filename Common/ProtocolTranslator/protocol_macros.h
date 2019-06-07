#ifndef PORTAL_PROTOCOL_MACROS_H
#define PORTAL_PROTOCOL_MACROS_H

/* Protocolo */
#define PROTOCOL_ID_POS 0 // Posicion del ID de la clase en todos los mensajes

#define NORTH_EAST  (int16_t)   0
#define NORTH_WEST  (int16_t)   1
#define SOUTH_EAST  (int16_t)   2
#define SOUTH_WEST  (int16_t)   3
#define NORTH  (int16_t)   4
#define SOUTH  (int16_t)   5
#define EAST  (int16_t)   6
#define WEST    (int16_t)   7
#define NOT_TILTED  (int16_t)   8   // Chell no inclinado

#define CLOSED   (int16_t)   0
#define OPEN    (int16_t)   1

#define NOT_PRESSED (int16_t)   0
#define PRESSED   (int16_t)   1

#define BLUE_PORTAL (int16_t) 0
#define ORANGE_PORTAL  (int16_t) 1

#define DONT_DELETE (int16_t) 0
#define DELETE  (int16_t) 1

#define NOT_JUMPING   (int16_t) 0
#define JUMPING   (int16_t) 1

#define NOT_MOVING  (int16_t)   0
#define MOVING  (int16_t)   1

#define NOT_SHOOTING    (int16_t)   0
#define SHOOTING    (int16_t)   1

#define NOT_CARRYING   (int16_t)    0
#define CARRYING    (int16_t)   1

#define PROTOCOL_MOVE_LEFT   (int16_t) 0

#define PROTOCOL_MOVE_RIGHT   (int16_t) 1

#define PROTOCOL_JUMP   (int16_t) 2

#define PROTOCOL_STOP   (int16_t) 3

#define PROTOCOL_SHOOT_PORTAL (int16_t) 4
#define SHOOT_PORTAL_COLOUR_POS 1
#define SHOOT_PORTAL_X_POS 2
#define SHOOT_PORTAL_Y_POS 3

#define PROTOCOL_SHOOT_PIN_TOOL   (int16_t) 5
#define SHOOT_PT_X_POS 1
#define SHOOT_PT_Y_POS 2

#define PROTOCOL_LIFT_ROCK  (int16_t) 6
#define LIFT_ROCK_ID_POS    1

#define PROTOCOL_DROP_ROCK  (int16_t) 7

#define PROTOCOL_ROCK_BLOCK_DATA (int16_t) 8
#define ROCK_BLOCK_X_POS  1
#define ROCK_BLOCK_Y_POS  2
#define ROCK_BLOCK_WIDTH_POS  3
#define ROCK_BLOCK_HEIGHT_POS  4

#define PROTOCOL_METAL_BLOCK_DATA    (int16_t) 9
#define METAL_BLOCK_X_POS  1
#define METAL_BLOCK_Y_POS  2
#define METAL_BLOCK_WIDTH_POS  3
#define METAL_BLOCK_HEIGHT_POS  4

#define PROTOCOL_METAL_DIAGONAL_BLOCK_DATA   (int16_t) 10
#define METAL_DIAG_BLOCK_X_POS  1
#define METAL_DIAG_BLOCK_Y_POS  2
#define METAL_DIAG_BLOCK_SIDE_LEN_POS  3
#define METAL_DIAG_BLOCK_ORIENT_POS  4

#define PROTOCOL_ENERGY_TRANSMITTER_DATA (int16_t) 11
#define ENRG_TRANSM_ID_POS  1
#define ENRG_TRANSM_X_POS  2
#define ENRG_TRANSM_Y_POS  3
#define ENRG_TRANSM_SIDE_LEN_POS  4
#define ENRG_TRANSM_DIRECTION_POS  5

#define PROTOCOL_ENERGY_RECEIVER_DATA    (int16_t) 12
#define ENRG_RECVR_ID_POS  1
#define ENRG_RECVR_X_POS  2
#define ENRG_RECVR_Y_POS  3
#define ENRG_RECVR_SIDE_LEN_POS  4

#define PROTOCOL_ACID_DATA   (int16_t) 13
#define ACID_X_POS  1
#define ACID_Y_POS  2
#define ACID_WIDTH_POS  3
#define ACID_HEIGHT_POS  4

#define PROTOCOL_BUTTON_DATA (int16_t) 14
#define BUTTON_ID_POS   1
#define BUTTON_X_POS   2
#define BUTTON_Y_POS   3
#define BUTTON_WIDTH_POS   4
#define BUTTON_HEIGHT_POS   5

#define PROTOCOL_GATE_DATA   (int16_t) 15
#define GATE_ID_POS   1
#define GATE_X_POS   2
#define GATE_Y_POS   3
#define GATE_WIDTH_POS   4
#define GATE_HEIGHT_POS   5

#define PROTOCOL_ENERGY_BARRIER_DATA (int16_t) 16
#define ENRG_BARRIER_X_POS  1
#define ENRG_BARRIER_Y_POS  2
#define ENRG_BARRIER_WIDTH_POS  3
#define ENRG_BARRIER_HEIGHT_POS  4

#define PROTOCOL_ROCK_DATA   (int16_t) 17
#define ROCK_ID_POS  1
#define ROCK_X_POS  2
#define ROCK_Y_POS  3
#define ROCK_SIDE_LEN_POS  4
#define ROCK_DELETE_STATE_POS  5

#define PROTOCOL_ENERGY_BALL_DATA    (int16_t) 18
#define ENRG_BALL_ID_POS  1
#define ENRG_BALL_X_POS  2
#define ENRG_BALL_Y_POS  3
#define ENRG_BALL_RADIUS_POS  4
#define ENRG_BALL_DELETE_STATE_POS  5

#define PROTOCOL_PORTAL_DATA (int16_t) 19
#define PORTAL_ID_POS   1
#define PORTAL_X_POS   2
#define PORTAL_Y_POS   3
#define PORTAL_WIDTH_POS   4
#define PORTAL_HEIGHT_POS   5
#define PORTAL_COLOUR_POS   6
#define PORTAL_DELETE_STATE_POS   7

#define PROTOCOL_PIN_TOOL_DATA   (int16_t) 20
#define PIN_TOOL_ID_POS   1
#define PIN_TOOL_X_POS   2
#define PIN_TOOL_Y_POS   3
#define PIN_TOOL_WIDTH_POS   4
#define PIN_TOOL_HEIGHT_POS   5
#define PIN_TOOL_DELETE_STATE_POS   6

#define PROTOCOL_CHELL_DATA  (int16_t) 21
#define CHELL_ID_POS   1
#define CHELL_X_POS   2
#define CHELL_Y_POS   3
#define CHELL_WIDTH_POS   4
#define CHELL_HEIGHT_POS   5
#define CHELL_DIRECTION_POS   6
#define CHELL_TILTED_POS   7
#define CHELL_MOVING_POS   8
#define CHELL_JUMPING_POS  9
#define CHELL_SHOOTING_POS  10
#define CHELL_CARRYING_ROCK_POS   11
#define CHELL_DELETE_STATE_POS   12

#define PROTOCOL_BUTTON_CHANGE_STATE   (int16_t) 22
#define BUTTON_CHANGE_ID_POS    1
#define BUTTON_CHANGE_STATE_POS    2

#define PROTOCOL_ENERGY_TRANSMITTER_ACTIVATE    (int16_t) 23
#define ENRG_TRANSM_ACTV_ID_POS    1

#define PROTOCOL_ENERGY_RECEIVER_ACTIVATE    (int16_t) 24
#define ENRG_RECVR_ACTV_ID_POS    1

#define PROTOCOL_GATE_CHANGE_STATE  (int16_t) 25
#define GATE_CHANGE_ID_POS    1
#define GATE_CHANGE_STATE_POS    2

#define PROTOCOL_PLAYER_CHELL_ID    (int16_t) 26
#define PLAYER_CHELL_ID_POS 1

#endif //PORTAL_PROTOCOL_MACROS_H