#include "BoxCreator.h"

b2Body *BoxCreator::createStaticBox(b2World *world, const float &x, const float &y,
        const float &box_half_width, const float &box_half_height, const float &friction) {
    b2BodyDef body_def;
    body_def.position.Set(x, y);
    body_def.type = b2_staticBody;

    b2PolygonShape shape;
    shape.SetAsBox(box_half_width, box_half_height);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.friction = friction;
    b2Body *body = world->CreateBody(&body_def);

    body->CreateFixture(&fixture);
    return body;
}

b2Body *BoxCreator::createDynamicBox(b2World *world, const float &x, const float &y,
        const float &box_half_width, const float &box_half_height, const float &density) {
    b2BodyDef body_def;
    body_def.position.Set(x, y);
    body_def.type = b2_dynamicBody;
    body_def.fixedRotation = true;

    b2PolygonShape shape;
    shape.SetAsBox(box_half_width, box_half_height);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = density;
    fixture.friction = 0;
    fixture.restitution = -1;   // Permite chell resbale en roca

    b2Body *body = world->CreateBody(&body_def);

    body->CreateFixture(&fixture);
    return body;
}

