#ifndef PORTAL_GATESTATEDTO_H
#define PORTAL_GATESTATEDTO_H

#include "ProtocolDTO.h"

class GateStateDTO: public ProtocolDTO {
private:
    const int16_t _id;
    const int16_t _state;

public:
    GateStateDTO(const int16_t& id, const int16_t& state);

    ~GateStateDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getId() const;

    const int16_t getState() const;
};


#endif //PORTAL_GATESTATEDTO_H
