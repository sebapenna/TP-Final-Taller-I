#ifndef PORTAL_GAMETHREAD_H
#define PORTAL_GAMETHREAD_H

#include <Common/SafeQueue.h>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include "Player.h"
#include "ReceiverThread.h"
#include "DTOProcessor.h"
#include <string>

// A cada jugador se le asignara un id (inician desde 0) por orden de llegada (su posicion en el
// vector). Este id se notificara a los usuarios una vez iniciada la partida, ya que se podria
// modificar si algun jugador se retira de la partida antes de ser iniciada. solo el owner podra
// iniciar partida y sera aquel de id igual a 0
class GameThread {
private:
    // Cola cotendra pares conformados por el id del jugador y el DTO que corresponda, asi se
    // sabra a que chell aplicar la accion
    std::mutex _m;
    std::thread _gameloop;
    std::list<std::shared_ptr<Player>> _players;
    SafeQueue<std::shared_ptr<Event>> _events_queue;
    std::vector<std::shared_ptr<ReceiverThread>> _receive_threads;
    size_t _max_players;
    bool _begin_game = false, _game_finished = false, _empty_game = false;
    std::string _map_filename;

    // Run para el thread del gameloop. Juego comienza una vez que owner de la partida indica que
    // se debe iniciar y se llama al metodo beginGame.
    void run(std::string map_filename);

    void sendToAllPlayers(std::shared_ptr<ProtocolDTO> &dto);

public:
    // map_filename es el archivo yaml con la configuracion del mapa
    explicit GameThread(std::shared_ptr<Player> new_player, const size_t& max_players, std::string &&map_filename);

    void addPlayer(std::shared_ptr<Player> new_player);

    void deletePlayer(const size_t& id);

    // Indico que se debe iniciar la partida
    void beginGame();

    // Indico que se debe finalizar la partida
    void endGame();

    void join();
};


#endif //PORTAL_GAMETHREAD_H