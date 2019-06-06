#ifndef PORTAL_PORTALDTO_H
#define PORTAL_PORTALDTO_H

#include "ProtocolDTO.h"

class PortalDTO: public ProtocolDTO {
private:
    int _color;
    int _x;
    int _y;

public:
    PortalDTO(const int& color, const int& x, const int& y);

    int getClassId() const override;

    int getColor() const;

    int getX() const;

    int getY() const;

    ~PortalDTO() override;
};


#endif //PORTAL_PORTALDTO_H
