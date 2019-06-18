#ifndef PORTAL_CAKEDATA_H
#define PORTAL_CAKEDATA_H

class CakeData {
private:
    const float _x;
    const float _y;

public:
    CakeData(const float &x, const float& y);

    const float getX() const;

    const float getY() const;
};


#endif //PORTAL_CAKEDATA_H
