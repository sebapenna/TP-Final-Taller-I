#ifndef PORTAL_EMISOR_ENERGIA_H
#define PORTAL_EMISOR_ENERGIA_H

#include <Server/Model/EnergyBall.h>
#include <Server/Model/Collidable.h>

class EnergyTransmitter: public Collidable {
private:
    b2Body *_body;
    uint8_t _direction; // Direccion en que saldra la Bola Energia
    float32 _time_elapsed = 0;
    bool _changed_state = false;    // Booleano para indicar camibo de estado durante step
    size_t _id;
    const float _width, _height;
    const float _time_to_release;

public:
    explicit EnergyTransmitter(const size_t &id, b2Body *body, uint8_t direction,
            const float& width, const float& height, const float& time_to_release);

    ~EnergyTransmitter() override;

    size_t id() const;
    uint8_t getDirection() const;

    bool isDead(const float &time_step) override;

    const float x() override;
    const float y() override;
    const float width() override;
    const float height() override;
    b2Body *getBody() const override;
    const uint8_t classId() override;

    void collideWith(Collidable *other) override;
    void endCollitionWith(Collidable *other) override;

    void step(const float &time_step) override;
    bool actedDuringStep() override;
};


#endif //PORTAL_EMISOR_ENERGIA_H
