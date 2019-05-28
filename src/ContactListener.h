#ifndef PORTAL_CONTACTLISTENER_H
#define PORTAL_CONTACTLISTENER_H

#include "Box2D/Box2D.h"

class ContactListener: public b2ContactListener {
private:
    b2World *_world;

public:
    explicit ContactListener(b2World *world);

    virtual void beginContact(b2Contact *contact);

//    virtual void endContact(b2Contact *contact);

    void doE() {};


};


#endif //PORTAL_CONTACTLISTENER_H
