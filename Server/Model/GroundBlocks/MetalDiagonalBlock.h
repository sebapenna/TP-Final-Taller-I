#ifndef PORTAL_BLOQUE_METAL_DIAGONAL_H
#define PORTAL_BLOQUE_METAL_DIAGONAL_H

#include <cstdint>
#include <Server/Model/Collidable.h>

class MetalDiagonalBlock: public Collidable {
private:
    const float _x;
    const float _y;
    const float _width;
    const float _height;
    const uint8_t _orientation;

public:
    explicit MetalDiagonalBlock(const float& x, const float& y, const float& width, const float&
    height, uint8_t orientation);

    ~MetalDiagonalBlock() override;

    const uint8_t getOrientation() const;

    bool isDead(const float &time_step) override;

    void collideWith(Collidable *other) override;
    void endCollitionWith(Collidable *other) override;

    void step(const float &time_step) override;
    bool actedDuringStep() override;

    // X e Y seran la posicion de la punta inferior izquierda, pensando el bloque diagonal
    // como un cuadrado completo, sin importar la orientacion del mismo
    const uint8_t classId() override;
    const float x() override;
    const float y() override;
    const float width() override;
    const float height() override;
    b2Body *getBody() const override;

    // Retorna el valor de x en el centro del cuerpo
    const float getCenterX();
    const float getCenterY();
};


#endif //PORTAL_BLOQUE_METAL_DIAGONAL_H
