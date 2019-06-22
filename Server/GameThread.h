#ifndef PORTAL_GAMETHREAD_H
#define PORTAL_GAMETHREAD_H

#include <Common/SafeQueue.h>
#include <Common/ProtectedBlockingQueue.h>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include "DTOProcessor.h"
#include "Event.h"
#include "Configuration.h"
#include <string>

class Player;

// A cada jugador se le asignara un id (inician desde 0) por orden de llegada (su posicion en el
// vector). Este id se notificara a los usuarios una vez iniciada la partida, ya que se podria
// modificar si algun jugador se retira de la partida antes de ser iniciada. Solo el owner podra
// iniciar partida y sera aquel de id igual a 0
class GameThread {
private:
    size_t _id;   // id de la partida
    std::string _map_filename;
    bool _begin_game, _game_finished, _empty_game, _dead_thread;
    size_t _max_players;
    std::list<Player*> _players;
    SafeQueue<std::shared_ptr<Event>> _events_queue;
    std::mutex _m;
    std::thread _gameloop;

    // Run para el thread del gameloop. Juego comienza una vez que owner de la partida indica que
    // se debe iniciar y se llama al metodo beginGame.
    void run(std::shared_ptr<Configuration> configuration);

    void notifyAllNewPlayer();

    void notifyAllDeletedPlayer();

    void notifyNewOwner();

    void notifyOwnerBeganGame();

    void sendToAllPlayers(std::shared_ptr<ProtocolDTO> &dto);

public:
    // map_filename es el archivo yaml con la configuracion del map
    GameThread(Player* new_player, const size_t &max_players, std::string &&map_filename,
            const size_t &id, std::shared_ptr<Configuration> configuration);

    // Une jugador a la partida en caso de que no se haya llegado al limite de jugadores.
    // Valor de retorno sera true en caso de haber sido agregado, false de lo contrario.
    bool addPlayerIfOpenToNewPlayersAndNotFull(Player *new_player);

    // Elimina jugador del id indicado y libera su memoria
    void deletePlayer(const size_t& id);



    // Indico que se debe finalizar la partida y finalizo la ejecucion del hilo
    void endGameAndJoin();

    const size_t id() const;

    SafeQueue<std::shared_ptr<Event>>& getEventsQueue();

    bool isDead();

    bool openToNewPlayers();

    size_t maxPlayers();

    size_t playersJoined();

    std::string& mapFileName();
};


#endif //PORTAL_GAMETHREAD_H
