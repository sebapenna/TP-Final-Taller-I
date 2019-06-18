#ifndef PORTAL_CAKEDTO_H
#define PORTAL_CAKEDTO_H

#include <Common/ProtocolTranslator/ProtocolDTO.h>

class CakeDTO: public ProtocolDTO {
private:
    const int16_t _x;
    const int16_t _y;
    const int16_t _side_length;

public:
    CakeDTO(const int16_t& x, const int16_t& y, const int16_t& side_length);

    ~CakeDTO() override = default;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getSideLength() const;

    int16_t getClassId() const override;

};


#endif //PORTAL_CAKEDTO_H
