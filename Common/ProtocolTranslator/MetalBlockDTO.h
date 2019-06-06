#ifndef PORTAL_METALBLOCKDTO_H
#define PORTAL_METALBLOCKDTO_H

#include "ProtocolDTO.h"

class MetalBlockDTO: public ProtocolDTO {
private:
    const int16_t _x;
    const int16_t _y;
    const int16_t _width;
    const int16_t _height;
public:
    MetalBlockDTO(const int16_t& x, const int16_t& y, const int16_t& width,
                  const int16_t& height);

    ~MetalBlockDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getWidth() const;

    const int16_t getHeight() const;
};


#endif //PORTAL_METALBLOCKDTO_H
