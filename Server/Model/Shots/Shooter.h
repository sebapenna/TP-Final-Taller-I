#ifndef PORTAL_SHOOTER_H
#define PORTAL_SHOOTER_H

#include <Server/Model/Chell.h>
#include <Server/Model/Shots/PinTool.h>
#include <Server/Model/Shots/Portal.h>
#include <Server/Model/RayCastCallback.h>
#include <Server/Configuration.h>

class World;

// Realiza el disparo desde la chell indicada hacia el punto destino brindado. En caso de
// colisionar con una superficie de metal crea el objeto y utiliza los metodos necesarios de
// World para que lo agregue a sus estructuras, tanto nuevos objetos como objetos a eliminar
class Shooter {
private:
    // Retorna true en caso de que el disparo colisiono sobre una superficie en la cual se puede
    // crear el objeto que genera el disparo, false en el caso contrario.
    static bool shotHitMetal(b2World * world, RayCastCallback &callback, Chell *chell,
            const float &dest_x, const float &dest_y);

    static PinTool* createPinTool(World *world, const float &x, const float &y,
            const size_t& chell_id, std::shared_ptr<Configuration> config);

    static Portal* createPortal(World *world, Collidable * collidable, b2Vec2 point, b2Vec2 normal,
                                const int16_t &colour, std::shared_ptr<Configuration> config);

public:
    static void shoot(World *world, Chell *chell, const float &dest_x, const float &dest_y,
                   std::shared_ptr<Configuration> config);

    static void shoot(World *world, Chell *chell, const float &dest_x, const float &dest_y,
            const int16_t &colour, std::shared_ptr<Configuration> config);
};


#endif //PORTAL_SHOOTER_H
