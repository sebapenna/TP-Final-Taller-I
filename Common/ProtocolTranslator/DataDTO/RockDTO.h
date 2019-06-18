#ifndef PORTAL_ROCKDTO_H
#define PORTAL_ROCKDTO_H

#include "Common/ProtocolTranslator/ProtocolDTO.h"

class RockDTO: public ProtocolDTO {
private:
    const int16_t _id;
    const int16_t _x;
    const int16_t _y;
    const int16_t _side_length;
    const int16_t _delete_state;
public:
    RockDTO(const int16_t& id, const int16_t& x, const int16_t& y, const int16_t& side_length,
            const int16_t& delete_state);

    ~RockDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getId() const;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getSideLength() const;

    const int16_t getDeleteState() const;
};


#endif //PORTAL_ROCKDTO_H
