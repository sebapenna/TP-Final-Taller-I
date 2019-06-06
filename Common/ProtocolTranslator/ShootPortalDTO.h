#ifndef PORTAL_SHOOTPORTALDTO_H
#define PORTAL_SHOOTPORTALDTO_H

#include "ProtocolDTO.h"

class ShootPortalDTO: public ProtocolDTO {
private:
    const int16_t _color;
    const int16_t _x;
    const int16_t _y;

public:
    ShootPortalDTO(const int16_t &color, const int16_t &x, const int16_t &y);

    ~ShootPortalDTO() override;

    int16_t getClassId() const override;

    const int16_t getColor() const;

    const int16_t getX() const;

    const int16_t getY() const;
};


#endif //PORTAL_SHOOTPORTALDTO_H
