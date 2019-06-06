#ifndef PORTAL_METALDIAGONALBLOCKDTO_H
#define PORTAL_METALDIAGONALBLOCKDTO_H

#include "ProtocolDTO.h"

class MetalDiagonalBlockDTO: public ProtocolDTO {
private:
    const int16_t _x;
    const int16_t _y;
    const int16_t _side_length;
    const int16_t _orientation;
public:
    MetalDiagonalBlockDTO(const int16_t& x, const int16_t& y,
            const int16_t& side_length, const int16_t& orientation);

    ~MetalDiagonalBlockDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getSideLength() const;

    const int16_t getOrientation() const;

};


#endif //PORTAL_METALDIAGONALBLOCKDTO_H
