#ifndef PORTAL_GATEDATA_H
#define PORTAL_GATEDATA_H

#include <vector>

class GateData {
private:
    size_t _id;
    float _x;
    float _y;
    std::vector<size_t> _buttons_needed; // id de los botones necesarios
    std::vector<size_t> _energy_receivers_needed; // id receptores energia

public:
    GateData(const size_t& id, const float& x, const float& y);

    void addButtonNeeded(const size_t& id);

    void addEnergyReceiverNeeded(const size_t& id);

    size_t getId() const;

    float getX() const;

    float getY() const;

    const std::vector<size_t> &getButtonsNeeded() const;

    const std::vector<size_t> &getEnergyReceiversNeeded() const;
};


#endif //PORTAL_GATEDATA_H