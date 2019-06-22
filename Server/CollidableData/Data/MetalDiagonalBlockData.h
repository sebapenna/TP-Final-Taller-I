#ifndef PORTAL_METALDIAGONALBLOCKDATA_H
#define PORTAL_METALDIAGONALBLOCKDATA_H

#include <string>
#include "Server/CollidableData/CollidableData.h"

class MetalDiagonalBlockData : public CollidableData {
private:
    const float _width;
    const float _height;
    float _x;
    const float _y;
    uint8_t _orientation;

public:
    // X e Y deben ser la posicion de la punta inferior izquierda, pensando el bloque diagonal
    // como un cuadrado completo, sin importar la orientacion del mismo
    MetalDiagonalBlockData(const float& width, const float& height,
            const float& x, const float& y, const std::string& orientation);

    const float getWidth() const;

    const float getHeight() const;

    const float getX() const override;

    const float getY() const override;

    const uint8_t getOrientation() const;

    void build(World *world, std::shared_ptr<Configuration> config) override;
};


#endif //PORTAL_METALDIAGONALBLOCKDATA_H
