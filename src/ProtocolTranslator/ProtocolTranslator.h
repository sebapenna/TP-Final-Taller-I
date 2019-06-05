#ifndef PORTAL_PROTOCOLTRANSLATOR_H
#define PORTAL_PROTOCOLTRANSLATOR_H

#include "ProtocolDTO.h"
#include <vector>

class ProtocolTranslator {
private:
    static std::vector<int> moveLeft(const ProtocolDTO *dto);

    static std::vector<int> moveRight(const ProtocolDTO *dto);

    static std::vector<int> jump(const ProtocolDTO *dto);

    static std::vector<int> stop(const ProtocolDTO *dto);

    static std::vector<int> portal(const ProtocolDTO *dto);

    static std::vector<int> pinTool(const ProtocolDTO *dto);

    static std::vector<int> liftRock(const ProtocolDTO *dto);

    static std::vector<int> dropRock(const ProtocolDTO *dto);

public:
    static std::vector<int> translate(const ProtocolDTO *dto);
};


#endif //PORTAL_PROTOCOLTRANSLATOR_H
