//
// Created by jonathanmedina on 02/06/19.
//

#include <SDL2/SDL_image.h>
#include "TextureFactory.h"
#include "SDLException.h"

#define CHELL_FLYING_TEXTURE_NAME "flying_chell"
#define CHELL_DYING_TEXTURE_NAME "dying_chell"
#define CHELL_FIRING_TEXTURE_NAME "firing_chell"
#define CHELL_RESTING_IDLE_TEXTURE_NAME "resting_idle_chelll"
#define CHELL_RUNNING_CHELL_TEXTURE_NAME "running_chell"
#define CHELL_WINNING_CHELL_TEXTURE_NAME "winning_chell"


#define BLOCK_TEXTURE_NAME "block"
#define GATE_TEXTURE_NAME "gate"
#define BULLET_AND_ROCK_TEXTURE_NAME "bulletAndRock"
#define ACID_AND_BUTTONS_TEXTURE_NAME "acidAndButtons"
#define BACKGROUND_TEXTURE_NAME "background"
#define CAKE_TEXTURE_NAME "cake"
#define PORTAL_TEXTURE_NAME "portal"
#define PINTOOL_TEXTURE_NAME "pintool"

#ifdef DEBUG_MODE
#define DYING_FILE "assets/textures/chellTextures/dying_chell.png"
#else
#define DYING_FILE "/etc/Portal/assets/textures/chellTextures/dying_chell.png"
#endif

#ifdef DEBUG_MODE
#define FIRING_FILE "assets/textures/chellTextures/firing_chell.png"
#else
#define FIRING_FILE "/etc/Portal/assets/textures/chellTextures/firing_chell.png"
#endif

#ifdef DEBUG_MODE
#define FLYING_FILE "assets/textures/chellTextures/flying_chell.png"
#else
#define FLYING_FILE "/etc/Portal/assets/textures/chellTextures/flying_chell.png"
#endif

#ifdef DEBUG_MODE
#define RESTING_FILE "assets/textures/chellTextures/resting_idle_chell.png"
#else
#define RESTING_FILE "/etc/Portal/assets/textures/chellTextures/resting_idle_chell.png"
#endif

#ifdef DEBUG_MODE
#define RUNNING_FILE "assets/textures/chellTextures/running_chell.png"
#else
#define RUNNING_FILE "/etc/Portal/assets/textures/chellTextures/running_chell.png"
#endif

#ifdef DEBUG_MODE
#define WINNING_FILE "assets/textures/chellTextures/winning_chell.png"
#else
#define WINNING_FILE "/etc/Portal/assets/textures/chellTextures/winning_chell.png"
#endif

#ifdef DEBUG_MODE
#define BLOCK_FILE "assets/textures/chellTextures/block.png"
#else
#define BLOCK_FILE "/etc/Portal/assets/textures/chellTextures/block.png"
#endif

#ifdef DEBUG_MODE
#define GATES_FILE "assets/textures/chellTextures/gates.png"
#else
#define GATES_FILE "/etc/Portal/assets/textures/chellTextures/gates.png"
#endif

#ifdef DEBUG_MODE
#define BULLET_AND_ROCK_FILE "assets/textures/chellTextures/bulletAndRock.png"
#else
#define BULLET_AND_ROCK_FILE "/etc/Portal/assets/textures/chellTextures/bulletAndRock.png"
#endif

#ifdef DEBUG_MODE
#define ACID_FILE "assets/textures/chellTextures/acidAndButtons.png"
#else
#define ACID_FILE "/etc/Portal/assets/textures/chellTextures/acidAndButtons.png"
#endif

#ifdef DEBUG_MODE
#define BACKGROUND_FILE "assets/textures/chellTextures/background.png"
#else
#define BACKGROUND_FILE "/etc/Portal/assets/textures/chellTextures/background.png"
#endif

#ifdef DEBUG_MODE
#define CAKE_FILE "assets/textures/chellTextures/cake.png"
#else
#define CAKE_FILE "/etc/Portal/assets/textures/chellTextures/cake.png"
#endif

#ifdef DEBUG_MODE
#define PORTAL_FILE "assets/textures/chellTextures/portal.png"
#else
#define PORTAL_FILE "/etc/Portal/assets/textures/chellTextures/portal.png"
#endif

