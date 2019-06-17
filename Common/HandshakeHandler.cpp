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

#define SELECT_MAP_MSG "Ingrese la opción de mapa deseada siendo:\n\t- 0: Espacio;\n"

#define HOW_TO_REFRESH_MSG "Ingrese -1 para actualizar listado de partidas abiertas.\n"

#define SELECT_GAME_MSG "Ingrese el id de una de las siguientes partidas:\n"

#define SPACE_ID (uint8_t) 0   // todo: nombres mapas / CREAR MAPAS
#define SPACE "space.yaml"

#define CITY_ID (uint8_t) 1
#define CITY "city.yaml"

#define WOODS_ID (uint8_t) 2
#define WOODS "woods.yaml"

#define MAP_IDS SPACE_ID, CITY_ID, WOODS_ID // Listado de todos los ids

#define REFRESH (int16_t)   -1  // Valor de refresh negativo para no coincider con posible game_id

using std::ref;
using std::find;
using std::get;
using std::to_string;

/********************************** HANDLER SERVER ********************************************/
void errorLoop(Protocol &connection, uint8_t &player_choice) {
    connection << ERROR;
    connection << WRONG_OPTION_MSG;
    connection >> player_choice;
}

void errorLoop(Protocol &connection, int16_t &player_choice) {
    connection << ERROR;
    connection << WRONG_OPTION_MSG;
    connection >> player_choice;
}

size_t HandshakeHandler::joinGame(Protocol &connection, Lobby &lobby) {
    connection << HOW_TO_REFRESH_MSG;   // Mensaje como listar partidas

    int16_t player_choice;
    connection >> player_choice;
    while (player_choice != REFRESH)
        errorLoop(ref(connection), player_choice);
    connection << SUCCESS;

    while (true) {  // Loop finaliza cuando cliente ingresa id de partida correcto
        auto games_data_vec = lobby.getOpenGamesInformation();

        connection << (uint32_t) games_data_vec.size(); // Envio cantidad partidas a recibir

        connection << SELECT_GAME_MSG;  // Mensaje seleccion partida

        std::string msg;
        std::vector<size_t> game_ids;
        for (auto &game_data : games_data_vec) {
            msg.clear();
            auto game_id = get<0>(game_data);
            game_ids.push_back(game_id);    // Agrego id a la lista de opciones
            auto max_players = get<1>(game_data);
            auto players_joined = get<2>(game_data);
            auto map_fname = get<3>(game_data);
            if (map_fname == SPACE)
                map_fname = "Espacio";
            else if (map_fname == CITY)
                map_fname = "Ciudad";
            else if (map_fname == WOODS)
                map_fname = "Bosque";
            msg.append("\t- Id Partida: " + to_string(game_id) + " | Jugadores: " +
            to_string(players_joined) + "/" + to_string(max_players) + " | Mapa: " +
            map_fname + "\n");
            connection << msg;  // Envio informacion partida
        }
        connection >> player_choice;  // Recibo eleccion, tambien podria ser nuevo refresh
        bool wrong_id = find(game_ids.begin(), game_ids.end(), player_choice) == game_ids.end();

        while (wrong_id && player_choice != REFRESH) {
            errorLoop(ref(connection), player_choice);
            wrong_id = find(game_ids.begin(), game_ids.end(), player_choice) == game_ids.end();
        }
        connection << SUCCESS;

        if (player_choice != REFRESH)
            return player_choice;   // Retorno id de la partida seleccionada
    }
}


std::pair<size_t, std::string> HandshakeHandler::createGame(Protocol &connection) {
    connection << SELECT_PLAYERS_MSG;   // Envio mensaje seleccion jugadores

    uint8_t max_players, map_choice;
    connection >> max_players;
    while (max_players > MAX_PLAYERS_IN_GAME || max_players < 1) // Cantidad maxima de jugadores
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



// todo: VERIFICAR CUANDO CLIENTE ELIGE SI HAY GAMES DISPONIBLES
// if (getGames.empty)
//      "DEBE CREAR PARTIDA"
//  => directo a create
/********************************** HANDLER CLIENTE ********************************************/
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

void refreshLoop(Protocol &connection, int16_t &choice) {
    std::string server_msg, str_choice; // Buffer para mensaje servidor e input
    auto server_response = ERROR;    // Inicialmente no tengo comando
    while (server_response != SUCCESS) {
        server_msg.clear(); // Limpio mensaje del servidor
        str_choice.clear(); // Limpio entrada jugador

        connection >> server_msg;
        std::cout << server_msg;
        std::cin >> str_choice; // Leo input jugador y elimino salto del linea
        str_choice.erase(remove(str_choice.begin(), str_choice.end(), '\n'), str_choice.end());
        choice = (int16_t) std::stoi(str_choice);

        connection << choice;   // Envio eleccion
        connection >> server_response;  // Obtengo ERROR o SUCCESS
    }
}

void joinChoiceLoop(Protocol &connection, int16_t &choice) {
    std::string server_msg, str_choice; // Buffer para mensaje servidor e input
    uint32_t n_games;
    uint8_t server_response;
    while (choice == REFRESH) {
        server_msg.clear(); // Limpio mensaje del servidor
        str_choice.clear(); // Limpio entrada jugador

        connection >> n_games;  // Recibo cantidad partidas disponibles

        connection >> server_msg;   // Recibo mensaje escoger partida
        std::cout << server_msg;

        for (size_t i = 0; i < n_games; ++i) {
            connection >> server_msg;   // Recibo listado partidas
            std::cout << server_msg;
        }
        std::cin >> str_choice; // Leo input jugador y elimino salto del linea
        str_choice.erase(remove(str_choice.begin(), str_choice.end(), '\n'), str_choice.end());
        choice = (int16_t) std::stoi(str_choice);
        connection << choice;   // Envio partida seleccionada
        connection >> server_response;  // Obtengo ERROR o SUCCESS
        while (server_response == ERROR) {
            server_msg.clear();
            str_choice.clear();
            connection >> server_msg;
            std::cout << server_msg;
            std::cin >> str_choice; // Leo input jugador y elimino salto del linea
            str_choice.erase(remove(str_choice.begin(), str_choice.end(), '\n'), str_choice.end());
            choice = (int16_t) std::stoi(str_choice);
            connection << choice;   // Envio partida seleccionada
            connection >> server_response;  // Obtengo ERROR o SUCCESS
        } // todo: eliminar codigo repetido
    }
}

bool HandshakeHandler::getOptionsAndChoose(Protocol &connection) {
    uint8_t choice = 0;
    std::string server_msg;
    uint8_t server_response;

    choiceLoop(ref(connection), choice);    // Mensaje bienvenida y eleccion crear o unir

    if (choice == CREATE_GAME) {
        choiceLoop(ref(connection), choice);    // Selecciono maximo jugadores
        choiceLoop(ref(connection), choice);    // Selecciono mapa
        connection >> server_msg;   // Recibo informacion de lo sucedido
        std::cout << server_msg;
        connection >> server_response;  // Recibo SUCCESS
        return true;
    } else {    // Join
        while (true) {  // Loop finaliza una vez que se pudo agregar jugador a la partida
            int16_t refresh;
            refreshLoop(ref(connection), refresh);
            joinChoiceLoop(ref(connection), refresh);
            connection >> server_msg;   // Recibo informacion de lo sucedido
            std::cout << server_msg;
            connection >> server_response;  // Recibo notificacion si se pudo unir a la partida
            if (server_response == SUCCESS)
                return false; // Se obtuvo SUCCESS (añadido a la partida)
        }
    }
}
