#ifndef PORTAL_BLOQUE_METAL_H
#define PORTAL_BLOQUE_METAL_H

#include <cstdint>
#include <Server/Model/Collidable.h>

class MetalBlock: public Collidable {
private:
    const float _x;
    const float _y;
    const float _width;
    const float _height;

public:
    MetalBlock(const float& x, const float& y, const float& width, const float& height);

    ~MetalBlock() override;

    const uint8_t classId() override;
    const float x() override;
    const float y() override;
    const float width() override;
    const float height() override;
    b2Body *getBody() const override;

    void collideWith(Collidable *other) override;
    void endCollitionWith(Collidable *other) override;

    void step(const float &time_step) override;
    bool actedDuringStep() override;

    // Calcula la x central del sub-bloque mas cercano al punto x dentro del bloque de gran tamaño.
    // PRE: x debe encontrarse dentro del largo del bloque.
    float getSubBlockCenterX(const float& x);

    // Calcula la y central del sub-bloque mas cercano al punto y dentro del bloque de gran tamaño.
    // PRE: y debe encontrarse dentro del largo del bloque.
    float getSubBlockCenterY(const float& y);

    bool isDead(const float &time_step) override;

};


#endif //PORTAL_BLOQUE_METAL_H
