#include <Server/CollidableData/BoxCreator.h>
#include <Server/Model/constants.h>
#include <Server/Model/World.h>
#include "Shooter.h"
#include "../RayCastCallback.h"

bool Shooter::shotHitMetal(b2World * world, RayCastCallback &callback, Chell *chell,
                           const float &dest_x, const float &dest_y) {
    float origin_x = chell->x(), origin_y = chell->y();
    b2Vec2 point1(origin_x, origin_y);
    b2Vec2 point2(dest_x, dest_y);
    world->RayCast(&callback, point1, point2);
    if (callback.m_fixture) {
        auto collidable = (Collidable *) callback.m_fixture->GetBody()->GetUserData();
        auto cname = collidable->classId();
        return (cname == METAL_BLOCK || cname == METAL_DIAGONAL_BLOCK);// Choco con bloque de metal
    }
    return false;   // Colision no fue con superficie donde se pueda crear objeto
}

/***************************************** Create PinTool ***************************************/
PinTool *Shooter::createPinTool(World *world, const float &x, const float &y, const size_t&
chell_id, std::shared_ptr<Configuration> config) {
    auto body = BoxCreator::createStaticBox(world->getWorld(), x, y, config->getPintoolHalfWidth(),
                                            config->getPintoolHalfHeight());

    auto pintool = new PinTool(world->getNextShootableId(), chell_id, body,
            2 * config->getPintoolHalfWidth(), 2 * config->getPintoolHalfHeight());
    body->SetUserData(pintool);
    world->addShootable(pintool->id(), pintool);
    return pintool;
}

void Shooter::shoot(World *world, Chell *chell, const float &dest_x, const float &dest_y,
        std::shared_ptr<Configuration> config) {
    RayCastCallback callback;
    if (shotHitMetal(world->getWorld(), callback, chell, dest_x, dest_y)) {  // Colision con metal
        auto pintool = createPinTool(world, callback.m_point.x, callback.m_point.y, chell->id(),
                config);
        auto old_pintool_id = chell->setNewPinTool(pintool);
        if (old_pintool_id != -1)
            world->addShootableToDelete(old_pintool_id);
    }
}



/***************************************** Create Portal ***************************************/
Portal * Shooter::createPortal(World *world, Collidable * collidable, b2Vec2 point, b2Vec2 normal,
                               const int16_t &colour, std::shared_ptr<Configuration> config) {
    float half_width = config->getPortalHalfWidth(), half_height = config->getPortalHalfHeight();

    int angle = 0;  // Default portal vertical, defino angulo en base a normal
    if ((normal.x > 0 && normal.y > 0) || (normal.x < 0 && normal.y < 0))
        angle = 45;    // Portal inclinado (rotado hacia izquierda)
    else if ((normal.x > 0 && normal.y < 0) || (normal.x < 0 && normal.y > 0))
        angle = -45;   // Portal inclinado (rotado hacia derecha)
    else if ((normal.x == 0 && normal.y > 0) || (normal.x == 0 && normal.y < 0)) {
        angle = 180; // Cuerpo horizontal
        half_width = config->getPortalHalfHeight();
        half_height = config->getPortalHalfWidth();
    }

    // Posicion sera en base a collidable, para quedar en centro de cara
    float x = collidable->x(), y = collidable->y();
    switch (angle) {
        case 0: {
            if (collidable->classId() == METAL_BLOCK) {
                auto block = (MetalBlock *) collidable;
                (normal.x > 0) ? (x += +collidable->width() / 2) : (x -= collidable->width() / 2);
                y = block->getSubBlockCenterY(point.y);
            } else {    // Cara plana de bloque diagonal
                auto block = (MetalDiagonalBlock *) collidable;
                (normal.x > 0) ? (x += block->width()) : 0; // x se matiene si falso
                y = block->getCenterY();
            }
            break;
        } case 180: {
            if (collidable->classId() == METAL_BLOCK) {
                auto block = (MetalBlock *) collidable;
                (normal.y > 0) ? (y += +collidable->height() / 2) : (y -= collidable->height() / 2);
                x = block->getSubBlockCenterX(point.x);
            } else {    // Cara plana bloque diagonal
                auto block = (MetalDiagonalBlock *) collidable;
                (normal.y > 0) ? (y += block->height()) : 0;    // y se mantiene si falso
                x = block->getCenterX();
            }
            break;
        } default:   // Inclinado, ambos casos
            auto block = (MetalDiagonalBlock*) collidable;
            x = block->getCenterX();
            y = block->getCenterY();
            break;
    }

    auto body = BoxCreator::createStaticBox(world->getWorld(), x, y, half_width, half_height);
    auto radians = angle * b2_pi / 180;
    body->SetTransform(body->GetPosition(), radians);   // Realizo posible transformacion

    size_t next_id = 0;
    auto portal = new Portal(world->getNextShootableId(), body, normal, colour, 2 * half_width,
            2 * half_height);
    body->SetUserData(portal);
    world->addShootable(portal->id(), portal);
    return portal;
}

void Shooter::shoot(World *world, Chell *chell, const float &dest_x, const float &dest_y,
                    const int16_t &colour, std::shared_ptr<Configuration> config) {
    RayCastCallback callback;
    if (shotHitMetal(world->getWorld(), callback, chell, dest_x, dest_y)) {  // Colision con metal
        auto portal = createPortal(world,
                (Collidable*) callback.m_fixture->GetBody()->GetUserData(), callback.m_point,
                callback.m_normal, colour, config);
        auto old_pintool_id = chell->setNewPortal(portal);
        if (old_pintool_id != -1)
            world->addShootableToDelete(old_pintool_id);
    }
}
