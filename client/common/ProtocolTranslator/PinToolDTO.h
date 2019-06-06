#ifndef PORTAL_PINTOOLDTO_H
#define PORTAL_PINTOOLDTO_H

#include "ProtocolDTO.h"

class PinToolDTO: public ProtocolDTO {
private:
    const int _x;
    const int _y;

public:
    PinToolDTO(const int& x, const int& y);

    ~PinToolDTO() override;

    int getClassId() const override;

    const int getX() const;

    const int getY() const;
};


#endif //PORTAL_PINTOOLDTO_H
