#ifndef PORTAL_BUTTONSTATEDTO_H
#define PORTAL_BUTTONSTATEDTO_H

#include "ProtocolDTO.h"

class ButtonStateDTO: public ProtocolDTO {
private:
    const int16_t _id;
    const int16_t _state;

public:
    ButtonStateDTO(const int16_t& id, const int16_t& state);

    ~ButtonStateDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getId() const;

    const int16_t getState() const;
};


#endif //PORTAL_BUTTONSTATEDTO_H
