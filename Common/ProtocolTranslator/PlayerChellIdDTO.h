#ifndef PORTAL_PLAYERCHELLIDDTO_H
#define PORTAL_PLAYERCHELLIDDTO_H


#include "ProtocolDTO.h"

class PlayerChellIdDTO: public ProtocolDTO {
private:
    const int16_t _chell_id;

public:
    explicit PlayerChellIdDTO(const int16_t& id);

    ~PlayerChellIdDTO() override;

    int16_t getClassId() const override;

    const int16_t getChellId() const;
};


#endif //PORTAL_PLAYERCHELLIDDTO_H