#ifdef DEBUG_MODE
#define PINTOOL_FILE "assets/textures/chellTextures/pintool.png"
#else
#define PINTOOL_FILE "/etc/Portal/assets/textures/chellTextures/pintool.png"
#endif

TextureFactory::TextureFactory() : textures(textures) {
    IMG_Init(IMG_INIT_PNG);
}

TextureFactory::~TextureFactory() {
    for (auto& elem : textures) {
        SDL_DestroyTexture(elem.second);
    }
}

void TextureFactory::init(Renderer& renderer) {
    textures[CHELL_DYING_TEXTURE_NAME] = loadTexture(std::string(DYING_FILE), renderer);
    textures[CHELL_FIRING_TEXTURE_NAME] = loadTexture(std::string(FIRING_FILE), renderer);
    textures[CHELL_FLYING_TEXTURE_NAME] = loadTexture(std::string(FLYING_FILE), renderer);
    textures[CHELL_RESTING_IDLE_TEXTURE_NAME] = loadTexture(std::string(RESTING_FILE), renderer);
    textures[CHELL_RUNNING_CHELL_TEXTURE_NAME] = loadTexture(std::string(RUNNING_FILE), renderer);
    textures[CHELL_WINNING_CHELL_TEXTURE_NAME] = loadTexture(std::string(WINNING_FILE), renderer);

    textures[BLOCK_TEXTURE_NAME] = loadTexture(std::string(BLOCK_FILE), renderer);
    textures[GATE_TEXTURE_NAME] = loadTexture(std::string(GATES_FILE), renderer);
    textures[BULLET_AND_ROCK_TEXTURE_NAME] = loadTexture(std::string(BULLET_AND_ROCK_FILE), renderer);
    textures[ACID_AND_BUTTONS_TEXTURE_NAME] = loadTexture(std::string(ACID_FILE), renderer);
    textures[BACKGROUND_TEXTURE_NAME] = loadTexture(std::string(BACKGROUND_FILE), renderer);
    textures[CAKE_TEXTURE_NAME] = loadTexture(std::string(CAKE_FILE), renderer);
    textures[PORTAL_TEXTURE_NAME] = loadTexture(std::string(PORTAL_FILE), renderer);
    textures[PINTOOL_TEXTURE_NAME] = loadTexture(std::string(PINTOOL_FILE), renderer);

    //setColor(textures["chell"], 255, 0, 0);
}


SDL_Texture *TextureFactory::getBlockTexture() {
    return textures[BLOCK_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getGateTexture() {
    return textures[GATE_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getCakeTexture() {
    return textures[CAKE_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getPortalTexture() {
    return textures[PORTAL_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getPintoolTexture() {
    return textures[PINTOOL_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getBulletAndRocksTexture() {
    return textures[BULLET_AND_ROCK_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getBackground() {
    return textures[BACKGROUND_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getAcidAndButtonsTexture() {
    return textures[ACID_AND_BUTTONS_TEXTURE_NAME];
}


SDL_Texture *TextureFactory::getDyingChellTexture() {
    return textures[CHELL_DYING_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getFiringChellTexture() {
    return textures[CHELL_FIRING_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getFlyingChellTexture() {
    return textures[CHELL_FLYING_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getRestingIdleChellTexture() {
    return textures[CHELL_RESTING_IDLE_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getRunningChellTexture() {
    return textures[CHELL_RUNNING_CHELL_TEXTURE_NAME];
}

SDL_Texture *TextureFactory::getWinningChellTexture() {
    return textures[CHELL_WINNING_CHELL_TEXTURE_NAME];
}


SDL_Texture *TextureFactory::loadTexture(const std::string &filename, Renderer& renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer.getRenderer(), filename.c_str());
    if (!texture) {
        throw SDLException("Error while loading texture", SDL_GetError());
    }
    return texture;
}

void TextureFactory::setColor(SDL_Texture* texture, int r, int g, int b) {
    int error = SDL_SetTextureColorMod(texture, r, g, b);
    if (error) {
        throw SDLException("Error while changing color in chell texture", SDL_GetError());
    }
}
