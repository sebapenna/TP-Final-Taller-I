#include "MetalDiagonalBlockData.h"
#include <Server/Model/constants.h>
#include <Server/Model/World.h>

MetalDiagonalBlockData::MetalDiagonalBlockData(const float &width,
        const float &height, const float &x, const float &y,
        const std::string &orientation) : _width(width), _height(height),
        _x(x), _y(y) {
    if (orientation == "NE")
        _orientation = O_NE;
    else if (orientation == "NO")
        _orientation = O_NO;
    else if(orientation == "SO")
        _orientation = O_SO;
    else
        _orientation = O_SE;
}

const float MetalDiagonalBlockData::getWidth() const {
    return _width;
}

const float MetalDiagonalBlockData::getHeight() const {
    return _height;
}

const float MetalDiagonalBlockData::getX() const {
    return _x;
}

const float MetalDiagonalBlockData::getY() const {
    return _y;
}

const uint8_t MetalDiagonalBlockData::getOrientation() const {
    return _orientation;
}

void
MetalDiagonalBlockData::build(World *world, std::shared_ptr<Configuration> config) {
    b2Vec2 vertices[3];
    int32 count = 3;
    switch (_orientation) {
        case O_NE:
            vertices[0].Set(0, 0);
            vertices[1].Set(_width, 0);
            vertices[2].Set(0, _height);
            break;
        case O_NO:
            vertices[0].Set(0, 0);
            vertices[1].Set(_width, 0);
            vertices[2].Set(_width, _height);
            break;
        case O_SE:
            vertices[0].Set(0, _height);
            vertices[1].Set(_width, _height);
            vertices[2].Set(0, 0);
            break;
        case O_SO:
            vertices[0].Set(0, _height);
            vertices[1].Set(_width, _height);
            vertices[2].Set(_width, 0);
            break;
        default:    // No existe este caso
            break;
    }

    b2BodyDef body_def;
    body_def.position.Set(_x, _y);
    body_def.type = b2_staticBody;

    b2Body *body = world->getWorld()->CreateBody(&body_def);

    b2PolygonShape shape;
    shape.Set(vertices, count);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.friction = 0;

    body->CreateFixture(&fixture);

    auto met_diag_block = new MetalDiagonalBlock(_x, _y, _width, _height, _orientation);
    body->SetUserData(met_diag_block);
    world->addMetalDiagonalBlock(met_diag_block);
}

