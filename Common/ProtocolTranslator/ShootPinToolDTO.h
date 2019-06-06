#ifndef PORTAL_SHOOTPINTOOLDTO_H
#define PORTAL_SHOOTPINTOOLDTO_H

#include "ProtocolDTO.h"

class ShootPinToolDTO: public ProtocolDTO {
private:
    const int16_t _x;
    const int16_t _y;

public:
    ShootPinToolDTO(const int16_t &x, const int16_t &y);

    ~ShootPinToolDTO() override;

    int16_t getClassId() const override;

    const int16_t getX() const;

    const int16_t getY() const;
};


#endif //PORTAL_SHOOTPINTOOLDTO_H
