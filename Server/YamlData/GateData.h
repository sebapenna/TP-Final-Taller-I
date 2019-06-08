#ifndef PORTAL_GATEDATA_H
#define PORTAL_GATEDATA_H

#include <vector>

class GateData {
private:
    const size_t _id;
    const float _x;
    const float _y;
    std::vector<size_t> _buttons_needed; // id de los botones necesarios
    std::vector<size_t> _energy_receivers_needed; // id receptores energia

public:
    GateData(const size_t& id, const float& x, const float& y);

    void addButtonNeeded(const size_t& id);

    void addEnergyReceiverNeeded(const size_t& id);

    const size_t getId() const;

    const float getX() const;

    const float getY() const;

    const std::vector<size_t> &getButtonsNeeded() const;

    const std::vector<size_t> &getEnergyReceiversNeeded() const;
};


#endif //PORTAL_GATEDATA_H
