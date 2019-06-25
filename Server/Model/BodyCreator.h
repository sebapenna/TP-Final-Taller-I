#ifndef PORTAL_BOXCREATOR_H
#define PORTAL_BOXCREATOR_H

#include <Box2D/Box2D.h>

// Se encarga de crear las box del modelo Box2D estaticos y dinamicos de Box2D y genrarlas en el
// world brindado como parametro. Se utiliza esta clase dada la gran cantidad de veces que se
// repetira el mismo codigo
struct BoxCreator {
    // box_width y box_height seran los valores que se usaran en setAsBox. Friccion 0 por default
    static b2Body *createStaticBox(b2World *world, const float &x, const float &y,
            const float &box_half_width, const float &box_half_height, const float &friction = 0);

    static b2Body *createDynamicBox(b2World *world, const float &x, const float &y,
            const float &box_half_width, const float &box_half_height, const float &density);

    static b2Body *createDynamicCircle(b2World *world, const float &x, const float &y,
                                       const float &radius, const float& restitution,
                                       const float &denisty, const float &grav_scale = 0);
};


#endif //PORTAL_BOXCREATOR_H
