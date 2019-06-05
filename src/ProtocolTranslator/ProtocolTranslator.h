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

    static ProtocolDTO* moveLeft(std::vector<int> data);
    static ProtocolDTO* moveRight(std::vector<int> data);
    static ProtocolDTO* jump(std::vector<int> data);
    static ProtocolDTO* stop(std::vector<int> data);
    static ProtocolDTO* portal(std::vector<int> data);
    static ProtocolDTO* pinTool(std::vector<int> data);
    static ProtocolDTO* liftRock(std::vector<int> data);
    static ProtocolDTO* dropRock(std::vector<int> data);

public:
    static std::vector<int> translate(const ProtocolDTO *dto);

    static ProtocolDTO* translate(const std::vector<int> &data);
};


#endif //PORTAL_PROTOCOLTRANSLATOR_H
