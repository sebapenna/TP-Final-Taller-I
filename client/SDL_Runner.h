//
// Created by jonathanmedina on 05/06/19.
//

#ifndef SDL_SDL_RUNNER_H
#define SDL_SDL_RUNNER_H


#include <Common/ProtectedBlockingQueue.h>
#include <Common/ProtocolTranslator/DataDTO/PlayerChellIdDTO.h>
#include <Common/ProtocolTranslator/DataDTO/ButtonDTO.h>
#include <Common/ProtocolTranslator/DataDTO/ChellDTO.h>
#include <Common/ProtocolTranslator/DataDTO/GateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/AcidDTO.h>
#include <Common/ProtocolTranslator/DataDTO/RockBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/MetalBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/MetalDiagonalBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyTransmitterDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyReceiverDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyBarrierDTO.h>
#include <Common/ProtocolTranslator/DataDTO/RockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/CakeDTO.h>
#include <Common/ProtocolTranslator/DataDTO/ButtonStateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/GateStateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyBallDTO.h>
#include <Common/ProtocolTranslator/DataDTO/PortalDTO.h>
#include <Common/ProtocolTranslator/DataDTO/PinToolDTO.h>
#include <client/ComponentsSDL/SoundFactory.h>
#include <client/ComponentsSDL/MusicPlayer.h>
#include "ComponentsSDL/Renderer.h"
#include "TextureFactory.h"
#include "../Common/SafeQueue.h"
#include "../Common/Thread.h"
#include "WorldView.h"

class SDL_Runner : public Thread {
private:
    SafeQueue<std::shared_ptr<ProtocolDTO>>& safeQueue;
    bool& done;
    Window window;
    Renderer renderer;
    TextureFactory textureFactory;
    SoundFactory soundFactory;
    MusicPlayer musicPlayer;
    WorldView world;
    int16_t myChellId;

    void addChell(ChellDTO* chellDTO, std::string& file_name);
    void addPlayerId(PlayerChellIdDTO* chellId, std::string& file_name);
    void addButton(ButtonDTO* buttonData, std::string& file_name);
    void addGate(GateDTO* gateDTO, std::string& file_name);
    void addAcid(AcidDTO* acidDTO, std::string& file_name);
    void addRockBlock(RockBlockDTO* rockBlockDTO, std::string& file_name);
    void addMetalBlock(MetalBlockDTO* metalBlockDTO, std::string& file_name);
    void addMetalDiagonalBlock(MetalDiagonalBlockDTO* metalDiagonalBlockDTO, std::string& file_name);
    void addEnergyTransmitter(EnergyTransmitterDTO* energyTransmitterDTO, std::string& file_name);
    void addEnergyReceiver(EnergyReceiverDTO* energyReceiverDTO, std::string& file_name);
    void addEnergyBarrier(EnergyBarrierDTO* energyBarrierDTO, std::string& file_name);
    void addRock(RockDTO* rockDTO, std::string& file_name);
    void addCake(CakeDTO* cakeDTO, std::string& file_name);
    void setButtonState(ButtonStateDTO* buttonStateDTO);
    void setGateState(GateStateDTO* gateStateDTO);
    void addEnergyBall(EnergyBallDTO* energyBallDTO, std::string& file_name);
    void addPortal(PortalDTO* portalDTO, std::string& file_name);
    void addPinTool(PinToolDTO* pinToolDTO, std::string& file_name);

public:
    SDL_Runner(std::string& title, SafeQueue<std::shared_ptr<ProtocolDTO>>& safeQueue, bool& done);
    void getRealPos(int& x, int& y, int x_m, int y_m);
    void run() override;
};


#endif //SDL_SDL_RUNNER_H
