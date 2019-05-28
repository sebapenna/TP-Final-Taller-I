#ifndef PORTAL_STAGEDATA_H
#define PORTAL_STAGEDATA_H

class StageData {
private:
    size_t _height;
    size_t _width;

public:
    StageData(const size_t &height, const size_t &width);

    size_t getHeight() const;

    size_t getWidth() const;
};


#endif //PORTAL_STAGEDATA_H
