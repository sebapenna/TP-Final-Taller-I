#ifndef PORTAL_ROCKBLOCKDTO_H
#define PORTAL_ROCKBLOCKDTO_H

#include "ProtocolDTO.h"

class RockBlockDTO: public ProtocolDTO {
private:
    const int16_t _x;
    const int16_t _y;
    const int16_t _width;
    const int16_t _height;

public:
    RockBlockDTO(const int16_t& x, const int16_t& y, const int16_t& width,
                 const int16_t& height);

    ~RockBlockDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getWidth() const;

    const int16_t getHeight() const;
};


#endif //PORTAL_ROCKBLOCKDTO_H
