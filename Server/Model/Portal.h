#ifndef TP_FINAL_PORTAL_H
#define TP_FINAL_PORTAL_H


#include <cstdint>
#include <Server/Model/Collidable.h>

class Portal: public Collidable {
private:
    uint8_t _orientation;

public:
    explicit Portal(uint8_t orientation);

    void collideWith(Collidable *other) override;

    const std::string getClassName() override;
};


#endif //TP_FINAL_PORTAL_H
