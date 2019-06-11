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
// modificar si algun jugador se retira de la partida antes de ser iniciada.
class GameThread {
private:
    // Cola cotendra pares conformados por el id del jugador y el DTO que corresponda, asi se
    // sabra a que chell aplicar la accion
    DTOProcessor _processor;
    std::mutex _m;
    std::thread _gameloop;
    SafeQueue<std::shared_ptr<Event>> _events_queue;
    std::list<Player> _players;
    std::vector<ReceiverThread> _receive_threads;
    bool _begin_game = false, _game_finished = false;
    const std::string _map_filename;

    // Run para el thread del gameloop. Juego comienza una vez que owner de la partida indica que
    // se debe iniciar y se llama al metodo beginGame.
    void run(std::string map_filename);

public:
    // map_filename es el archivo yaml con la configuracion del mapa
    explicit GameThread(Player &&new_player, std::string &&map_filename);

    void addPlayer(Player &&new_player);

    void deletePlayer(const size_t& id);

    // Indico que se debe iniciar la partida
    void beginGame();

    // Indico que se debe finalizar la partida
    void endGame();
};


#endif //PORTAL_GAMETHREAD_H
