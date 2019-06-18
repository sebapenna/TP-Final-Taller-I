#ifndef PORTAL_ACIDDTO_H
#define PORTAL_ACIDDTO_H

#include "Common/ProtocolTranslator/ProtocolDTO.h"

class AcidDTO: public ProtocolDTO {
private:
    const int16_t _x;
    const int16_t _y;
    const int16_t _width;
    const int16_t _height;

public:
    AcidDTO(const int16_t& x, const int16_t& y, const int16_t& width,
                 const int16_t& height);

    ~AcidDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getWidth() const;

    const int16_t getHeight() const;

};


#endif //PORTAL_ACIDDTO_H
