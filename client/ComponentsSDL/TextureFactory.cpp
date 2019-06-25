//
// Created by jonathanmedina on 02/06/19.
//

#include <SDL2/SDL_image.h>
#include "TextureFactory.h"
#include "SDLException.h"

#define CHELL_TEXTURE_NAME "chell"
#define BLOCK_TEXTURE_NAME "block"
#define GATE_TEXTURE_NAME "gate"
#define BULLET_AND_ROCK_TEXTURE_NAME "bulletAndRock"
#define ACID_AND_BUTTONS_TEXTURE_NAME "acidAndButtons"
#define BACKGROUND_TEXTURE_NAME "background"
#define CAKE_TEXTURE_NAME "cake"
#define PORTAL_TEXTURE_NAME "portal"
#define PINTOOL_TEXTURE_NAME "pintool"

TextureFactory::TextureFactory() : textures(textures) {
    IMG_Init(IMG_INIT_PNG);
}

TextureFactory::~TextureFactory() {
    for (auto& elem : textures) {
        SDL_DestroyTexture(elem.second);
    }
}

void TextureFactory::init(Renderer& renderer) {
    textures[CHELL_TEXTURE_NAME] = loadTexture(std::string("assets/textures/chell.png"), renderer);
    textures[BLOCK_TEXTURE_NAME] = loadTexture(std::string("assets/textures/block.png"), renderer);
    textures[GATE_TEXTURE_NAME] = loadTexture(std::string("assets/textures/gates.png"), renderer);
    textures[BULLET_AND_ROCK_TEXTURE_NAME] = loadTexture(std::string("assets/textures/bulletAndRock.png"), renderer);
    textures[ACID_AND_BUTTONS_TEXTURE_NAME] = loadTexture(std::string("assets/textures/acidAndButtons.png"), renderer);
    textures[BACKGROUND_TEXTURE_NAME] = loadTexture(std::string("assets/backgroundImage/background.png"), renderer);
    textures[CAKE_TEXTURE_NAME] = loadTexture(std::string("assets/textures/cake.png"), renderer);
    textures[PORTAL_TEXTURE_NAME] = loadTexture(std::string("assets/textures/portal.png"), renderer);
    textures[PINTOOL_TEXTURE_NAME] = loadTexture(std::string("assets/textures/pintool.png"), renderer);
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

SDL_Texture *TextureFactory::getChellTexture() {
    return textures[CHELL_TEXTURE_NAME];
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
