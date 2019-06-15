#include <iostream>
#include <algorithm>
#include <vector>
#include "HandshakeHandler.h"


#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define SUCCESS  (uint8_t) 1
#define ERROR   (uint8_t) 0

#define CREATE_GAME  (uint8_t) 0
#define JOIN_GAME    (uint8_t) 1

#define MAX_PLAYERS_IN_GAME 4

#define WELCOME_MSG "Bienvenido a Portal. Ingrese 0 para crear una nueva partida o 1 para unirse "\
"a una ya existente:\n"

#define WRONG_OPTION_MSG    "Opcion incorrecta. Intentelo de nuevo.\n"

#define SELECT_PLAYERS_MSG  "Ingrese la cantidad máxima de jugadores para su partida. El valor "\
"máximo posible es " STR(MAX_PLAYERS_IN_GAME) STR(.\n)

#define SELECT_MAP_MSG "Ingrese la opción de mapa deseada siendo:\n\t-0: Espacio;\n"

#define SPACE_ID (uint8_t) 0   // todo: nombres mapas / CREAR MAPAS
#define SPACE "space.yaml"

#define CITY_ID (uint8_t) 1
#define CITY "city.yaml"

#define WOODS_ID (uint8_t) 2
#define WOODS "woods.yaml"

#define MAP_IDS SPACE_ID, CITY_ID, WOODS_ID // Listado de todos los ids

#define REFRESH (uint8_t)   0

using std::ref;

void errorLoop(Protocol &connection, uint8_t &player_choice) {
    connection << ERROR;
    connection << WRONG_OPTION_MSG;
    connection >> player_choice;
}

std::pair<size_t, std::string> HandshakeHandler::createGame(Protocol &connection) {
    connection << SELECT_PLAYERS_MSG;   // Envio mensaje seleccion jugadores

    uint8_t max_players, map_choice;
    connection >> max_players;
    while (max_players > MAX_PLAYERS_IN_GAME) // Seleccion cantidad maxima de jugadores
        errorLoop(ref(connection), max_players);
    connection << SUCCESS;

    connection << SELECT_MAP_MSG;  // Envio mensaje seleccion mapa
    connection >> map_choice;
    std::vector<uint8_t > map_ids = {MAP_IDS};
    while (std::find(map_ids.begin(), map_ids.end(), map_choice) == map_ids.end()) // Seleccion mapa
        errorLoop(ref(connection), map_choice);
    connection << SUCCESS;

    std::string map_name;
    switch (map_choice) {
        case SPACE_ID:
            map_name.append(SPACE);
            break;
        case CITY_ID:
            map_name.append(CITY);
            break;
        case WOODS_ID:
            map_name.append(WOODS);
            break;
        default:
            break;
    }

    return std::move(std::make_pair(max_players, map_name));
}

uint8_t HandshakeHandler::getPlayerChoice(Protocol &connection) {
    connection << WELCOME_MSG;  // Mensaje bienvenida

    uint8_t player_choice;
    connection >> player_choice;    // Obtengo elecccion jugador

    while (player_choice != CREATE_GAME && player_choice != JOIN_GAME)     // Comando incorrecto
        errorLoop(ref(connection), player_choice);
    connection << SUCCESS; // Comando correcto

    return player_choice;
}

size_t HandshakeHandler::joinGame(Protocol &connection) {
    // todo : join game
    return 0;
}

void choiceLoop(Protocol &connection, uint8_t &choice) {
    std::string server_msg, str_choice; // Buffer para mensaje servidor e input
    auto server_response = ERROR;    // Inicialmente no tengo comando
    while (server_response != SUCCESS) {
        server_msg.clear(); // Limpio mensaje del servidor
        str_choice.clear(); // Limpio entrada jugador

        connection >> server_msg;
        std::cout << server_msg;
        std::cin >> str_choice; // Leo input jugador y elimino salto del linea
        str_choice.erase(remove(str_choice.begin(), str_choice.end(), '\n'), str_choice.end());
        choice = (uint8_t) std::stoi(str_choice);

        connection << choice;   // Envio eleccion
        connection >> server_response;  // Obtengo ERROR o SUCCESS
    }
}

void HandshakeHandler::getOptionsAndChoose(Protocol &connection) {
    uint8_t choice;
    choiceLoop(ref(connection), choice);    // Mensaje bienvenida y eleccion crear o unir
    if (choice == CREATE_GAME) {
        choiceLoop(ref(connection), choice);    // Selecciono maximo jugadores
        choiceLoop(ref(connection), choice);    // Selecciono mapa
        std::string server_msg;
        connection >> server_msg;
        std::cout << server_msg;    // Mensaje de como comenzar el juego
    } else {
        // todo: join game
//        connection >> server_msg;
//        std::cout << server_msg; // Mensaje de esperar a que owner comienze partida
    }
}









//
//// Hilo receptor
//void func() {
//    bool _begin_game = false;
//    Protocol prot;
//    while (!_begin_game) {
//        uint8_t server_command = -1;
//        prot >> server_command;
//        if (server_command == 0) { // 0 == Comienza el juego
//            _begin_game = true;
//        } else if (server_command == 1) {  // Notificacion del server
//            std::string msg;
//            prot >> msg;
//            std::cout << msg;
//        } else if (server_command == 2) {  // Sos nuevo owner
//            std::string msg;
//            prot >> msg;
//            std::cout << msg;
//        }
//    }
//}
//
//// Hilo que lee de entrada
//void loopChar() {
//    char c;
//    do {
//        std::cin.get(c);    // OJO ! Tenes que borrar el \n creo
//        if (c == 0) {   // Solo si  c==0 (begin), q sigue teniendo que enviar quitDTO
//            sendBeginDTO;    // Envio mensaje de comenzar partida (uint8_t)
//        }
//    } while (c != QUIT);
//    sendQuitDTO;
//}

