#ifndef PORTAL_EMISOR_ENERGIA_H
#define PORTAL_EMISOR_ENERGIA_H

#include <src/EnergyBall.h>
#include <src/Collidable.h>

class EnergyTransmitter: public Collidable {
private:
    b2Body *_body;
    uint8_t _direction; // Direccion en que saldra la Bola Energia
    float32 _time_elapsed = 0;

public:
    explicit EnergyTransmitter(b2Body *body, uint8_t direction);

    // Le indica a world si debe crear una EnergyBall
    bool releaseEnergyBall();

    b2Body *getBody() const;

    uint8_t getDirection() const;

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;
};


#endif //PORTAL_EMISOR_ENERGIA_H
