#ifndef PORTAL_PINTOOLDTO_H
#define PORTAL_PINTOOLDTO_H


#include "Common/ProtocolTranslator/ProtocolDTO.h"

class PinToolDTO: public ProtocolDTO {
private:
    const int16_t _id, _x, _y, _width, _height, _delete_state;

public:
    PinToolDTO(const int16_t& id, const int16_t& x, const int16_t& y, const
    int16_t& width, const int16_t& height, const int16_t& delete_state);

    ~PinToolDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getId() const;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getWidth() const;

    const int16_t getHeight() const;

    const int16_t getDeleteState() const;
};


#endif //PORTAL_PINTOOLDTO_H
