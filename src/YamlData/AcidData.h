#ifndef PORTAL_ACIDDATA_H
#define PORTAL_ACIDDATA_H


class AcidData {
private:
    float _x;
    float _y;

public:
    AcidData(const float& x, const float& y);

    float getX() const;

    float getY() const;
};


#endif //PORTAL_ACIDDATA_H
