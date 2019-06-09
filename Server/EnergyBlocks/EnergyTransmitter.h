#ifndef PORTAL_EMISOR_ENERGIA_H
#define PORTAL_EMISOR_ENERGIA_H

#include <Server/EnergyBall.h>
#include <Server/Collidable.h>

class EnergyTransmitter: public Collidable {
private:
    b2Body *_body;
    uint8_t _direction; // Direccion en que saldra la Bola Energia
    float32 _time_elapsed = 0;
    bool _changed_state = false;    // Booleano para indicar camibo de estado durante step

public:
    explicit EnergyTransmitter(b2Body *body, uint8_t direction);

    // Le indica a world si debe crear una EnergyBall
    bool releaseEnergyBall();

    b2Body *getBody() const;

    uint8_t getDirection() const;

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;
};


#endif //PORTAL_EMISOR_ENERGIA_H
