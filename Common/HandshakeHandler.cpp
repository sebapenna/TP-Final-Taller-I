#include <iostream>
#include <algorithm>
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

#define HOW_TO_REFRESH_MSG "Ingrese l para actualizar listado de partidas abiertas.\n";

#define SPACE_ID (uint8_t) 0   // todo: nombres mapas / CREAR MAPAS
#define SPACE "space.yaml"

#define CITY_ID (uint8_t) 1
#define CITY "city.yaml"

#define WOODS_ID (uint8_t) 2
#define WOODS "woods.yaml"

#define REFRESH (uint8_t)   0

using std::ref;

void errorLoop(Protocol &connection, uint8_t &player_choice) {
    connection << ERROR;
    connection << WRONG_OPTION_MSG;
    connection >> player_choice;
}

std::pair<size_t, std::string> HandshakeHandler::createGame(Protocol &connection) {
    connection << SELECT_PLAYERS_MSG;

    uint8_t max_players, map_choice;
    connection >> max_players;
    while (max_players > MAX_PLAYERS_IN_GAME) // Seleccion cantidad maxima de jugadores
        errorLoop(ref(connection), max_players);
    connection << SUCCESS;

    connection << SELECT_MAP_MSG;  // Seleccion mapa
    connection >> map_choice;
    while (map_choice != SPACE_ID)
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
    auto pair = std::make_pair(max_players, map_name);
    return std::move(pair);
}

uint8_t HandshakeHandler::getPlayerChoice(Protocol &connection) {
    connection << WELCOME_MSG;
    uint8_t player_choice;
    try {
        connection >> player_choice;
        while (player_choice != CREATE_GAME && player_choice != JOIN_GAME)     // Comando incorrecto
            errorLoop(ref(connection), player_choice);
        connection << SUCCESS; // Comando correcto
        return player_choice;
    } catch (const std::exception &e) {

    }
}

size_t HandshakeHandler::joinGame(Protocol &connection) {
    // todo : join game
    return 0;
}

void choiceLoop(Protocol &connection, uint8_t &choice) {
    std::string server_msg, str_choice;
    uint8_t server_response;
    connection >> server_msg;   // Mensaje bienvenida y muestra opciones
    std::cout << server_msg;
    std::cin >> str_choice;
    str_choice.erase(remove(str_choice.begin(), str_choice.end(), '\n'), str_choice.end());
    choice = (uint8_t) std::stoi(str_choice);
    connection << choice;   // Envio eleccion
    connection >> server_response;  // Obtengo ERROR o SUCCESS
    while (server_response != SUCCESS) {
        server_msg.clear(); // Limpio mensaje del servidor
        str_choice.clear(); // Limpio entrada jugador
        connection >> server_msg;
        std::cout << server_msg;
        std::cin >> str_choice;
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



