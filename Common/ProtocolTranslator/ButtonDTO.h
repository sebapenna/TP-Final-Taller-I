#ifndef PORTAL_BUTTONDTO_H
#define PORTAL_BUTTONDTO_H

#include "ProtocolDTO.h"

class ButtonDTO: public ProtocolDTO {
private:
    const int16_t _id;
    const int16_t _x;
    const int16_t _y;
    const int16_t _width;
    const int16_t _height;

public:
    ButtonDTO(const int16_t& id, const int16_t& x, const int16_t& y, const int16_t& width,
            const int16_t& height);

    ~ButtonDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getWidth() const;

    const int16_t getHeight() const;

    const int16_t getId() const;

};


#endif //PORTAL_BUTTONDTO_H
