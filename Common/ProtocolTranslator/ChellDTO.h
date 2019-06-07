#ifndef PORTAL_CHELLDTO_H
#define PORTAL_CHELLDTO_H

#include "ProtocolDTO.h"

class ChellDTO: public ProtocolDTO {
private:
    const int16_t _id;
    const int16_t _x;
    const int16_t _y;
    const int16_t _width;
    const int16_t _height;
    const int16_t _direction;
    const int16_t _tilted;
    const int16_t _moving;
    const int16_t _jumping;
    const int16_t _shooting;
    const int16_t _carrying_rock;
    const int16_t _delete_state;

public:
    ChellDTO(const int16_t& id, const int16_t& x, const int16_t& y, const int16_t& width,
            const int16_t& height, const int16_t& direction, const int16_t& tilted,
            const int16_t& moving, const int16_t& jumping, const int16_t& shoting, const int16_t&
            carrying_rock, const int16_t& delete_state);

    ~ChellDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getId() const;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getDirection() const;

    const int16_t getTilted() const;

    const int16_t getJumping() const;

    const int16_t getShooting() const;

    const int16_t getCarryingRock() const;

    const int16_t getDeleteState() const;

    const int16_t getMoving() const;

    const int16_t getWidth() const;

    const int16_t getHeight() const;
};


#endif //PORTAL_CHELLDTO_H
