#ifndef PORTAL_ACIDDATA_H
#define PORTAL_ACIDDATA_H


class AcidData {
private:
    const float _x;
    const float _y;

public:
    AcidData(const float& x, const float& y);

    const float getX() const;

    const float getY() const;
};


#endif //PORTAL_ACIDDATA_H
