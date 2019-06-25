#ifndef PORTAL_COLLIDABLEDATA_H
#define PORTAL_COLLIDABLEDATA_H

#include <stdint-gcc.h>
#include <Server/Model/constants.h>
#include <Server/Model/BodyCreator.h>
#include <Server/Configuration.h>

class World;

class CollidableData {
public:
    virtual const float getX() const = 0;

    virtual const float getY() const = 0;

    // Todos los datos necesarios para la creacion estan presentes en el CollidableData
    // respectivo, se brinda tan solo world para generar el cuerpo en el mismo y
    // config para obtener una instancia del mismo y utilizar datos configurables
    virtual void build(World* world, std::shared_ptr<Configuration> config) = 0;
};

#endif //PORTAL_COLLIDABLEDATA_H
