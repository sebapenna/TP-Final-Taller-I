#ifndef PORTAL_PORTALDTO_H
#define PORTAL_PORTALDTO_H

#include "Common/ProtocolTranslator/ProtocolDTO.h"

class PortalDTO: public ProtocolDTO {
private:
    const int16_t _id, _x, _y, _width, _height, _colour, _tilt, _delete_state;
public:
    PortalDTO(const int16_t& id, const int16_t& x, const int16_t& y, const int16_t& width,
            const int16_t& height, const int16_t& tilt, const int16_t& colour, const int16_t&
            delete_state);

    ~PortalDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getId() const;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getWidth() const;

    const int16_t getHeight() const;

    const int16_t getColour() const;

    const int16_t getDeleteState() const;

    const int16_t getTilt() const;
};


#endif //PORTAL_PORTALDTO_H
